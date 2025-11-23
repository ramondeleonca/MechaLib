#pragma once
#ifndef MOTOR_CONTROLLER_L298N_H
#define MOTOR_CONTROLLER_L298N_H

#include <Arduino.h>
#include <motor/dc/MOTOR_CONTROLLER_Base.h>
#include <motor/MotorSafety.h>

class MOTOR_CONTROLLER_L298N : public MOTOR_CONTROLLER_Base {
    private:
        int in1;
        int in2;
        int en;

    public:
        /**
         * @brief Constructor for the L298N motor controller.
         * @param in1 Pin for IN1 control.
         * @param in2 Pin for IN2 control.
         * @param en Pin for EN control (PWM).
         */
        MOTOR_CONTROLLER_L298N(int in1, int in2, int en, float deadband = 0.075) {
            this->in1 = in1;
            this->in2 = in2;
            this->en = en;
            this->deadband = deadband;
        };

        void begin() {
            pinMode(in1, OUTPUT);
            pinMode(in2, OUTPUT);
            pinMode(en, OUTPUT);

            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            analogWrite(en, LOW);
        }

        void set(float speed, bool isBeep) {
            speed = applySpeedFilters(speed, isBeep);

            if (speed > 0) {
                digitalWrite(in1, HIGH);
                digitalWrite(in2, LOW);
            } else if (speed < 0) {
                digitalWrite(in1, LOW);
                digitalWrite(in2, HIGH);
            } else {
                digitalWrite(in1, LOW);
                digitalWrite(in2, LOW);
            }

            analogWrite(en, abs(speed) * 255);

            // Update followers
            updateFollowers(speed, isBeep);
        }
        
        void set(float speed) {
            set(speed, false);
        };
};

// Alias
using CONTROLADOR_MOTOR_L298N = MOTOR_CONTROLLER_L298N;

#endif