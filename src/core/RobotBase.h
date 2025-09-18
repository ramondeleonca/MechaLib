#pragma once
#ifndef ROBOTBASE_H
#define ROBOTBASE_H

#include <Arduino.h>
#include <core/logger/Logger.h>
#include <esp_task_wdt.h>

/**
 * ## RobotBase
 * @brief [EN] The main class a robot program should extend, RobotBase will act as a container for the parent robot functions
 * @brief [ES] La clase principal que un programa de robot debe extender, RobotBase actuará como un contenedor para las funciones principales del robot
 */
class RobotBase {
    // ! Public constants
    public:
        const enum ROBOT_STATUS {
            ROBOT_DISABLED,
            ROBOT_AUTO,
            ROBOT_DRIVER
        };

        static const uint8_t ROBOT_PERIOD = 20; // Main loop period in milliseconds
        static const uint16_t ROBOT_STALL_TIMEOUT = 2000; // Time in milliseconds before the watchdog timer triggers a reset

    // ! Private members called by the main program
    private:
        // Timekeeping
        uint32_t lastTime = 0;
        uint32_t currentTime = 0;
        uint16_t deltaTime = 0;

    // ! Protected members for use by child classes
    protected:
        RobotBase::ROBOT_STATUS robotStatus = ROBOT_STATUS::ROBOT_DISABLED;

    // ! Public methods
    public:
        // * Setup and Loop Methods
        /**
         * @brief [EN] setupRobot is called once when the robot is powered on or reset.
         * @brief [ES] setupRobot se llama una vez cuando el robot se enciende o reinicia.
         * 
         * @param robot [EN] Reference to the robot instance to set up.
         * [ES] Referencia a la instancia del robot para configurar.
         */
        static void setupRobot(RobotBase &robot) {
            // * Log program start
            Logger::getInstance().log(F("********** MechaLeague Robot Setup **********"));

            // * Set CPU frequency to 240 MHz for maximum performance
            setCpuFrequencyMhz(240);

            // * Call user-defined robot setup
            robot.robotSetup();

            // * Setup watchdog timer for loop
            // Watchdog timer is set up after robotSetup to avoid false positives during setup which could take longer than the stall timeout
            esp_err_t taskInitErr = esp_task_wdt_init(ROBOT_STALL_TIMEOUT / portTICK_PERIOD_MS, true); // Enable panic so ESP32 restarts
            esp_err_t taskAddErr = esp_task_wdt_add(NULL); // Add current thread to WDT watch

            // * Log any errors with watchdog timer setup
            // Task watchdog timer init error
            if (taskInitErr != ESP_OK)
                Logger::getInstance().log("Error: Initializing watchdog timer: " + String(esp_err_to_name(taskInitErr)));

            // Task watchdog timer add error
            if (taskAddErr != ESP_OK)
                Logger::getInstance().log("Error: Adding task to watchdog timer: " + String(esp_err_to_name(taskAddErr)));

            // * Log setup complete
            Logger::getInstance().log(F("********** MechaLeague Robot Setup Complete **********"));
        }

