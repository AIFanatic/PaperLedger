// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("JsonArray basics") {
  DynamicJsonDocument doc;
  JsonArray array = doc.to<JsonArray>();

  SECTION("isNull()") {
    REQUIRE(array.isNull() == false);
  }

  SECTION("InitialSizeIsZero") {
    REQUIRE(0U == array.size());
  }

  SECTION("CreateNestedArray") {
    JsonArray arr = array.createNestedArray();
    REQUIRE(arr == array[0].as<JsonArray>());
  }

  SECTION("CreateNestedObject") {
    JsonObject obj = array.createNestedObject();
    REQUIRE(obj == array[0].as<JsonObject>());
  }
}
