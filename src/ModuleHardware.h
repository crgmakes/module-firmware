/**
 * @brief Defines attributes about the modules
 * @file ModuleHardware.h
 * @date June 15, 2025
 * @author cyberreefguru
 */
#pragma once

#define AQUARIUS 1

// Each module can have up to 4 different addresses
// set in hardware; A0 and A1 on the board define 
// how much is added to the base address 0, 1, 3, 4
#define MODULE_BASE_ADDRESS 0x30 // 0, 1, 2, 3
#define MODULE_ADDRESS_SERVO MODULE_BASE_ADDRESS // 0, 1, 2, 3
#define MODULE_ADDRESS_MOTOR (MODULE_ADDRESS_SERVO+0x04) // 4, 5, 6, 7
#define MODULE_ADDRESS_SWITCH (MODULE_ADDRESS_MOTOR+0x04) // 8, 9, A, B
#define MODULE_ADDRESS_RELAY (MODULE_ADDRESS_SWITCH+0x04) // C, D, E, F
#define MODULE_ADDRESS_IR (MODULE_ADDRESS_RELAY+0x04) // 0, 1, 2, 3 (0x40)
#define MODULE_ADDRESS_RF (MODULE_ADDRESS_IR+0x04) // 4, 5, 6, 7
#define MODULE_ADDRESS_CURRENT (MODULE_ADDRESS_RF+0x04) // 8, 9, A, B
#define MODULE_ADDRESS_ENVIRONMENT (MODULE_ADDRESS_CURRENT+0x04) // C, D, E, F
#define MODULE_ADDRESS_PARTICLE (MODULE_ADDRESS_ENVIRONMENT+0x04) // 0, 1, 2, 3 (0x50)

#define MODULE_PC_SERVO (uint16_t)((0x00AA<<16) | (MODULE_ADDRESS_SERVO))
#define MODULE_PC_MOTOR (uint16_t)((0x00AA<<16) | (MODULE_ADDRESS_MOTOR))
#define MODULE_PC_SWITCH (uint16_t)((0x00AA<<16) | (MODULE_ADDRESS_SWITCH))
#define MODULE_PC_RELAY (uint16_t)((0x00AA<<16) | (MODULE_ADDRESS_RELAY))
#define MODULE_PC_IR (uint16_t)((0x00AA<<16) | (MODULE_ADDRESS_IR))
#define MODULE_PC_RF (uint16_t)((0x00AA<<16) | (MODULE_ADDRESS_RF))
#define MODULE_PC_CURRENT (uint16_t)((0x00AA<<16) | (MODULE_ADDRESS_CURRENT))
#define MODULE_PC_ENVIRONMENT (uint16_t)((0x00AA<<16) | (MODULE_ADDRESS_ENVIRONMENT))
#define MODULE_PC_PARTICLE (uint16_t)((0x00AA<<16) | (MODULE_ADDRESS_PARTICLE))

