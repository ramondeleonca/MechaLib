#pragma once
#ifndef ROBOTBASE_H
#define ROBOTBASE_H

#include <Arduino.h>

/**
 * The main class a robot program should extend, RobotBase will act as a container for the parent robot functions
 */
class RobotBase {
    public:
        // * Robot Methods
        /**
         * @brief robotSetup is called once when the robot is powered on or reset.
         */
        virtual void robotSetup() = 0;

        /**
         * @brief robotLoop is called repeatedly in the main Arduino loop.
         */
        virtual void robotLoop() = 0;


        // * Auto Methods
        /**
         * @brief autoSetup is called when the robot enters autonomous mode.
         */
        virtual void autoSetup() = 0;

        /**
         * @brief autoLoop is called repeatedly during autonomous mode right after robotLoop.
         */
        virtual void autoLoop() = 0;


        // * Teleop Methods
        /**
         * @brief driverSetup is called when the robot enters teleoperated mode.
         */
        virtual void driverSetup() = 0;

        /**
         * @brief driverLoop is called repeatedly during teleoperated mode right after robotLoop.
         */
        virtual void driverLoop() = 0;


        // * Disabled Methods
        /**
         * @brief disabledSetup is called when the robot enters disabled mode.
         */
        virtual void disabledSetup() = 0;

        /**
         * @brief disabledLoop is called repeatedly during disabled mode right after robotLoop.
         */
        virtual void disabledLoop() = 0;
};

#endif