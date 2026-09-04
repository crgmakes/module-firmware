/**
 * @brief Main program file for an Aquarius Servo Module
 * @file servo_module.h
 * @date July 5, 2025
 * @author cyberreefguru
 */
#include "servo/ServoModule.h"

// uint8_t value = 0;
// HardwareSerial SerialVCP(PA3, PA2); // RX, TX

void setup()
{
#if CONFIG_UART_DEBUG
  Serial.setTx(MODULE_TX_PIN);
  Serial.setRx(MODULE_RX_PIN);
  Serial.begin(115200);
  // delay(500);
#endif

  SEESAW_DEBUGLN(F("ST"));

#if MODULE_VERSION == 0
  pinMode(LED_BUILTIN, OUTPUT);
#endif

#if MODULE_VERSION == 11
    pinMode(LED_STATUS_PIN, OUTPUT);
#endif

  module = new ServoModule();

  module->initialize();
  module->begin();

  ((ServoModule *)module)->set(0, 180);
  delay(1000);
  ((ServoModule *)module)->set(0, 0);
}

void loop()
{
#if MODULE_VERSION == 0
  digitalWrite(LED_BUILTIN, HIGH); // change state of the LED by setting the pin to the HIGH voltage level
  delay(250);                    // wait for a second
  digitalWrite(LED_BUILTIN, LOW); // change state of the LED by setting the pin to the LOW voltage level
  delay(250);                   // wait for a second
#endif

#if MODULE_VERSION == 10
  module->setChannelLed(3, true);
  // digitalWrite(LED_1_PIN, HIGH); // change state of the LED by setting the pin to the HIGH voltage level
  delay(250);                    // wait for a second
  module->setChannelLed(3, false);
  // digitalWrite(LED_1_PIN, LOW); // change state of the LED by setting the pin to the LOW voltage level
  delay(250);                   // wait for a second
#endif


#if MODULE_VERSION == 11
  digitalWrite(LED_STATUS_PIN, HIGH); // change state of the LED by setting the pin to the HIGH voltage level
  delay(250);                    // wait for a second
  digitalWrite(LED_STATUS_PIN, LOW); // change state of the LED by setting the pin to the LOW voltage level
  delay(250);                   // wait for a second
#endif
}
