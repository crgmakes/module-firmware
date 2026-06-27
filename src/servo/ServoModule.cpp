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

/**
 * @brief handles any data received from the controller. Usually setting a register to a value.
 */
void ServoModule::handleReceiveEvent()
{
    if (i2cBuffer[0] == SEESAW_SERVO_BASE)
    {
        if (receiveLength == 2)
        {
            // Writing two bytes is really writing the command and function for an upcoming read
            return;
        }

        if (i2cBuffer[1] == SEESAW_SERVO_ANGLE)
        {
            // We have more than two bytes, so let's "parse" the data
            // For a servo command, the 3rd byte is the channel
            uint8_t channel = i2cBuffer[2];

            // Check if channel is out of bounds
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
            SEESAW_DEBUG(F("Unhandled receive function 0x"));
            SEESAW_DEBUGLN(i2cBuffer[1], HEX);
        }
    }
    else
    {
        SEESAW_DEBUG(F("Unhandled receive cmd 0x"));
        SEESAW_DEBUGLN(i2cBuffer[0], HEX);
    }
}

/**
 * @brief Handles the controller writing data to us and expecting some sort of response
 */
void ServoModule::handleRequestEvent()
{
    // NOTE: the last receiveEvent filled the i2cbuffer with information about this command
    if (i2cBuffer[0] == SEESAW_SERVO_BASE)
    {
        uint8_t func = i2cBuffer[1];
        if (func > SEESAW_SERVO_SPEED)
        {
            SEESAW_DEBUG(F("Requested cuntions out of range: "));
            SEESAW_DEBUGLN(i2cBuffer[1]);
            return;
        }

        uint8_t channel = i2cBuffer[2];
        if (channel >= MODULE_CHANNELS)
        {
            SEESAW_DEBUG(F("Requested channel out of range: "));
            SEESAW_DEBUGLN(channel);
            Wire.write(0xff); // instant reply
            return;
        }

        uint8_t angle = 0;
        switch (func)
        {
        case SEESAW_SERVO_ANGLE:
            angle = (servos[channel].read() & 0x0ff);
            if (angle > 180)
            {
                Wire.write(0xff); // instant reply
            }
            else
            {
                Wire.write(angle); // instant reply
            }
            break;
        case SEESAW_SERVO_SPEED:
            Wire.write(0xff); // instant reply
            break;
        }
    }
    else
    {
        SEESAW_DEBUG(F("Unhandled request cmd 0x"));
        SEESAW_DEBUGLN(i2cBuffer[0], HEX);
    }
}