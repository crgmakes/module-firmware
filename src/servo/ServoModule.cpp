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
    // Call super initialize
    AbstractModule::initialize();

    // Setup hardware
    servos[0].attach(SERVO_1_PIN);
    servos[0].write(0); // this needs to be pulled from EEPROM

    servos[1].attach(SERVO_2_PIN);
    servos[1].write(0); // this needs to be pulled from EEPROM

    servos[2].attach(SERVO_3_PIN);
    servos[2].write(0); // this needs to be pulled from EEPROM
}

void ServoModule::handleReceiveEvent()
{
    if (i2cBuffer[0] == SEESAW_SERVO_BASE)
    {
        if (receiveLength == 2)
        {
            // This is a read command
            return;
        }

        uint8_t channel = i2cBuffer[2];
        if (channel >= MODULE_CHANNELS)
        {
            SEESAW_DEBUG(F("channel out of range: "));
            SEESAW_DEBUGLN(channel);
            return;
        }

        uint8_t angle = i2cBuffer[3];
        servos[channel].write(angle);
        values[channel] = angle;
    }
    else
    {
        SEESAW_DEBUG(F("Unhandled receive cmd 0x"));
        SEESAW_DEBUGLN(base_cmd, HEX);
    }
}

void ServoModule::handleRequestEvent()
{
    if (i2cBuffer[0] == SEESAW_SERVO_BASE)
    {
        uint8_t channel = i2cBuffer[2];
        uint8_t angle = 0;
        if (channel >= MODULE_CHANNELS)
        {
            SEESAW_DEBUG(F("Requested channel out of range: "));
            SEESAW_DEBUGLN(channel);
            Wire.write(0xff); // instant reply
        }
        else
        {
            angle = (servos[channel].read() & 0x0ff);
            if (angle > 180)
            {
                Wire.write(0xff); // instant reply
            }
            else
            {
                Wire.write(angle); // instant reply
            }
        }
    }
    else
    {
        SEESAW_DEBUG(F("Unhandled request cmd 0x"));
        SEESAW_DEBUGLN(base_cmd, HEX);
    }
}