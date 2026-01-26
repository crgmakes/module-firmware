/**
 * @brief Main program file for an Aquarius GPIO Module
 * @file gpio_module.h
 * @date Jan 26, 2026
 * @author cyberreefguru
 */
#include "gpio/GpioModule.h"

void setup()
{
#if CONFIG_UART_DEBUG
  Serial.begin(115200);
  delay(500);
#endif

  module = new GpioModule();

  module->initialize();
  module->begin();
}

void loop()
{
  delay(10);
}
