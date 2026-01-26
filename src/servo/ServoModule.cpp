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
    servos[0].attach(SERVO_1_PIN);
    servos[0].write(0); // this needs to be pulled from EEPROM

    servos[1].attach(SERVO_2_PIN);
    servos[1].write(0); // this needs to be pulled from EEPROM

    servos[2].attach(SERVO_3_PIN);
    servos[2].write(0); // this needs to be pulled from EEPROM

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

    uint32_t angle = 0;
    angle = servos[0].read();
    if( angle == 0 )
    {
        servos[0].write(180);
    }
    else
    {
        servos[0].write(0);
    }
    return;

    uint8_t channel = i2cBuffer[2];
    if (channel >= MODULE_CHANNELS)
    {
        SEESAW_DEBUG(F("Requested channel out of range: "));
        SEESAW_DEBUGLN(channel);
        return;
    }

    angle = i2cBuffer[3]; // MSB
    angle <<= 8;
    angle |= i2cBuffer[4]; // LSB

    servos[channel].write(angle);
    // switch (channel)
    // {
    // case 0:
    //     servo1.write(angle);
    //     break;
    // case 1:
    //     servo2.write(angle);
    //     break;
    // case 2:
    //     servo3.write(angle);
    //     break;
    // case 3:
    //     // servo3.write(angle);
    //     break;
    // default:
    //     break;
    // }
}

void ServoModule::handleServoRequest()
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
        angle = servos[channel].read();
        // switch (channel)
        // {
        // case 0:
        //     angle = servo1.read();
        //     break;
        // case 1:
        //     angle = servo2.read();
        //     break;
        // case 2:
        //     angle = servo3.read();
        //     break;
        // case 3:
        //     // angle = servo4.read();
        //     break;
        // default:
        //     break;
        // }
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
