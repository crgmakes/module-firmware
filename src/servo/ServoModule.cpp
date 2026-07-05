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

    pinMode(SERVO_1_PIN, OUTPUT);
    pinMode(SERVO_2_PIN, OUTPUT);
    pinMode(SERVO_3_PIN, OUTPUT);
    pinMode(SERVO_4_PIN, OUTPUT);

    // Setup hardware
    servos[0].attach(SERVO_1_PIN);
    servos[1].attach(SERVO_2_PIN);
    servos[2].attach(SERVO_3_PIN);
    servos[3].attach(SERVO_4_PIN);

    servos[0].write(0); // this needs to be pulled from EEPROM
    servos[1].write(0); // this needs to be pulled from EEPROM
    servos[2].write(0); // this needs to be pulled from EEPROM
    servos[3].write(0); // this needs to be pulled from EEPROM

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

void ServoModule::set(uint8_t servo, uint8_t value)
{
    switch (servo)
    {
    case 0:
        servos[0].write(value);
        break;
    case 1:
        servos[1].write(value);
        break;
    case 2:
        servos[2].write(value);
        break;
    case 3:
        servos[3].write(value);
        break;
    default:
        break;
    }
    // servos[servo].write(value);
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
            SEESAW_DEBUGLN("2b");
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
                SEESAW_DEBUG(F("channel err: "));
                SEESAW_DEBUGLN(channel);
                return;
            }

            uint8_t angle = i2cBuffer[3];
            servos[channel].write(angle);
            values[channel] = angle;
        }
        else
        {
            // SEESAW_DEBUG(F("Unhandled receive function 0x"));
            // SEESAW_DEBUGLN(i2cBuffer[1], HEX);
        }
    }
    else
    {
        // SEESAW_DEBUG(F("Unhandled receive cmd 0x"));
        // SEESAW_DEBUGLN(i2cBuffer[0], HEX);
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
            // SEESAW_DEBUG(F("Requested cuntions out of range: "));
            // SEESAW_DEBUGLN(i2cBuffer[1]);
            return;
        }

        uint8_t channel = i2cBuffer[2];
        if (channel >= MODULE_CHANNELS)
        {
            // SEESAW_DEBUG(F("Requested channel out of range: "));
            // SEESAW_DEBUGLN(channel);
            // i2c->write(0xff); // instant reply
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
                //i2c->write(0xff); // instant reply
                Wire.write(0xff); // instant reply
            }
            else
            {
                // i2c->write(angle); // instant reply
                Wire.write(angle); // instant reply
            }
            break;
        case SEESAW_SERVO_SPEED:
            // i2c->write(0xff); // instant reply
            Wire.write(0xff); // instant reply
            break;
        }
    }
    else
    {
        // SEESAW_DEBUG(F("Unhandled request cmd 0x"));
        // SEESAW_DEBUGLN(i2cBuffer[0], HEX);
    }
}