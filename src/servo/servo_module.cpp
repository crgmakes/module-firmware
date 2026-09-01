/**
 * @brief Main program file for an Aquarius Servo Module
 * @file servo_module.h
 * @date July 5, 2025
 * @author cyberreefguru
 */
#include "servo/ServoModule.h"

uint8_t value = 0;
// HardwareSerial SerialVCP(PA3, PA2); // RX, TX

void setup()
{
#if CONFIG_UART_DEBUG
  Serial.setTx(MODULE_TX_PIN); 
  Serial.setRx(MODULE_RX_PIN);
  // Serial.setTx(PA2); 
  // Serial.setRx(PA3);
  Serial.begin(115200);
  delay(500);
#endif

  SEESAW_DEBUGLN(F("ST"));

  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);

  module = new ServoModule();

  module->initialize();
  module->begin();

  ((ServoModule*)module)->set(0, 180);
  delay(1000);
  ((ServoModule*)module)->set(0, 0);

}

void loop()
{
  // Adafruit_seesawPeripheral_run();
  //digitalWrite(LED_BUILTIN, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  digitalWrite(LED_1_PIN, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  delay(250);                      // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  digitalWrite(LED_1_PIN, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  delay(250);                      // wait for a second
}
