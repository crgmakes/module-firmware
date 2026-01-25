/**
 * @brief Generic module code
 * @file AbstractModule.cpp
 * @date 3 Jan 2026
 * @author cyberreefguru
 * @note software cribbed from Adafruit and optimized for Aquarius
 */
#include "AbstractModule.h"

AbstractModule *module;

/**
 * @brief Constructor
 */
AbstractModule::AbstractModule()
{
    i2cAddr = 0;
    memset((void *)i2cBuffer, 0, sizeof(i2cBuffer));
    receiveLength = 0;

    gVersion = 0;
    gDateCode = 0;

    g_bufferedBulkGPIORead = 0;
    // g_bufferedADCRead = 0;
    // g_adcStatus = 0;
    // g_pwmStatus = 0;
}

/**
 * @brief Deconstructor
 */
AbstractModule::~AbstractModule() {}

void AbstractModule::initialize()
{
    // Disable interruprs
    cli();

    // End any pending wire initialization/transmission
    Wire.end();

    // Set address bits to input
    pinMode(MODULE_ADDR_PIN_0, INPUT_PULLUP);
    pinMode(MODULE_ADDR_PIN_1, INPUT_PULLUP);

    // Figure out what our I2C address is
    i2cAddr = MODULE_ADDRESS;

    uint8_t p = digitalReadFast(MODULE_ADDR_PIN_0);
    p |= (digitalReadFast(MODULE_ADDR_PIN_1) << 1);
    p = (~p & 0x03); // invert active low address bits
    i2cAddr += p;    // add to base address

    SEESAW_DEBUG(F("I2C 0x"));
    SEESAW_DEBUGLN(i2cAddr, HEX);

    uint32_t pins = VALID_GPIO;
    for (uint8_t pin = 0; pin < 32; pin++)
    {
        if ((pins >> pin) & 0x1)
        {
            pinMode(pin, INPUT);
            digitalWrite(pin, 0);
        }
    }

    // g_pwmStatus = 0;

    // // TCA0 is used for 16 bit PWM support
    // takeOverTCA0();
    // PORTMUX.CTRLC |= 0b111;   // Alternate WOx output pin locations
    // TCA0.SINGLE.PER = 0xFFFF; // Set TOP to MAX
    // TCA0.SINGLE.CTRLB = 0x03; // Single-slope PWM, WG outputs off
    // TCA0.SINGLE.CTRLD = 0x00; // Disable Split Mode
    // TCA0.SINGLE.CTRLA = 0x01; // Enable TCA0 peripheral

    // #if CONFIG_UART
    //   CONFIG_UART_SERCOM.begin(g_uart_baud);
    // #endif

    setDateCode();

    // Start I2C bus
    Wire.begin(i2cAddr);

    // Re-enable interrupts
    sei();
}

void AbstractModule::begin()
{
    Wire.onReceive([](int howMany)
                   {
                       module->receiveEvent(howMany); // receive events
                   });

    Wire.onRequest([]()
                   {
                       module->requestEvent(); // request events
                   });
}

/**
 * @brief Sets the date the software was compiled
 *
 */
void AbstractModule::setDateCode()
{
    char buf[12];
    char *bufp = buf;
    int month = 0, day = 0, year = 2000;
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

    memset((void *)buf, 0, 12);

    // __DATE__ format: 'Mmm dd yyyy'
    strncpy(buf, __DATE__, 11);

    buf[3] = 0; // null terminator after month
    buf[6] = 0; // null terminator after day
    buf[11] = 0; // null terminator after year

    month = (strstr(month_names, buf) - month_names) / 3 + 1;
    day = atoi(buf + 4);
    year = atoi(buf + 7);

    gDateCode = day & 0x1F; // top 5 bits are day of month
    gDateCode <<= 4;
    gDateCode |= month & 0x0F; // middle 4 bits are month
    gDateCode <<= 7;
    gDateCode |= (year - 2000) & 0x7F; // bottom 7 bits are year

    gVersion = ((uint32_t)MODULE_PRODUCT_CODE) << 16;
    gVersion |= (((uint32_t)gDateCode) & 0x0000ffff);
}

