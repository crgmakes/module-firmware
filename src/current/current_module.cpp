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

  module = new CurrentModule();
  module->initialize();
  module->begin();

}


void loop()
{
  module->setStatusLed(true);
  delay(250);
  module->setStatusLed(false);
  delay(250);
}
