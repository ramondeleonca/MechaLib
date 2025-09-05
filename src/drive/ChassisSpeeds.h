#pragma once
#ifndef CHASSIS_SPEEDS_H
#define CHASSIS_SPEEDS_H

#include <Arduino.h>

class ChassisSpeeds {
    private:
        float vx = 0.0;
        float vy = 0.0;
        float omega = 0.0;

    public:
        float getVx() {
            return this->vx;
        };

        float getVy() {
            return this->vy;
        };

        float getOmega() {
            return this->omega;
        };

        void setVx(float vx) {
            this->vx = vx;
        };

        void setVy(float vy) {
            this->vy = vy;
        };

        void setOmega(float omega) {
            this->omega = omega;
        };

        void set(float vx, float vy, float omega) {
            this->vx = vx;
            this->vy = vy;
            this->omega = omega;
        };

        void setFieldRelative(float vx, float vy, float omega, float heading) {
            this->vx = vx * cos(heading) - vy * sin(heading);
            this->vy = vx * sin(heading) + vy * cos(heading);
            this->omega = omega;
        };

        String toString() {
            return "ChassisSpeeds{vx=" + String(this->vx) + ", vy=" + String(this->vy) + ", omega=" + String(this->omega) + "}";
        };
};

#endif