/**
 * @brief reads all input ports
 * @param validpins
 * @return returns inputs based on valid pins
 */
uint32_t AbstractModule::readBulk(uint32_t validpins = VALID_GPIO)
{
    uint32_t temp = 0;

    // read all ports
    uint8_t port_reads[3] = {0, 0, 0};
    port_reads[0] = VPORTA.IN;
    port_reads[1] = VPORTB.IN;
    port_reads[2] = VPORTC.IN;

    for (uint8_t pin = 0; pin < 32; pin++)
    {
        temp >>= 1;
        if (validpins & 0x1)
        {
            uint8_t mask = 1 << digital_pin_to_bit_position[pin];
            uint8_t port = digital_pin_to_port[pin];
            if (port_reads[port] & mask)
            {
                temp |= 0x80000000UL;
            }
        }
        validpins >>= 1;
    }
    return temp;
}

/**
 * @brief writes 16-bit value to I2C bus
 * @param value the value to write
 */
void AbstractModule::write16(uint16_t value)
{
    Wire.write(value >> 8);
    Wire.write(value);
}

/**
 * @brief writes 32-bit value to I2C bus
 * @param value the value to write
 */
void AbstractModule::write32(uint32_t value)
{
    Wire.write(value >> 24);
    Wire.write(value >> 16);
    Wire.write(value >> 8);
    Wire.write(value);
}

/**
 * @brief Handles the receive event, which means the controller has
 *        written data to us. The method handles common commands and then
 *        passes handling off to module for anything specific.
 * @param howMany how many bytes received
 * @note this is an ISR
 */
void AbstractModule::receiveEvent(int howMany)
{
    SEESAW_DEBUG(F("Received "));
    SEESAW_DEBUG(howMany);
    SEESAW_DEBUG(F(" bytes:"));

    // return if buffer too small
    if ((uint32_t)howMany > sizeof(i2cBuffer))
    {
        SEESAW_DEBUG(F("Too many bytes received"));
        return;
    }

    // clear buffer
    memset((void *)i2cBuffer, 0, sizeof(i2cBuffer));
    receiveLength = howMany;

    // Read the data
    for (uint8_t i = 0; i < receiveLength; i++)
    {
        i2cBuffer[i] = Wire.read();
    }

    switch (i2cBuffer[0])
    {
    case SEESAW_STATUS_BASE:
        handleStatusReceive();
        break;
    case SEESAW_GPIO_BASE:
        handleGpioReceive();
        break;
    // case SEESAW_ADC_BASE:
    //     handleAdcReceive();
    //     break;
    // case SEESAW_TIMER_BASE:
    //     handlePwmReceive();
    //     break;
    // case SEESAW_EEPROM_BASE:
    //     handleEepromReceive();
    //     break;
    // case SEESAW_SERVO_BASE:
    //     handleServoReceive();
    //     break;
    // case SEESAW_MOTOR_BASE:
    //     handleMotorReceive();
    //     break;
    // case SEESAW_RELAY_BASE:
    //     handleRelayReceive();
    //     break;
    // case SEESAW_IR_BASE:
    //     handleIrReceive();
    //     break;
    // case SEESAW_RF_BASE:
    //     handleRfReceive();
    //     break;
    // case SEESAW_CURRENT_BASE:
    //     handleCurrentReceive();
    //     break;
    // case SEESAW_DISTANCE_BASE:
    //     handleDistanceReceive();
    //     break;
    // case SEESAW_PARTICLE_BASE:
    //     handleServoReceive();
    //     break;
    // case SEESAW_ENVIRONMENT_BASE:
    //     handleServoReceive();
    //     break;
    default:
        handleReceiveEvent();
        break;
    }
}

/**
 * @brief Handles the request event, which means the controller has
 *        written data to us and expects a response. This method
 *        handles common commands and then passes handling off to
 *        module for anything specific.
 */
