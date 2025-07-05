/**
 * @brief Defines attributes about the modules
 * @file ModuleHardware.h
 * @date June 15, 2025
 * @author cyberreefguru
 */
#pragma once

#define AQUARIUS 1

#define MODULE_SERVO_PRODUCT_CODE 0xAA40
#define MODULE_MOTOR_PRODUCT_CODE 0xAA44
#define MODULE_SWITCH_PRODUCT_CODE 0xAA48
#define MODULE_RELAY_PRODUCT_CODE 0xAA4C
#define MODULE_IR_PRODUCT_CODE 0xAA50
#define MODULE_RF_PRODUCT_CODE 0xAA54
#define MODULE_CURRENT_PRODUCT_CODE 0xAA58
#define MODULE_ENVIRONMENT_PRODUCT_CODE 0xAA5C
#define MODULE_PARTICLE_PRODUCT_CODE 0xAA60

// Each module can have up to 4 different addresses
// set in hardware; A0 and A1 define what is added
// to the base address 0, 1, 3, 4
#define MODULE_SERVO_ADDRESS 0x40 // 1, 2, 3
#define MODULE_MOTOR_ADDRESS 0x44 // 5, 6, 7
#define MODULE_SWITCH_ADDRESS 0x48 // 9, A, B
#define MODULE_RELAY_ADDRESS 0x4C // D, E, F
#define MODULE_IR_ADDRESS 0x50 // 1, 2, 3 
#define MODULE_RF_ADDRESS 0x54 // 5, 6, 7
#define MODULE_CURRENT_ADDRESS 0x58 // 9, A, B
#define MODULE_ENVIRONMENT_ADDRESS 0x5C // D, E, F
#define MODULE_PARTICLE_ADDRESS 0x60 // 1, 2, 3