        /**
         * @brief [EN] loopRobot is called repeatedly in the main Arduino loop.
         * @brief [ES] loopRobot se llama repetidamente en el bucle principal de Arduino.
         * 
         * @param robot [EN] Reference to the robot instance to run the loop for.
         * [ES] Referencia a la instancia del robot para ejecutar el bucle.
         */
        static void loopRobot(RobotBase &robot) {
            // * Timekeeping
            robot.currentTime = millis();
            robot.deltaTime = robot.currentTime - robot.lastTime;

            // If the loop is running faster than the desired period, delay to maintain consistent timing
            if (robot.deltaTime < ROBOT_PERIOD) {
                // Delay for the remaining time in the period
                vTaskDelay((ROBOT_PERIOD - robot.deltaTime) / portTICK_PERIOD_MS);

                // Recalculate timing
                robot.currentTime = millis();
                robot.deltaTime = robot.currentTime - robot.lastTime;
            } else if (robot.deltaTime > ROBOT_PERIOD && robot.lastTime != 0) {
                // If the loop is running slower than the desired period, log a warning
                Logger::getInstance().log("Warning: Robot loop overrun (dt: " + String(robot.deltaTime) + " ms)");
            }

            // * Call user-defined robot loop
            robot.robotLoop();

            // * Call the apporpriate mode loop
            switch(robot.robotStatus) {
                case ROBOT_DISABLED:
                    robot.disabledLoop();
                    break;
                case ROBOT_AUTO:
                    robot.autoLoop();
                    break;
                case ROBOT_DRIVER:
                    robot.driverLoop();
                    break;
            }

            // Feed the watchdog timer to keep it alive
            esp_task_wdt_reset(); // Reset watchdog timer

            // Update lastTime for the next loop iteration
            robot.lastTime = robot.currentTime;
        }

    // ! User-defined methods
    public:
        // * Robot Methods
        /**
         * @brief [EN] robotSetup is called once when the robot is powered on or reset.
         * @brief [ES] robotSetup se llama una vez cuando el robot se enciende o se reinicia.
         */
        virtual void robotSetup() {};

        /**
         * @brief [EN] robotLoop is called repeatedly in the main Arduino loop.
         * @brief [ES] robotLoop se llama repetidamente en el bucle principal de Arduino.
         */
        virtual void robotLoop() {};


        // * Auto Methods
        /**
         * @brief [EN] autoSetup is called every time the robot enters autonomous mode.
         * @brief [ES] autoSetup se llama cada vez que el robot entra en modo autónomo.
         */
        virtual void autoSetup() {};

        /**
         * @brief [EN] autoLoop is called repeatedly during autonomous mode right after robotLoop.
         * @brief [ES] autoLoop se llama repetidamente durante el modo autónomo justo después de robotLoop.
         */
        virtual void autoLoop() {};


        // * Teleop Methods
        /**
         * @brief [EN] driverSetup is called every time the robot enters teleoperated mode.
         * @brief [ES] driverSetup se llama cada vez que el robot entra en modo teleoperado.
         */
        virtual void driverSetup() {};

        /**
         * @brief [EN] driverLoop is called repeatedly during teleoperated mode right after robotLoop.
         * @brief [ES] driverLoop se llama repetidamente durante el modo teleoperado justo después de robotLoop.
         */
        virtual void driverLoop() {};


        // * Disabled Methods
        /**
         * @brief [EN] disabledSetup is called every time the robot enters disabled mode.
         * @brief [ES] disabledSetup se llama cada vez que el robot entra en modo deshabilitado.
         */
        virtual void disabledSetup() {};

        /**
         * @brief [EN] disabledLoop is called repeatedly during disabled mode right after robotLoop.
         * @brief [ES] disabledLoop se llama repetidamente durante el modo deshabilitado justo después de robotLoop.
         */
        virtual void disabledLoop() {};
};

/**
 * ## ARDUINO_MECHALEAGUE_ROBOT_REGISTRATION
 * @brief [EN] Automatically sets up the Arduino functions for the robot instance.
 * @brief [ES] Define automáticamente las funciones Arduino para la instancia de robot.
 */
#define ARDUINO_MECHALEAGUE_ROBOT_REGISTRATION(robot) \
    static_assert(std::is_base_of<RobotBase, decltype(robot)>::value, "The robot must extend RobotBase!"); \
    void setup() { RobotBase::setupRobot(robot); } \
    void loop() { RobotBase::loopRobot(robot); }

/**
 * ## REGISTER_ROBOT
 * @brief [EN] Automatically configures the environment for the robot instance.
 * @brief [ES] Configura el entorno automaticamente para la instancia de robot.
 */
#define REGISTER_ROBOT(robot) ARDUINO_MECHALEAGUE_ROBOT_REGISTRATION(robot)

#endif