/**
 * @brief Class for an aquarius module
 * @file AbstractModule.h
 * @date 3 Jan 2026
 * @author cyberreefguru
 */
#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <wiring_private.h>
#include <pins_arduino.h>
#include <EEPROM.h>

#include <core/ModuleHardware.h>
#include <core/ModuleSeesaw.h>

/* ======================= Configuration ======================= */

#define EEPROM_I2C_ADDR (EEPROM.length() - 1)

#define CONFIG_UART_DEBUG 0

#if (CONFIG_UART_DEBUG == 1)
#define SEESAW_DEBUG(...) Serial.print(__VA_ARGS__)
#define SEESAW_DEBUGLN(...) Serial.println(__VA_ARGS__)
#elif (CONFIG_UART_DEBUG == 0)
#define SEESAW_DEBUG(...)
#define SEESAW_DEBUGLN(...)
#else
#error ("CONFIG_UART_DEBUG must be 0 or 1")
#endif

// #define UART_DEBUG_RXD 6
// #define UART_DEBUG_TXD 7

// /* ======================= GPIO masks ======================= */

// #define ALL_GPIO 0x01FFFFUL
// #define ALL_ADC 0b11100001100111111

// // See: https://github.com/adafruit/Adafruit_seesawPeripheral/pull/14
// //      https://github.com/SpenceKonde/megaTinyCore/blob/master/megaavr/extras/Ref_Timers.md#servo-library
// // TINYX6_PWM_PINS = (4, 5, 6)
// // #define ALL_PWM ((1UL << 6) | (1UL << 7) | (1UL << 8))

// #define PWM_WO_OFFSET 4
// #define ALL_PWM ((1UL << SERVO_1_PIN) | (1UL << SERVO_2_PIN) | (1UL << SERVO_3_PIN))

// #define INVALID_GPIO (((uint32_t)1 << SDA) |               \
//                       ((uint32_t)1 << SCL) |               \
//                       ((uint32_t)1 << UART_DEBUG_RXD) |    \
//                       ((uint32_t)1 << UART_DEBUG_TXD) |    \
//                       ((uint32_t)1 << PIN_PA0) |           \
//                       ((uint32_t)1 << MODULE_ADDR_PIN_0) | \
//                       ((uint32_t)1 << MODULE_ADDR_PIN_1))

// #define VALID_GPIO (ALL_GPIO & ~INVALID_GPIO)
// #define VALID_ADC (ALL_ADC & VALID_GPIO)
// #define VALID_PWM (ALL_PWM & VALID_GPIO)

#define MODULE_PRODUCT_CODE (0xAA00 | MODULE_ADDRESS)

/* ======================= Module class ======================= */

class AbstractModule
{
public:
  AbstractModule();
  virtual ~AbstractModule();

  virtual void initialize();
  virtual void begin();

  uint32_t readBulk(uint32_t validpins);

protected:
  uint8_t i2cAddr;
  volatile uint8_t i2cBuffer[32];
  volatile uint8_t receiveLength;

  uint16_t dateCode; // bits represent: DDDDDMMMMYYYYYYYY
  uint32_t version;  // PRODUCT_CODE<<16 | DATE_CODE

  volatile uint32_t bufferedBulkGPIORead;
  // volatile uint16_t g_bufferedADCRead;
  // volatile uint8_t g_adcStatus;
  // volatile uint8_t g_pwmStatus;

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
  // virtual void handleAdcReceive();
  // virtual void handlePwmReceive();
  // virtual void handleEepromReceive();

  /**********************/
  /* Request Handlers   */
  /**********************/

  // Base Seesaw
  virtual void handleStatusRequest();
  virtual void handleGpioRequest();
  // virtual void handleAdcRequest();
  // virtual void handleEepromRequest();

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

#ifdef __cplusplus
} // extern "C"
#endif
