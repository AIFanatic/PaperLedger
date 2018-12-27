// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../JsonVariant.hpp"
#include "../Polyfills/type_traits.hpp"
#include "../Serialization/measure.hpp"
#include "../Serialization/serialize.hpp"
#include "./endianess.hpp"

namespace ArduinoJson {
namespace Internals {

template <typename TPrint>
class MsgPackSerializer {
 public:
  MsgPackSerializer(TPrint& output) : _output(&output), _bytesWritten(0) {}

  template <typename T>
  typename enable_if<sizeof(T) == 4>::type acceptFloat(T value32) {
    writeByte(0xCA);
    writeInteger(value32);
  }

  template <typename T>
  typename enable_if<sizeof(T) == 8>::type acceptFloat(T value64) {
    float value32 = float(value64);
    if (value32 == value64) {
      writeByte(0xCA);
      writeInteger(value32);
    } else {
      writeByte(0xCB);
      writeInteger(value64);
    }
  }

  void acceptArray(const JsonArray& array) {
    size_t n = array.size();
    if (n < 0x10) {
      writeByte(uint8_t(0x90 + array.size()));
    } else if (n < 0x10000) {
      writeByte(0xDC);
      writeInteger(uint16_t(n));
    } else {
      writeByte(0xDD);
      writeInteger(uint32_t(n));
    }
    for (JsonArray::const_iterator it = array.begin(); it != array.end();
         ++it) {
      it->visit(*this);
    }
  }

  void acceptObject(const JsonObject& object) {
    size_t n = object.size();
    if (n < 0x10) {
      writeByte(uint8_t(0x80 + n));
    } else if (n < 0x10000) {
      writeByte(0xDE);
      writeInteger(uint16_t(n));
    } else {
      writeByte(0xDF);
      writeInteger(uint32_t(n));
    }
    for (JsonObject::const_iterator it = object.begin(); it != object.end();
         ++it) {
      acceptString(it->key);
      it->value.visit(*this);
    }
  }

  void acceptString(const char* value) {
    if (!value) return writeByte(0xC0);  // nil

    size_t n = strlen(value);

    if (n < 0x20) {
      writeByte(uint8_t(0xA0 + n));
    } else if (n < 0x100) {
      writeByte(0xD9);
      writeInteger(uint8_t(n));
    } else if (n < 0x10000) {
      writeByte(0xDA);
      writeInteger(uint16_t(n));
    } else {
      writeByte(0xDB);
      writeInteger(uint32_t(n));
    }
    writeBytes(reinterpret_cast<const uint8_t*>(value), n);
  }

  void acceptRawJson(const char* /*value*/) {}

  void acceptNegativeInteger(JsonUInt value) {
    JsonUInt negated = JsonUInt(~value + 1);
    if (value <= 0x20) {
      writeInteger(int8_t(negated));
    } else if (value <= 0x80) {
      writeByte(0xD0);
      writeInteger(int8_t(negated));
    } else if (value <= 0x8000) {
      writeByte(0xD1);
      writeInteger(int16_t(negated));
    } else if (value <= 0x80000000) {
      writeByte(0xD2);
      writeInteger(int32_t(negated));
    }
#if ARDUINOJSON_USE_LONG_LONG || ARDUINOJSON_USE_INT64
    else {
      writeByte(0xD3);
      writeInteger(int64_t(negated));
    }
#endif
  }

  void acceptPositiveInteger(JsonUInt value) {
    if (value <= 0x7F) {
      writeInteger(uint8_t(value));
    } else if (value <= 0xFF) {
      writeByte(0xCC);
      writeInteger(uint8_t(value));
    } else if (value <= 0xFFFF) {
      writeByte(0xCD);
      writeInteger(uint16_t(value));
    } else if (value <= 0xFFFFFFFF) {
      writeByte(0xCE);
      writeInteger(uint32_t(value));
    }
#if ARDUINOJSON_USE_LONG_LONG || ARDUINOJSON_USE_INT64
    else {
      writeByte(0xCF);
      writeInteger(uint64_t(value));
    }
#endif
  }

  void acceptBoolean(bool value) {
    writeByte(value ? 0xC3 : 0xC2);
  }

  void acceptNull() {
    writeByte(0xC0);
  }

  size_t bytesWritten() const {
    return _bytesWritten;
  }

 private:
  void writeByte(uint8_t c) {
    _output->print(char(c));
    _bytesWritten++;
  }

  void writeBytes(const uint8_t* c, size_t n) {
    for (; n > 0; --n, ++c) writeByte(*c);
  }

  template <typename T>
  void writeInteger(T value) {
    fixEndianess(value);
    writeBytes(reinterpret_cast<uint8_t*>(&value), sizeof(value));
  }

  TPrint* _output;
  size_t _bytesWritten;
};
}  // namespace Internals

template <typename TSource, typename TDestination>
inline size_t serializeMsgPack(const TSource& source, TDestination& output) {
  using namespace Internals;
  return serialize<MsgPackSerializer>(source, output);
}

template <typename TSource, typename TDestination>
inline size_t serializeMsgPack(const TSource& source, TDestination* output,
                               size_t size) {
  using namespace Internals;
  return serialize<MsgPackSerializer>(source, output, size);
}

template <typename TSource>
inline size_t measureMsgPack(const TSource& source) {
  using namespace Internals;
  return measure<MsgPackSerializer>(source);
}

}  // namespace ArduinoJson
