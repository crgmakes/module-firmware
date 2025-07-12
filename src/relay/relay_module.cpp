/**
 * @brief Main program file for an Aquarius Relay Module
 * @file relay_module.h
 * @date June 8, 2025
 * @author cyberreefguru
 */
#include "ModuleHardware.h"

#ifdef AQ_RELAY

// All modules needs these
#define ADDR_PIN_0 PIN_PB4
#define ADDR_PIN_1 PIN_PB5
#define PRODUCT_CODE MODULE_PC_RELAY
#define CONFIG_I2C_PERIPH_ADDR MODULE_ADDRESS_RELAY
#define CONFIG_CHANNELS 1

// This specific module
// #define CONFIG_NEOPIXEL 1
// #define CONFIG_NEOPIXEL_BUF_MAX 4

// #define CONFIG_INTERRUPT_PIN 8
// #define CONFIG_INTERRUPT 1
// #define USE_PINCHANGE_INTERRUPT 1

#include <Adafruit_seesawPeripheral.h>

void setup()
{
#if CONFIG_UART_DEBUG
  Serial.begin(115200);
  delay(500);
#endif

  setChannelCount(1);

  Adafruit_seesawPeripheral_begin();
}

void loop()
{
  Adafruit_seesawPeripheral_run();
}

#endif