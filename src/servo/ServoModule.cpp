/**
 * @brief Class representing a servo module
 * @file ServoModule.cpp
 * @date 4 Jan 2026
 * @author cyberreefguru
 */

#include "ServoModule.h"

ServoModule::ServoModule()
{
}

ServoModule::~ServoModule()
{
}

void ServoModule::initialize()
{
    // Setup hardware
    servo1.attach(SERVO_1_PIN);
    servo2.attach(SERVO_3_PIN);
    servo3.attach(SERVO_3_PIN);

    // Call super initialize
    AbstractModule::initialize();
}

void ServoModule::handleReceiveEvent()
{
    switch (i2cBuffer[0])
    {
    case SEESAW_SERVO_BASE:
        handleServoReceive();
        break;
    default:
        SEESAW_DEBUG(F("Unhandled receive cmd 0x"));
        SEESAW_DEBUGLN(base_cmd, HEX);
        break;
    }
}

void ServoModule::handleRequestEvent()
{
    switch (i2cBuffer[0])
    {
    case SEESAW_SERVO_BASE:
        handleServoRequest();
        break;
    default:
        SEESAW_DEBUG(F("Unhandled request cmd 0x"));
        SEESAW_DEBUGLN(base_cmd, HEX);
        break;
    }
}

void ServoModule::handleServoReceive()
{
}

void ServoModule::handleServoRequest()
{
}
