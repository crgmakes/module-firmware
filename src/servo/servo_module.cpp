/**
 * @brief Main program file for an Aquarius Servo Module
 * @file servo_module.h
 * @date July 5, 2025
 * @author cyberreefguru
 */
#include "servo/ServoModule.h"

void setup()
{
#if CONFIG_UART_DEBUG
  Serial.begin(115200);
  delay(500);
#endif

  module = new ServoModule();

  module->initialize();
  module->begin();
}

void loop()
{
  // Adafruit_seesawPeripheral_run();
  delay(10);
}
