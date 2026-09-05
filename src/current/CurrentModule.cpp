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

void CurrentModule::sample()
{
    for (uint8_t i = 0; i < MODULE_CHANNELS; i++)
    {
        values[i] = readChannel(i);
    }
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

        // if len=3, this is a write for upcoming read
        if (receiveLength == 2 && currentFunction == SEESAW_CURRENT_BULK)
        {
            currentChannel = 0;
            for (uint8_t i = 0; i < MODULE_CHANNELS; i++)
            {
                values[i] = readChannel(i);
            }
        }
        else if (receiveLength == 3 && currentFunction == SEESAW_CURRENT_CHANNEL)
        {
            currentChannel = i2cBuffer[2];
            values[currentChannel] = readChannel(currentChannel);
            SEESAW_DEBUGLN(values[currentChannel]);
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
    if (currentCommand == SEESAW_CURRENT_BASE)
    {
        if (currentChannel < MODULE_CHANNELS)
        {
            if (currentFunction == SEESAW_CURRENT_CHANNEL)
            {
                write32(values[currentChannel]);
                return;
            }
            else if (currentFunction == SEESAW_CURRENT_BULK)
            {
                for (uint8_t i = 0; i < MODULE_CHANNELS; i++)
                {
                    write32(values[i]);
                }
                return;
            }
        }
    }

    SEESAW_DEBUGLN(F("cmd err"));
    Wire.write(0xff); // instant reply error
}