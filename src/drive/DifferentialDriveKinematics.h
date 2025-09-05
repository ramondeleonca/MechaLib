#pragma once
#ifndef DIFFERENTIAL_DRIVE_KINEMATICS_H
#define DIFFERENTIAL_DRIVE_KINEMATICS_H

#include <Arduino.h>

class DifferentialDriveKinematics {
    private:
        float trackWidth;
        float wheelRadius;

    public:
        DifferentialDriveKinematics(float trackWidth, float wheelRadius) {
            this->trackWidth = trackWidth;
            this->wheelRadius = wheelRadius;
        }

        void calculateWheelSpeeds(float* wheelSpeeds, float vy, float omega) {
            wheelSpeeds[0] = (vy - omega * trackWidth / 2) / wheelRadius;
            wheelSpeeds[1] = (vy + omega * trackWidth / 2) / wheelRadius;
        }

        static float* normalizeWheelSpeeds(float* wheelSpeeds) {
            float maxMagnitude = 0;
            for (int i = 0; i < 2; i++) {
                float magnitude = abs(wheelSpeeds[i]);
                if (magnitude > maxMagnitude) maxMagnitude = magnitude;
            }
            if (maxMagnitude > 1) {
                for (int i = 0; i < 2; i++) wheelSpeeds[i] /= maxMagnitude;
            }
            return wheelSpeeds;
        }
};

#endif