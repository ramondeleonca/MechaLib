// TODO: Complete class behavior
#pragma once
#ifndef SERVO_BASE_H
#define SERVO_BASE_H

#include <Arduino.h>
#include <motor/MotorSafety.h>

/**
 * Recomended PWM pins: 2,4,12-19,21-23,25-27,32-33
 */
class SERVO_Base {
    protected:
        int minDeg = 0;
        int maxDeg = 180;

        int inverted = 0;
        int offset = 0;

        int minPulse = 1000;
        int maxPulse = 2000;
        
        SERVO_Base* followers[2] = {};

        public:
            // Per-servo motor implementation
            /**
             * @brief Begin the servo motor
            */
            virtual void begin() = 0;

            // Per-servo motor implementation
            /**
             * @brief Set the rotation (percent) of the servo motor
             * @param rotation The rotation (percent) to set the servo motor to
             */
            virtual void set(float rotation) = 0;

            /**
             * @brief Set the angle (degrees) of the servo motor
             * @param angle The angle (degrees) to set the servo motor to
             */
            void setAngle(int angle) {
                angle = constrain(angle, minDeg, maxDeg);
                float rotation = (angle - minDeg) / (maxDeg - minDeg);
                set(rotation);
            };

            /**
             * @brief Get the followers for the servo motor
             * @return The followers for the servo motor
             */
            virtual SERVO_Base** getFollowers() {
                return followers;
            }

            // TODO: update this
            /**
             * @brief Update the followers of the servo motor
             * @param speed The speed to set the followers to
             * servo motor internally calls this, not necessary to call this externally
             */
            virtual void updateFollowers(float rotation) {
                for (int i = 0; i < sizeof(followers) / sizeof(followers[0]); i++) {
                    if (followers[i] != nullptr) followers[i]->set(rotation);
                }
            }
};

#endif