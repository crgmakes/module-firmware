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

  pinMode(LED_BUILTIN, OUTPUT);

  module = new ServoModule();

  module->initialize();
  module->begin();
}

void loop()
{
  // Adafruit_seesawPeripheral_run();
  digitalWrite(LED_BUILTIN, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  delay(750);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  delay(750);                      // wait for a second
}
