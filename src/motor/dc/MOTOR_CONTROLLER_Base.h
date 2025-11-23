#pragma once
#ifndef CONTROLLER_BASE_H
#define CONTROLLER_BASE_H

#include <Arduino.h>
#include <motor/MotorSafety.h>

/**
 * Recomended PWM pins: 2,4,12-19,21-23,25-27,32-33
 */
class MOTOR_CONTROLLER_Base {
    protected:
        float multiplier = 1.0;
        float deadband = 0.0;
        float deadbandLimit = 0.1;
        bool inverted = false;
        MOTOR_CONTROLLER_Base* followers[2] = {};

        // TODO: Check the logic of this function
        /**
         * @brief Process the speed value (apply deadband, multiplier, inversion, constraints, motor safety status and beep setpoint)
         * @param speed The speed to process
         * @param isBeep Wether or not this is a beep setpoint (speed value will be taken as a percentage of deadband)
         */
        virtual float applySpeedFilters(float speed, bool isBeep) {
            if (MotorSafety::getInstance().getStatus() == MotorSafetyStatus::PROTECTED && !isBeep) return 0;
            if (isBeep) {
                if (this->deadband > deadbandLimit) speed = deadbandLimit * speed;
                else speed = this->deadband * speed;
            } else {
                if (this->inverted) speed = -speed;
                speed *= this->multiplier;
                speed = constrain(speed, -1, 1);
                if (abs(speed) < this->deadband) speed = 0;
            }
            return speed;
        }

    public:
        // Per-controller implementation
        /**
         * @brief Begin the motor controller
        */
        virtual void begin() = 0;

        // Per-controller implementation
        /**
         * @brief Set the speed of the motor
         * @param speed The speed to set the motor to
         * @param isBeep Wether or not this is a beep setpoint (speed value will be taken as a percentage of deadband)
         */
        virtual void set(float speed, bool isBeep) = 0;

        /**
         * @brief Set the speed of the motor
         * @param speed The speed to set the motor to
         */
        void set(float speed) {
            set(speed, false);
        };

        /**
         * @brief Wether or not the motor should be inverted
         */
        virtual void setInverted(bool inverted) {
            this->inverted = inverted;
        };

        /**
         * @brief Stop the motor
         * Calls set(0) by default
         */
        virtual void stop() {
            set(0);
        }

        /**
         * @brief Add a follower to the motor controller
         * @param slave The motor controller to follow this one
         * @return Wether or not the follower was added
         */
        virtual bool addFollower(MOTOR_CONTROLLER_Base* slave) {
            int8_t openSlot = -1;
            for (int i = 0; i < sizeof(followers) / sizeof(followers[0]); i++) if (followers[i] == nullptr) openSlot = i;
            if (openSlot != -1) {
                followers[openSlot] = slave;
                return true;
            } else {
                Serial.println("No open slots for followers, the motor controller can have up to " + String(sizeof(followers) / sizeof(followers[0])) + " followers");
                return false;
            }
        }

        /**
         * @brief Remove a follower from the motor controller
         * @param slave The motor controller to remove from the followers list
         */
        virtual void removeFollower(MOTOR_CONTROLLER_Base* slave) {
            for (int i = 0; i < sizeof(followers) / sizeof(followers[0]); i++) if (followers[i] == slave) followers[i] = nullptr;
        }

        /**
         * @brief Follow another motor controller
         * Inverted status is independent
         */
        virtual void follow(MOTOR_CONTROLLER_Base* master) {
            master->addFollower(this);
        }

        /**
         * @brief Set the multiplier for the motor controller
         * @param multiplier The multiplier to set
         */
        virtual void setMultiplier(float multiplier) {
            this->multiplier = multiplier;
        }

        /**
         * @brief Set the deadband for the motor controller
         * @param deadband The deadband to set
         */
        virtual void setDeadband(float deadband) {
            this->deadband = deadband;
        }

        /**
         * @brief Get the multiplier for the motor controller
         * @return The multiplier for the motor controller
         */
        virtual float getMultiplier() {
            return multiplier;
        }

        /**
         * @brief Get the deadband for the motor controller
         * @return The deadband for the motor controller
         */
        virtual float getDeadband() {
            return deadband;
        }

        /**
         * @brief Get the inverted status for the motor controller
         * @return The inverted status for the motor controller
         */
        virtual bool getInverted() {
            return inverted;
        }

        /**
         * @brief Get the followers for the motor controller
         * @return The followers for the motor controller
         */
        virtual MOTOR_CONTROLLER_Base** getFollowers() {
            return followers;
        }

        /**
         * @brief Update the followers of the motor controller
         * @param speed The speed to set the followers to
         * @param isBeep Wether or not this is a beep setpoint (speed value will be taken as a percentage of deadband)
         * Calls set(speed, isBeep) on all followers
         * Motor controller internally calls this, not necessary to call this externally
         */
        virtual void updateFollowers(float speed, bool isBeep) {
            for (int i = 0; i < sizeof(followers) / sizeof(followers[0]); i++) {
                if (followers[i] != nullptr) followers[i]->set(speed, isBeep);
            }
        }
};

// Alias
using CONTROLADOR_MOTOR_Base = MOTOR_CONTROLLER_Base;

#endif