void AbstractModule::requestEvent()
{
    SEESAW_DEBUGLN(F("Requesting data"));

    switch (i2cBuffer[0])
    {
    case SEESAW_STATUS_BASE:
        handleStatusRequest();
        break;
    case SEESAW_GPIO_BASE:
        handleGpioRequest();
        break;
    // case SEESAW_ADC_BASE:
    //     handleAdcRequest();
    //     break;
    // case SEESAW_EEPROM_BASE:
    //     handleEepromRequest();
    //     break;
    // case SEESAW_SERVO_BASE:
    //     handleServoRequest();
    //     break;
    // case SEESAW_MOTOR_BASE:
    //     handleMotorRequest();
    //     break;
    // case SEESAW_RELAY_BASE:
    //     handleRelayRequest();
    //     break;
    // case SEESAW_IR_BASE:
    //     handleIrRequest();
    //     break;
    // case SEESAW_RF_BASE:
    //     handleRfRequest();
    //     break;
    // case SEESAW_CURRENT_BASE:
    //     handleCurrentRequest();
    //     break;
    // case SEESAW_DISTANCE_BASE:
    //     handleDistanceRequest();
    //     break;
    // case SEESAW_PARTICLE_BASE:
    //     handleServoRequest();
    //     break;
    // case SEESAW_ENVIRONMENT_BASE:
    //     handleServoRequest();
    //     break;
    default:
        handleRequestEvent();
        break;
    }

    // uint8_t base_cmd = i2cBuffer[0];
    // uint8_t module_cmd = i2cBuffer[1];

    // if (base_cmd == SEESAW_STATUS_BASE)
    // {
    //     switch (module_cmd)
    //     {
    //     case SEESAW_STATUS_HW_ID:
    //         Wire.write(SEESAW_HW_ID); // instant reply
    //         break;
    //     case SEESAW_STATUS_VERSION:
    //         write32(version); // instant reply
    //         break;
    //     case SEESAW_STATUS_COUNT:
    //         Wire.write(channelCount);
    //         break;
    //     }
    // }
    // else if (base_cmd == SEESAW_GPIO_BASE)
    // {
    //     if (module_cmd == SEESAW_GPIO_BULK)
    //     {
    //         write32(g_bufferedBulkGPIORead); // instant reply because we did the write before
    //     }
    // }
    // else if (base_cmd == SEESAW_ADC_BASE)
    // {
    //     if (module_cmd >= SEESAW_ADC_CHANNEL_OFFSET)
    //     {
    //         Wire.write(g_bufferedADCRead >> 8);
    //         Wire.write(g_bufferedADCRead);
    //     }
    //     else if (module_cmd == SEESAW_ADC_STATUS)
    //     {
    //         Wire.write(g_adcStatus);
    //     }
    // }
    // else if (base_cmd == SEESAW_EEPROM_BASE)
    // {

    //     Wire.write(EEPROM.read(module_cmd % EEPROM.length()));
    // }
    // else
    // {
    //     SEESAW_DEBUG(F("Unhandled cmd 0x"));
    //     SEESAW_DEBUGLN(base_cmd, HEX);
    // }
}

void AbstractModule::handleStatusReceive()
{
    // The only command we handle is reset
    // Writing to reset register forces a restart
    if (i2cBuffer[1] == SEESAW_STATUS_SWRST)
    {
        initialize();
    }
}

