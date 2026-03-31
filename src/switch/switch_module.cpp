/**
 * @brief Main program file for an Aquarius Relay Module
 * @file relay_module.h
 * @date June 8, 2025
 * @author cyberreefguru
 */
#include "SwitchModule.h"

void setup()
{
#if CONFIG_UART_DEBUG
  Serial.begin(115200);
  delay(500);
#endif

  module = new SwitchModule();

  module->initialize();
  module->begin();
}

void loop()
{
  delay(10);
}
