/**
 * @brief Main program file for an Aquarius Current Module
 * @file current_module.cpp
 * @date Sep 3, 2026
 * @author cyberreefguru
 */
#include "current/CurrentModule.h"

void setup()
{
#if CONFIG_UART_DEBUG
  Serial.setTx(MODULE_TX_PIN);
  Serial.setRx(MODULE_RX_PIN);
  Serial.begin(115200);
  delay(500);
#endif

  SEESAW_DEBUGLN(F("ST"));

#if MODULE_VERSION == 0
    pinMode(LED_BUILTIN, OUTPUT);
#endif

  module = new CurrentModule();
  module->initialize();
  module->begin();

}


void loop()
{
#if MODULE_VERSION == 0
  digitalWrite(LED_BUILTIN, HIGH); // change state of the LED by setting the pin to the HIGH voltage level
  delay(250);                    // wait for a second
  digitalWrite(LED_BUILTIN, LOW); // change state of the LED by setting the pin to the LOW voltage level
  delay(250);                   // wait for a second
#endif

#if MODULE_VERSION == 11
  digitalWrite(LED_STATUS_PIN, HIGH); // change state of the LED by setting the pin to the HIGH voltage level
  delay(250);                    // wait for a second
  digitalWrite(LED_STATUS_PIN, LOW); // change state of the LED by setting the pin to the LOW voltage level
  delay(250);                   // wait for a second
#endif
}
