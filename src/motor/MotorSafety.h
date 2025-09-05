#pragma once
#ifndef MOTOR_SAFETY_H
#define MOTOR_SAFETY_H

enum MotorSafetyStatus {
    PROTECTED = 0,
    ENABLED = 1
};

class MotorSafety {
    private:
        MotorSafetyStatus status = MotorSafetyStatus::PROTECTED;

    public:
        void enable() {
            status = MotorSafetyStatus::ENABLED;
        }

        void disable() {
            status = MotorSafetyStatus::PROTECTED;
        }
    
        MotorSafetyStatus getStatus() {
            return status;
        }

    // Singleton
    public:
        MotorSafety() {};
        static MotorSafety& getInstance() {
            static MotorSafety instance;
            return instance;
        }
};

#endif