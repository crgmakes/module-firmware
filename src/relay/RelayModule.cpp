/**
 * @brief Class representing a relay module
 * @file RelayModule.cpp
 * @date 26 Jan 2026
 * @author cyberreefguru
 */

#include "RelayModule.h"

RelayModule::RelayModule()
{
}

RelayModule::~RelayModule()
{
}

void RelayModule::initialize()
{
    // Call super initialize
    AbstractModule::initialize();

    // Setup hardware
    // TODO - figure out how to do this using channel count
    relays[0].initialize(RELAY_1_PIN);
}

/**
 * @brief Handles write commands from the host
 */
void RelayModule::handleReceiveEvent()
{
    // NOTE - it actually uses less memory to make these local 
    //        and not use the pointer to an array
    uint8_t command = i2cBuffer[0];
    uint8_t reg = i2cBuffer[1];
    
    if (command != SEESAW_RELAY_BASE)
    {
        return;
    }

    if (receiveLength < 3 || receiveLength > 5)
    {
        // Not a valid command or a read/write combo
        return;
    }

    if (reg == SEESAW_RELAY_BULK)
    {
        uint8_t value = i2cBuffer[2];
        for (uint8_t index = 0; index < MODULE_CHANNELS; index++)
        {
            relays[index].set(((value >> index) & 0x1));
        }
    }
    else if (reg == SEESAW_RELAY_CHANNEL)
    {
        uint8_t channel = i2cBuffer[2];
        uint8_t value = i2cBuffer[3];
        if( channel >= MODULE_CHANNELS)
        {
            return;
        }
        relays[channel].set( value );
    }
}

void RelayModule::handleRequestEvent()
{
    uint8_t command = i2cBuffer[0];
    uint8_t reg = i2cBuffer[1];
    if (command != SEESAW_RELAY_BASE)
    {
        return;
    }

    if (reg == SEESAW_RELAY_BULK)
    {
        uint8_t temp = 0;
        for (uint8_t index = 0; index < MODULE_CHANNELS; index++)
        {
            temp |= ( (relays[index].get() & 0x01) << index);
        }
        Wire.write(temp);
    }
    else if (reg == SEESAW_RELAY_CHANNEL)
    {
        uint8_t channel = i2cBuffer[2];
        if( channel >= MODULE_CHANNELS)
        {
            return;
        }
        Wire.write( relays[channel].get() & 0x01 );
    }
}

Relay::Relay()
{
}

void Relay::initialize(uint8_t pin)
{
    pinMode(pin, OUTPUT);

    // TODO - get state from flash
    digitalWrite(pin, 0);
}

void Relay::set(bool b)
{
    digitalWrite(pin, b);
}

bool Relay::get()
{
    return digitalRead(pin);
}
