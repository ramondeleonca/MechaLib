#pragma once
#ifndef MECANUM_DRIVE_KINEMATICS_H
#define MECANUM_DRIVE_KINEMATICS_H

#include <Arduino.h>

class MecanumDriveKinematics {
    private:
        float wheelDiameter;
        float trackWidth;
        float wheelBase;

    public:
        MecanumDriveKinematics(float wheelDiameter, float trackWidth, float wheelBase) {
            this->wheelDiameter = wheelDiameter;
            this->trackWidth = trackWidth;
            this->wheelBase = wheelBase;
        };

        void calculateWheelSpeeds(float* wheelSpeeds, float vx, float vy, float omega) {
            wheelSpeeds[0] = vx - vy - omega * (this->trackWidth + this->wheelBase) / 2;
            wheelSpeeds[1] = vx + vy + omega * (this->trackWidth + this->wheelBase) / 2;
            wheelSpeeds[2] = vx + vy - omega * (this->trackWidth + this->wheelBase) / 2;
            wheelSpeeds[3] = vx - vy + omega * (this->trackWidth + this->wheelBase) / 2;
        };

        static float* normalizeWheelSpeeds(float* wheelSpeeds) {
            float maxMagnitude = 0;
            for (int i = 0; i < 4; i++) {
                float magnitude = abs(wheelSpeeds[i]);
                if (magnitude > maxMagnitude) maxMagnitude = magnitude;
            }
            if (maxMagnitude > 1) {
                for (int i = 0; i < 4; i++) wheelSpeeds[i] /= maxMagnitude;
            }
            return wheelSpeeds;
        };
};

#endif