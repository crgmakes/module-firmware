/**
 * @brief Class representing a servo module
 * @file GpioModule.cpp
 * @date 4 Jan 2026
 * @author cyberreefguru
 */

#include "GpioModule.h"

GpioModule::GpioModule()
{
}

GpioModule::~GpioModule()
{
}

void GpioModule::initialize()
{
    // Call super initialize
    AbstractModule::initialize();

    // Setup hardware from flash??
}

void GpioModule::handleReceiveEvent()
{
    if (i2cBuffer[0] != SEESAW_GPIO_BASE)
    {
        return;
    }

    if (receiveLength != 6)
    {
        // Not a valid command or a read/write combo
        return;
    }

    // All GPIO commands must have a 4 byte payload indicating
    // the pins or GPIO that should be affected.
    // Build single 32-bit variable representing the pins
    uint32_t temp = 0;
    temp = i2cBuffer[2];
    temp <<= 8;
    temp |= i2cBuffer[3];
    temp <<= 8;
    temp |= i2cBuffer[4];
    temp <<= 8;
    temp |= i2cBuffer[5];

    if (i2cBuffer[1] == SEESAW_GPIO_BULK)
    {
        // Bulk set the GPIO pin values
        uint32_t pinmask = 0x1;
        for (uint8_t pin = 0; pin < 32; pin++)
        {
            if (VALID_GPIO & pinmask)
            {
                // Set or reset the pin based on value of temp
                // 0 = clear (low); 1 = set (high)
                digitalWrite(pin, (temp >> pin) & 0x1);
            }
            pinmask <<= 1;
        }
    }
    else
    {
        temp &= VALID_GPIO;
        for (uint8_t pin = 0; pin < 32; pin++)
        {
            if ((temp >> pin) & 0x1)
            {
                SEESAW_DEBUG(F("Set pin "));
                SEESAW_DEBUG(pin);
                switch (i2cBuffer[1])
                {
                case SEESAW_GPIO_DIRSET_BULK:
                    pinMode(pin, OUTPUT);
                    SEESAW_DEBUGLN(F(" OUTPUT"));
                    break;

                case SEESAW_GPIO_DIRCLR_BULK:
                    pinMode(pin, INPUT);
                    SEESAW_DEBUGLN(F(" INPUT"));
                    break;

                case SEESAW_GPIO_BULK_SET:
                    digitalWrite(pin, 1);
                    SEESAW_DEBUGLN(F(" HIGH"));
                    break;

                case SEESAW_GPIO_BULK_CLR:
                    digitalWrite(pin, 0);
                    SEESAW_DEBUGLN(F(" LOW"));
                    break;

                case SEESAW_GPIO_PULLENSET:
                    pinMode(pin, INPUT_PULLUP);
                    SEESAW_DEBUGLN(F(" PULL"));
                    break;

                case SEESAW_GPIO_PULLENCLR:
                    pinMode(pin, INPUT);
                    SEESAW_DEBUGLN(F(" NOPULL"));
                    break;
                default:
                    SEESAW_DEBUGLN(F(" UNKNOWN"));
                    break;
                }
            }
        }
    }
}

void GpioModule::handleRequestEvent()
{
    if (i2cBuffer[0] != SEESAW_GPIO_BASE)
    {
        return;
    }

    if (i2cBuffer[1] == SEESAW_GPIO_BULK)
    {
        bufferedBulkGPIORead = readBulk(VALID_GPIO);
        write32(bufferedBulkGPIORead);
    }
}
