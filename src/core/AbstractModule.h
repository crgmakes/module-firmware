/**
 * @brief Class for an aquarius module
 * @file AbstractModule.h
 * @date 3 Jan 2026
 * @author cyberreefguru
 */
#pragma once

#include <Arduino.h>
#include <Wire.h>

#include <core/ModuleHardware.h>
#include <core/ModuleSeesaw.h>

/* ======================= Configuration ======================= */

#define EEPROM_I2C_ADDR (EEPROM.length() - 1)

// #define CONFIG_UART_DEBUG 0

#if (CONFIG_UART_DEBUG == 1)
// #define SEESAW_DEBUG(...) SerialVCP.print(__VA_ARGS__)
// #define SEESAW_DEBUGLN(...) SerialVCP.println(__VA_ARGS__)
#define SEESAW_DEBUG(...) Serial.print(__VA_ARGS__)
#define SEESAW_DEBUGLN(...) Serial.println(__VA_ARGS__)

#elif (CONFIG_UART_DEBUG == 0)
#define SEESAW_DEBUG(...)
#define SEESAW_DEBUGLN(...)
#else
#error ("CONFIG_UART_DEBUG must be 0 or 1")
#endif

#define MODULE_PRODUCT_CODE (0xAA00 | MODULE_ADDRESS)

/* ======================= Module class ======================= */

class AbstractModule
{
public:
  AbstractModule();
  virtual ~AbstractModule();

  virtual void initialize();
  virtual void begin();

  void setStatusLed(bool b);
  void setChannelLed(uint8_t channel, bool b);

  uint32_t readChannel(uint8_t channel);

  uint32_t readBulk(uint32_t validpins);

protected:
  uint8_t i2cAddr;
  volatile uint8_t i2cBuffer[32];
  volatile uint8_t receiveLength;

  volatile uint8_t currentCommand = 0;
  volatile uint8_t currentFunction = 0;
  volatile uint8_t currentChannel = 0;

  uint16_t dateCode; // bits represent: DDDDDMMMMYYYYYYYY
  uint32_t version;  // PRODUCT_CODE<<16 | DATE_CODE

  volatile uint32_t bufferedBulkGPIORead;

  const uint8_t ioPins[MODULE_CHANNELS] = IO_PINS;
  const uint8_t ledPins[MODULE_CHANNELS] = LED_PINS;

  void fail();

  void setDateCode();
  void write16(uint16_t value);
  void write32(uint32_t value);

  /* I2C callbacks (must be fast + ISR-safe) */
  virtual void receiveEvent(int howMany);
  virtual void requestEvent();

  virtual void handleReceiveEvent() = 0;
  virtual void handleRequestEvent() = 0;

  /**********************/
  // Handlers for I2C events
  /**********************/

  /**********************/
  /* Receive Handlers   */
  /**********************/
  virtual void handleStatusReceive();
  virtual void handleGpioReceive();

  /**********************/
  /* Request Handlers   */
  /**********************/

  // Base Seesaw
  virtual void handleStatusRequest();
  virtual void handleGpioRequest();

  void dumpBuffer();

private:
  AbstractModule(const AbstractModule &) = delete;
  AbstractModule &operator=(const AbstractModule &) = delete;
};

// end of add your includes here
#ifdef __cplusplus
extern "C"
{
#endif

  extern AbstractModule *module;
  //extern HardwareSerial SerialVCP;

#ifdef __cplusplus
} // extern "C"
#endif
