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

    for (uint8_t i = 0; i < MODULE_CHANNELS; i++)
    {
        servos[i].attach(ioPins[i]);
        set(i, 0); // this needs to be pulled from EEPROM
    }

    // pinMode(IO_1_PIN, OUTPUT);
    // pinMode(IO_2_PIN, OUTPUT);
    // pinMode(IO_3_PIN, OUTPUT);
    // pinMode(IO_4_PIN, OUTPUT);

    // // Setup hardware
    // servos[0].attach(IO_1_PIN);
    // servos[1].attach(IO_2_PIN);
    // servos[2].attach(IO_3_PIN);
    // servos[3].attach(IO_4_PIN);

    // servos[0].write(0); // this needs to be pulled from EEPROM
    // servos[1].write(0); // this needs to be pulled from EEPROM
    // servos[2].write(0); // this needs to be pulled from EEPROM
    // servos[3].write(0); // this needs to be pulled from EEPROM

    // Servo* s= new Servo();
    // s->attach(PA6);
    // s->write(0);

    // delay(2000);
    // for(uint8_t i=0;i<181; i+=10)
    // {
    //     s->write(i);
    //     delay(100);
    // }
    // delay(2000);
    // s->write(0);
}

void ServoModule::set(uint8_t channel, uint8_t value)
{
    if (channel < MODULE_CHANNELS)
    {
        servos[channel].write(value);
        values[currentChannel] = value;
        if (value == 0)
        {
            setChannelLed(channel, false);
        }
        else
        {
            setChannelLed(channel, true);
        }
    }
    // switch (channel)
    // {
    // case 0:
    //     servos[0].write(value);
    //     break;
    // case 1:
    //     servos[1].write(value);
    //     break;
    // case 2:
    //     servos[2].write(value);
    //     break;
    // case 3:
    //     servos[3].write(value);
    //     break;
    // default:
    //     break;
    // }
    // servos[servo].write(value);
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