#pragma once
#ifndef MOTOR_CONTROLLER_DRV8871_H
#define MOTOR_CONTROLLER_DRV8871_H

#include <Arduino.h>
#include <motor/MOTOR_CONTROLLER_Base.h>
#include <motor/MotorSafety.h>

class MOTOR_CONTROLLER_DRV8871 : public MOTOR_CONTROLLER_Base {
    public:
        /**
         * Idle mode for the motor controller
         */
        enum DRV8871_IdleMode {
            kCoast = 0,
            kBrake = 1
        };

    private:
        int in1;
        int in2;
        DRV8871_IdleMode idleMode = kCoast;
    
    public:
        MOTOR_CONTROLLER_DRV8871(int in1, int in2, float deadband = 0.075) {
            this->in1 = in1;
            this->in2 = in2;
            this->deadband = deadband;
        };

        void begin() {
            pinMode(in1, OUTPUT);
            pinMode(in2, OUTPUT);

            analogWrite(in1, LOW);
            analogWrite(in2, LOW);
        }

        void setIdleMode(DRV8871_IdleMode mode) {
            this->idleMode = mode;
        }

        void set(float speed, bool isBeep) {
            speed = applySpeedFilters(speed, isBeep);

            if (speed > 0) {
                analogWrite(in1, abs(speed) * 255);
                analogWrite(in2, LOW);
            } else if (speed < 0) {
                analogWrite(in1, LOW);
                analogWrite(in2, abs(speed) * 255);
            } else {
                if (this->idleMode == kBrake) {
                    analogWrite(in1, 255);
                    analogWrite(in2, 255);
                } else {
                    analogWrite(in1, LOW);
                    analogWrite(in2, LOW);
                }
            }

            // Update followers
            updateFollowers(speed, isBeep);
        }
        
        void set(float speed) {
            set(speed, false);
        };
};

#endif