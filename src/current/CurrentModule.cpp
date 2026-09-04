/**
 * @brief Class representing a Current Module
 * @file CurrentModule.cpp
 * @date Sep 3, 2026
 * @author cyberreefguru
 */

#include "CurrentModule.h"

CurrentModule::CurrentModule()
{
}

CurrentModule::~CurrentModule()
{
}

void CurrentModule::initialize()
{
    // Call super initialize
    AbstractModule::initialize();

#if MODULE_VERSION == 10
#endif

#if MODULE_VERSION == 11
    pinMode(LED_STATUS_PIN, OUTPUT);
#endif
}

/**
 * @brief handles any data received from the controller. Usually setting a register to a value.
 */
void CurrentModule::handleReceiveEvent()
{
    SEESAW_DEBUGLN(F("SRCV"));
    if (i2cBuffer[0] == SEESAW_CURRENT_BASE)
    {
        // Stash command, function, and channel
        currentCommand = i2cBuffer[0];
        currentFunction = i2cBuffer[1];
        currentChannel = i2cBuffer[2];

        // if len=3, this is a write for upcoming read
        if (receiveLength == 3)
        {
            if (i2cBuffer[1] == SEESAW_CURRENT_VALUE)
            {
                // Check if channel is out of bounds
                if (currentChannel < MODULE_CHANNELS)
                {
                    setChannelLed( currentChannel, true);
                    values[currentChannel] = readChannel(currentChannel);
                    setChannelLed( currentChannel, false);
                    
                    SEESAW_DEBUGLN(values[currentChannel]);
                }
            }
        }
    }
}

/**
 * @brief Handles the controller writing data to us and expecting some sort of response
 */
void CurrentModule::handleRequestEvent()
{
    SEESAW_DEBUGLN(F("SRQST"));

    // NOTE: the last receiveEvent filled the current* variables with information about this command
    if (currentCommand == SEESAW_SERVO_BASE)
    {
        if (currentChannel < MODULE_CHANNELS)
        {
            if (currentFunction == SEESAW_CURRENT_VALUE)
            {
                write32(values[currentChannel]);
                return;
            }
        }
    }

    SEESAW_DEBUGLN(F("cmd err"));
    Wire.write(0xff); // instant reply error
}