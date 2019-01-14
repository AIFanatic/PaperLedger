#ifndef _UTIL_H_
#define _UTIL_H_

#include <Arduino.h>

class Util {
    public:
        static double roundDecimals(double num, int precision) {
            return roundf(num * pow(10, precision)) / pow(10, precision);
        }

        static String numToHuman(double num, int precision) {
            if(num >= 1000000000) {
                return String(Util::roundDecimals(num / 1000000000, precision)) + " B";
            }
            else if(num >= 1000000) {
                return String(Util::roundDecimals(num / 1000000, precision)) + " M";
            }
            if(num >= 1000) {
                return String(Util::roundDecimals(num / 1000, precision)) + " K";
            }
        }
};

#endif