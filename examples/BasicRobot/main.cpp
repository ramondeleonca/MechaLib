#include <MechaLib.h>

class Robot : public RobotBase {
    public:
        void robotSetup() override {
            Serial.begin(115200);
            Serial.println("Robot setup complete.");
        }
};

#define ROBOT_CLASS Robot

#include <core/robot/RobotInit.h>