/**
 * @brief Generic module code
 * @file AbstractModule.cpp
 * @date 3 Jan 2026
 * @author cyberreefguru
 * @note software cribbed from Adafruit and optimized for Aquarius
 * @note this class only handles status and GPIO functions; all others passed to subclass.
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

    version = 0;
    dateCode = 0;

    bufferedBulkGPIORead = 0;
}

/**
 * @brief Deconstructor
 */
AbstractModule::~AbstractModule() {}

void AbstractModule::initialize()
{
    // Disable interrupts
    // cli();
    noInterrupts();

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

    // TODO - put GPIO setup code here?? Or delegate to moduel implementation?

    // uint32_t pins = VALID_GPIO;
    // for (uint8_t pin = 0; pin < 32; pin++)
    // {
    //     if ((pins >> pin) & 0x1)
    //     {
    //         pinMode(pin, INPUT_PULLUP);
    //         digitalWrite(pin, 0);
    //     }
    // }

    setDateCode();

    // Start I2C bus
    Wire.begin(i2cAddr);

    // Re-enable interrupts
    // sei();
    interrupts();

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

    dateCode = day & 0x1F; // top 5 bits are day of month
    dateCode <<= 4;
    dateCode |= month & 0x0F; // middle 4 bits are month
    dateCode <<= 7;
    dateCode |= (year - 2000) & 0x7F; // bottom 7 bits are year

    version = ((uint32_t)MODULE_PRODUCT_CODE) << 16;
    version |= (((uint32_t)dateCode) & 0x0000ffff);
}

/**
 * @brief reads all input ports
 * @param validpins
 * @return returns inputs based on valid pins
 */
// uint32_t AbstractModule::readBulk(uint32_t validpins = VALID_GPIO)
uint32_t AbstractModule::readBulk(uint32_t validpins = 0)
{
    uint32_t temp = 0;

    // read all ports
    // uint8_t port_reads[3] = {0, 0, 0};
    // port_reads[0] = VPORTA.IN;
    // port_reads[1] = VPORTB.IN;
    // port_reads[2] = VPORTC.IN;

    // for (uint8_t pin = 0; pin < 32; pin++)
    // {
    //     temp >>= 1;
    //     if (validpins & 0x1)
    //     {
    //         uint8_t mask = 1 << digital_pin_to_bit_position[pin];
    //         uint8_t port = digital_pin_to_port[pin];
    //         if (port_reads[port] & mask)
    //         {
    //             temp |= 0x80000000UL;
    //         }
    //     }
    //     validpins >>= 1;
    // }
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
 *        written data to us. Either the controller wants to set a value
 *        or whats to prepare for an uncoming read command.
 *        The method handles common commands and then
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
    default:
        handleReceiveEvent();
        break;
    }
}

/**
 * @brief Handles the request event, which means the controller has
 *        written data to us and requests a response. This method
 *        handles common commands and then passes handling off to
 *        module for anything specific.
 * @note the last write fills the buffer used to determine how this request reacts
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
    default:
        handleRequestEvent();
        break;
    }
}

/**
 * @brief handles sending status info back to controller
 */
void AbstractModule::handleStatusReceive()
{
    // The only command we handle is writing a reset command
    // Writing to reset register forces a restart
    if (i2cBuffer[1] == SEESAW_STATUS_SWRST)
    {
        initialize();
    }
}

/**
 * @brief handles sending GPIO info back to the controlelr
 */
void AbstractModule::handleGpioReceive()
{
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
            //bufferedBulkGPIORead = readBulk(VALID_GPIO);
            bufferedBulkGPIORead = readBulk();
        }
        else
        {
            // We have more than 2 bytes received so act on the command data
            uint32_t pinmask = 0x1;
            for (uint8_t pin = 0; pin < 32; pin++)
            {
                // if (VALID_GPIO & pinmask)
                // {
                //     // Set or reset the pin based on value of temp
                //     // 0 = clear (low); 1 = set (high)
                //     digitalWrite(pin, (temp >> pin) & 0x1);
                // }
                // pinmask <<= 1;
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
        //temp &= VALID_GPIO;
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
            } // end if temp
        } // end for
        break;
    }
}

void AbstractModule::handleStatusRequest()
{
    switch (i2cBuffer[1])
    {
    case SEESAW_STATUS_HW_ID:
        Wire.write(MODULE_HW_ID); // instant reply
        break;
    case SEESAW_STATUS_VERSION:
        write32(version); // instant reply
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
        write32(bufferedBulkGPIORead); // instant reply because we did the write before
    }
}