void AbstractModule::handleGpioReceive()
{
    // All GPIO commands must have a 4 byte payload indicating
    // the pins or GPIO that should be affected.
    // Build single 32-bit variable representing the pins
    uint32_t temp;
    temp = i2cBuffer[2];
    temp <<= 8;
    temp |= i2cBuffer[3];
    temp <<= 8;
    temp |= i2cBuffer[4];
    temp <<= 8;
    temp |= i2cBuffer[5];

    switch (i2cBuffer[1])
    {
    case SEESAW_GPIO_BULK:
        if (receiveLength == 2)
        {
            // This is a little awkward, but works -- this "receive" is the command to
            // return the values of the GPIO. However, this is the write phase of the
            // command (to the client), not the actual read phase (where the controller expects
            // the values to be returned). Generally one would just put the read of the ports in the
            // code segment where the write (to the controller) happens. I may move it
            // in the future to be less confusing.

            // we're about to request the data next so we'll do the read now
            g_bufferedBulkGPIORead = readBulk(VALID_GPIO);
        }
        else
        {
            // We have more than 2 bytes received so act on the command data
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
        break;
    case SEESAW_GPIO_DIRSET_BULK:
    case SEESAW_GPIO_DIRCLR_BULK:
    case SEESAW_GPIO_BULK_SET:
    case SEESAW_GPIO_BULK_CLR:
    case SEESAW_GPIO_PULLENSET:
    case SEESAW_GPIO_PULLENCLR:
    case SEESAW_GPIO_INTENSET:
        temp &= VALID_GPIO;
        for (uint8_t pin = 0; pin < 32; pin++)
        {
            if ((temp >> pin) & 0x1)
            {
                // SEESAW_DEBUG(F("Set pin "));
                // SEESAW_DEBUG(pin);
                switch (i2cBuffer[1])
                {
                case SEESAW_GPIO_DIRSET_BULK:
                    pinMode(pin, OUTPUT);
                    // SEESAW_DEBUGLN(F(" OUTPUT"));
                    break;

                case SEESAW_GPIO_DIRCLR_BULK:
                    pinMode(pin, INPUT);
                    // SEESAW_DEBUGLN(F(" INPUT"));
                    break;

                case SEESAW_GPIO_BULK_SET:
                    digitalWrite(pin, 1);
                    // SEESAW_DEBUGLN(F(" HIGH"));
                    break;

                case SEESAW_GPIO_BULK_CLR:
                    digitalWrite(pin, 0);
                    // SEESAW_DEBUGLN(F(" LOW"));
                    break;

                case SEESAW_GPIO_PULLENSET:
                    pinMode(pin, INPUT_PULLUP);
                    // SEESAW_DEBUGLN(F(" PULL"));
                    break;

                case SEESAW_GPIO_PULLENCLR:
                    pinMode(pin, INPUT);
                    // SEESAW_DEBUGLN(F(" NOPULL"));
                    break;
                default:
                    // Optional: handle unknown commands
                    break;
                }
            }
        }
    }
}

// void AbstractModule::handleAdcReceive()
// {
//     if (i2cBuffer[1] >= SEESAW_ADC_CHANNEL_OFFSET)
//     {
//         uint8_t adcpin = i2cBuffer[1] - SEESAW_ADC_CHANNEL_OFFSET;
//         if (!((VALID_ADC) & (1UL << adcpin)))
//         {
//             g_adcStatus = 0x1; // error, invalid pin!
//         }
//         else
//         {
//             // its valid!
//             // SEESAW_DEBUG(F("ADC read "));
//             // SEESAW_DEBUG(adcpin);
//             // SEESAW_DEBUG(F(": "));
//             g_bufferedADCRead = analogRead(adcpin);
//             // SEESAW_DEBUGLN(g_bufferedADCRead);
//             g_adcStatus = 0x0;
//         }
//     }
// }

// void AbstractModule::handlePwmReceive()
// {
//     uint8_t pin = i2cBuffer[2];
//     uint16_t value = i2cBuffer[3];
//     value <<= 8;
//     value |= i2cBuffer[4];
//     if (!(VALID_PWM & (1UL << pin)))
//     {
//         g_pwmStatus = 0x1; // error, invalid pin!
//     }
//     else if (i2cBuffer[1] == SEESAW_TIMER_PWM)
//     {
//         // its valid!
//         SEESAW_DEBUG(F("PWM "));
//         SEESAW_DEBUG(pin);
//         SEESAW_DEBUG(F(": "));
//         SEESAW_DEBUGLN(value);

//         pinMode(pin, OUTPUT);
//         // set duty cycle via CMPx
//         uint16_t duty_cycle = map(value, 0, 0xFFFF, 0, TCA0.SINGLE.PER);
//         pin -= PWM_WO_OFFSET;
//         if (pin == 0)
//         {
//             TCA0.SINGLE.CTRLB |= TCA_SINGLE_CMP2EN_bm;
//             TCA0.SINGLE.CMP2 = duty_cycle;
//         }
//         else if (pin == 1)
//         {
//             TCA0.SINGLE.CTRLB |= TCA_SINGLE_CMP1EN_bm;
//             TCA0.SINGLE.CMP1 = duty_cycle;
//         }
//         else if (pin == 2)
//         {
//             TCA0.SINGLE.CTRLB |= TCA_SINGLE_CMP0EN_bm;
//             TCA0.SINGLE.CMP0 = duty_cycle;
//         }
//         g_pwmStatus = 0x0;
//     }
//     else if (i2cBuffer[1] == SEESAW_TIMER_FREQ)
//     {
//         SEESAW_DEBUG(F("Freq "));
//         SEESAW_DEBUG(pin);
//         SEESAW_DEBUG(F(": "));
//         SEESAW_DEBUGLN(value);
//         pinMode(pin, OUTPUT);

//         // set frequency via CLKSEL and PER based on F_CPU
//         // NOTE: changes all PWM outputs
//         uint8_t clksel = 0;
//         unsigned long period = (F_CPU / value);
//         while (period > 65536 && clksel < 7)
//         {
//             clksel++;
//             period = period >> (clksel > 4 ? 2 : 1);
//         }
//         TCA0.SINGLE.CTRLA = (clksel << 1) | TCA_SINGLE_ENABLE_bm;
//         TCA0.SINGLE.PER = period;
//         g_pwmStatus = 0x0;
//     }
// }

// void AbstractModule::handleEepromReceive()
// {
//     // special case for 1 byte at -1 (i2c addr)
//     if ((i2cBuffer[1] == 0xFF) && (receiveLength == 3))
//     {
//         EEPROM.write(EEPROM.length() - 1, i2cBuffer[2]);
//     }
//     else
//     {
//         // write the data
//         for (uint8_t i = 0; i < receiveLength - 2; i++)
//         {
//             if ((i2cBuffer[1] + i) < EEPROM.length())
//             {
//                 EEPROM.write(i2cBuffer[1] + i, i2cBuffer[2 + i]);
//                 SEESAW_DEBUG(F("EEP $"));
//                 SEESAW_DEBUG(module_cmd + i, HEX);
//                 SEESAW_DEBUG(F(" <- 0x"));
//                 SEESAW_DEBUGLN(i2cBuffer[2 + i], HEX);
//             }
//         }
//     }
// }

void AbstractModule::handleStatusRequest()
{
    switch (i2cBuffer[1])
    {
    case SEESAW_STATUS_HW_ID:
        Wire.write(MODULE_HW_ID); // instant reply
        break;
    case SEESAW_STATUS_VERSION:
        write32(gVersion); // instant reply
        break;
    case SEESAW_STATUS_COUNT:
        Wire.write(MODULE_CHANNELS); // instant reply
        break;
    }
}

void AbstractModule::handleGpioRequest()
{
    if (i2cBuffer[1] == SEESAW_GPIO_BULK)
    {
        write32(g_bufferedBulkGPIORead); // instant reply because we did the write before
    }
}

// void AbstractModule::handleAdcRequest()
// {
//     if (i2cBuffer[1] >= SEESAW_ADC_CHANNEL_OFFSET)
//     {
//         Wire.write(g_bufferedADCRead >> 8);
//         Wire.write(g_bufferedADCRead);
//     }
//     else if (i2cBuffer[1] == SEESAW_ADC_STATUS)
//     {
//         Wire.write(g_adcStatus);
//     }
// }

// void AbstractModule::handleEepromRequest()
// {
//     Wire.write(EEPROM.read(i2cBuffer[1] % EEPROM.length()));
// }
