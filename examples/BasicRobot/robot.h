#include <MechaLib.h>
#include <Arduino.h>

class Robot : public RobotBase {
    public:
        void robotSetup() override {
            Logger::getInstance().log("Robot setup.");
        }

        void robotLoop() override {
            // Example: Log chassis speeds (0, 0, 0)
            ChassisSpeeds speeds(0.0, 0.0, 0.0);
            Logger::getInstance().log(speeds);
        }
};