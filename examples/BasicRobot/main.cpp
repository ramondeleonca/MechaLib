#include <MechaLib.h>

class Robot : public RobotBase {
    public:
        void robotSetup() override {
            
        }
};

#define ROBOT_CLASS Robot

#include <core/robot/RobotInit.h>