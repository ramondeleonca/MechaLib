#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <Arduino.h>

class MathUtil {
    public:
        /**
         * @brief Maps a float from one range to another.
         * 
         * @param x The float to map.
         * @param in_min The minimum of the input range.
         * @param in_max The maximum of the input range.
         * @param out_min The minimum of the output range.
         * @param out_max The maximum of the output range.
         * @return The mapped float.
         */
        static float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
            const float run = in_max - in_min;
            if(run == 0){
                log_e("map(): Invalid input range, min == max");
                return -1; // AVR returns -1, SAM returns 0
            }
            const float rise = out_max - out_min;
            const float delta = x - in_min;
            return (delta * rise) / run + out_min;
        }
};

#endif