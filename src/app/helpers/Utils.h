#ifndef _UTIL_H_
#define _UTIL_H_

#include <Arduino.h>

class Utils {
    public:
        static double roundDecimals(double num, int precision) {
            if(num == 0) {
                return 0;
            }
            return roundf(num * pow(10, precision)) / pow(10, precision);
        }

        static String numToHuman(double num, int precision) {
            if(num == 0) {
                return "0";
            }

            if(num >= 1000000000) {
                return String(Utils::roundDecimals(num / 1000000000, precision)) + " B";
            }
            else if(num >= 1000000) {
                return String(Utils::roundDecimals(num / 1000000, precision)) + " M";
            }
            else if(num >= 1000) {
                return String(Utils::roundDecimals(num / 1000, precision)) + " K";
            }

            return String(Utils::roundDecimals(num, precision));
        }
};

#endif