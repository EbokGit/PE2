/*
 * max3485.h
 *
 *  Created on: May 4, 2025
 *      Author: ebokm
 */

#ifndef INC_MAX3485_H_
#define INC_MAX3485_H_

#include <stdint.h> // For uint8_t, uint16_t etc.
#include "main.h"

// Declare the external UART handle.
// This tells the compiler that 'huart1' exists somewhere else (defined in a .c file, usually main.c).
extern UART_HandleTypeDef huart1;

// Declare the external volatile float variable for RS485 data.
// 'extern' is used here because 'rs485' is defined in max3485.c and needs to be accessible globally.
extern volatile float rs485;

// Function declarations (prototypes)
// These are the functions that other .c files can call.

/**
 * @brief Calculates the CRC16 (Modbus RTU) checksum for a given data buffer.
 *
 * @param data Pointer to the data buffer.
 * @param length The number of bytes in the data buffer.
 * @return The calculated CRC16 checksum.
 */
uint16_t calculateCRC(uint8_t *data, uint8_t length);

/**
 * @brief Sends a Modbus RTU command over RS485.
 * Enables the MAX3485 transceiver, sends the command, then disables the transceiver.
 *
 * @param address The Modbus slave address.
 * @param functionCode The Modbus function code (e.g., 0x03 for Read Holding Registers).
 * @param startAddress The starting register address to read/write.
 * @param numData The number of registers/bits to read/write.
 */
void sendCommand(uint8_t address, uint8_t functionCode, uint16_t startAddress, uint16_t numData);

/**
 * @brief Reads an expected response from the Modbus RTU slave.
 * Attempts to parse the response to extract pressure data if a specific
 * Modbus response pattern is found. Updates the global 'rs485' variable.
 *
 * @param expectedBytes The total number of bytes expected in the response.
 */
void readResponse(uint16_t expectedBytes);

#endif /* INC_MAX3485_H_ */
