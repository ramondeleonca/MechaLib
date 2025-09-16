#include <Arduino.h>
#include <unity.h>
#include <MechaLib.h>

ChassisSpeeds speeds(1.0, 2.0, 3.0);

void testLogger() {
    Logger::getInstance().log("Testing Logger...");
    Logger::getInstance().log(speeds);
}

void setup() {
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(testLogger);
    UNITY_END();
}

void loop() {

}