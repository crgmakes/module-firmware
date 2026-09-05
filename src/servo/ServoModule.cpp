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

/**
 * @brief initializes servo module
 */
void ServoModule::initialize()
{
    // Call super initialize
    AbstractModule::initialize();

    for (uint8_t i = 0; i < MODULE_CHANNELS; i++)
    {
        servos[i].attach(ioPins[i]);
        set(i, 0); // this needs to be pulled from EEPROM
    }
}

/**
 * @brief sets servo channel to specified value
 * @param channel the channel
 * @param value the value (0-180 degrees)
 */
void ServoModule::set(uint8_t channel, uint8_t value)
{
    if (channel < MODULE_CHANNELS)
    {
        servos[channel].write(value);
        values[channel] = value;
        if (value == 0)
        {
            setChannelLed(channel, false);
        }
        else
        {
            setChannelLed(channel, true);
        }
    }
}

/**
 * @brief handles any data received from the controller. Usually setting a register to a value.
 */
void ServoModule::handleReceiveEvent()
{
    SEESAW_DEBUGLN(F("SRCV"));
    if (i2cBuffer[0] == SEESAW_SERVO_BASE)
    {
        // Stash command, function, and channel
        currentCommand = i2cBuffer[0];
        currentFunction = i2cBuffer[1];
        currentChannel = i2cBuffer[2];

        // if len=3, this is a write for upcoming read
        if (receiveLength == 4)
        {
            if (i2cBuffer[1] == SEESAW_SERVO_ANGLE)
            {
                // Check if channel is out of bounds
                if (currentChannel < MODULE_CHANNELS)
                {
                    uint8_t angle = i2cBuffer[3];
                    set(currentChannel, angle);
                    // servos[currentChannel].write(angle);
                    // values[currentChannel] = angle;

                    SEESAW_DEBUG(F("WANG "));
                    SEESAW_DEBUGLN(angle);
                }
            }
        }
    }
}

/**
 * @brief Handles the controller writing data to us and expecting some sort of response
 */
void ServoModule::handleRequestEvent()
{
    SEESAW_DEBUGLN(F("SRQST"));

    // NOTE: the last receiveEvent filled the current* variables with information about this command
    if (currentCommand == SEESAW_SERVO_BASE)
    {
        if (currentChannel < MODULE_CHANNELS)
        {
            if (currentFunction == SEESAW_SERVO_ANGLE)
            {
                uint8_t angle = 0;
                angle = (servos[currentChannel].read() & 0x0ff);
                SEESAW_DEBUG(F("RANG "));
                SEESAW_DEBUGLN(angle);
                if (angle <= 180)
                {
                    Wire.write(angle); // instant reply
                    return;
                }
            }
        }
    }

    SEESAW_DEBUGLN(F("cmd err"));
    Wire.write(0xff); // instant reply error
}