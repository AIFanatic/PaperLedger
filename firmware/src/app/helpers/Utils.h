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
        
        static String readableTimestamp(String timestamp) { 
            char buffer[21];
            time_t input_time = (time_t) timestamp.toInt();
            strftime(buffer, 21, "%Y-%m-%d %H:%M UTC", localtime(&input_time));

            String readable_timestamp = buffer;
            return readable_timestamp;
        }

        static long getCurrentTime() {
            timeval t;
            gettimeofday(&t, NULL);
            return (t.tv_sec * (uint64_t)1000) + (t.tv_usec / 1000);
        }

        static long getCurrentTimeMicros() {
            timeval t;
            gettimeofday(&t, NULL);
            return t.tv_usec;
        }

        static long getBootCurrentTime() {
            return millis();
        }

        static bool hasBootedFromDeepSleep() {
            return (esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_UNDEFINED);
        }
};

#endif