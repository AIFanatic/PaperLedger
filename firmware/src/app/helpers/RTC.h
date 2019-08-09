#ifndef _RTC_H_
#define _RTC_H_

#include "Arduino.h"
#include "esp32/ulp.h"
#include "soc/rtc.h"

class RTC {
    /*
    * Offset (in 32-bit words) in RTC Slow memory where the data is placed
    * by the ULP coprocessor. It can be chosen to be any value greater or equal
    * to ULP program size, and less than the CONFIG_ULP_COPROC_RESERVE_MEM/4 - 6,
    * where 6 is the number of words used by the ULP coprocessor.
    */
    #define ULP_DATA_OFFSET     36

    public:
        /**
         * @brief Utility function which reads data written by ULP program
         *
         * @param offset offset from ULP_DATA_OFFSET in RTC Slow memory, in words
         * @return lower 16-bit part of the word writable by the ULP
         */
        static inline uint16_t read(size_t offset) {
            // Serial.printf("RTC: %i\n", RTC_SLOW_MEM[ULP_DATA_OFFSET + offset] & 0xffff);
            return RTC_SLOW_MEM[ULP_DATA_OFFSET + offset] & 0xffff;
        }

        /**
         * @brief Utility function which writes data to be ready by ULP program
         *
         * @param offset offset from ULP_DATA_OFFSET in RTC Slow memory, in words
         * @param value lower 16-bit part of the word to be stored
         */
        static inline void write(size_t offset, uint16_t value) {
            RTC_SLOW_MEM[ULP_DATA_OFFSET + offset] = value;
        }



        static inline void writeLong(size_t offset, long value) {
            uint16_t a = (uint16_t) (value >> 16);
            uint16_t b = (uint16_t) (value);

            RTC_SLOW_MEM[ULP_DATA_OFFSET + offset] = a;
            RTC_SLOW_MEM[ULP_DATA_OFFSET + offset + 1] = b;
        }

        static inline long readLong(size_t offset) {
            uint16_t a = RTC_SLOW_MEM[ULP_DATA_OFFSET + offset];
            uint16_t b = RTC_SLOW_MEM[ULP_DATA_OFFSET + offset + 1];

            return (long)a << 16 | (b & 0xFFFFFFFF);
        }

        static void hexdump(const uint32_t* src, size_t count) {
            for (size_t i = 0; i < count; ++i) {
                printf("%08x ", *src);
                ++src;
                if ((i + 1) % 4 == 0) {
                    printf("\n");
                }
            }
        }
        static void dumpRTC() {
            hexdump(RTC_SLOW_MEM, CONFIG_ULP_COPROC_RESERVE_MEM / 4);
        }
};

#endif