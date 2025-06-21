#include "ModuleHardware.h"

#define PRODUCT_CODE            MODULE_RELAY_PRODUCT_CODE
#define CONFIG_I2C_PERIPH_ADDR  MODULE_RELAY_ADDRESS
#define CONFIG_CHANNELS 1

// #define CONFIG_INTERRUPT_PIN 8
// #define CONFIG_INTERRUPT 1
// #define USE_PINCHANGE_INTERRUPT 1

#include <Adafruit_seesawPeripheral.h>


void setup() {
#if CONFIG_UART_DEBUG
  Serial.begin(115200);
  delay(500);
#endif

  setChannelCount(1);
 
  Adafruit_seesawPeripheral_begin();
}


void loop() {
  Adafruit_seesawPeripheral_run();
}