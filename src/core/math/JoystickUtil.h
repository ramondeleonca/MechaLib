#ifndef JOYSTICK_UTIL_H
#define JOYSTICK_UTIL_H

#include <Arduino.h>

class JoystickUtil {
    public:
        /**
         * @brief Maps a joystick input value with a deadband.
         * 
         * @param x The joystick input value.
         * @param deadband The deadband value.
         * @param in_min The minimum of the input range.
         * @param in_max The maximum of the input range.
         * @param out_min The minimum of the output range.
         * @param out_max The maximum of the output range.
         * @return The mapped joystick value with deadband applied.
         */
        static float deadbandMap(float x, float deadband, float in_min, float in_max, float out_min, float out_max) {
            if (abs(x) < deadband) return 0.0;
            float sign = x > 0 ? 1 : -1;
            return sign * map(abs(x), in_min + deadband, in_max, out_min, out_max);
        };
};


#endif