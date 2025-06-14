/*
 * max3485.c
 *
 *  Created on: Jun 14, 2025
 *      Author: ebokm
 */


#include "max3485.h" // Include the corresponding header file for declarations
#include "main.h"
#include <string.h> // For memset, if used for clearing buffers (not strictly necessary here but good practice)

// Define the global volatile float variable here.
// This is the single definition for 'rs485' in your entire project.
volatile float rs485 = 0;

/**
 * @brief Calculates the CRC16 (Modbus RTU) checksum for a given data buffer.
 *
 * @param data Pointer to the data buffer.
 * @param length The number of bytes in the data buffer.
 * @return The calculated CRC16 checksum.
 */
uint16_t calculateCRC(uint8_t *data, uint8_t length) {
  uint16_t crc = 0xFFFF;

  for (uint8_t i = 0; i < length; i++) {
    crc ^= data[i];

    for (uint8_t j = 0; j < 8; j++) {
      if (crc & 0x0001) {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else {
        crc >>= 1;
      }
    }
  }
  return crc;
}

/**
 * @brief Sends a Modbus RTU command over RS485.
 * Enables the MAX3485 transceiver, sends the command, then disables the transceiver.
 *
 * @param address The Modbus slave address.
 * @param functionCode The Modbus function code (e.g., 0x03 for Read Holding Registers).
 * @param startAddress The starting register address to read/write.
 * @param numData The number of registers/bits to read/write.
 */
void sendCommand(uint8_t address, uint8_t functionCode, uint16_t startAddress, uint16_t numData) {
  uint8_t command[8];
  uint16_t crc;

  // Enable RS485 Transmit (DE/RE pin HIGH)
  HAL_GPIO_WritePin(MAX3485_EN_GPIO_Port, MAX3485_EN_Pin, GPIO_PIN_SET);

  command[0] = address;
  command[1] = functionCode;
  command[2] = (startAddress >> 8) & 0xFF; // High byte of start address
  command[3] = startAddress & 0xFF;        // Low byte of start address
  command[4] = (numData >> 8) & 0xFF;      // High byte of number of data
  command[5] = numData & 0xFF;             // Low byte of number of data

  crc = calculateCRC(command, 6);
  command[6] = crc & 0xFF;        // Low byte of CRC
  command[7] = (crc >> 8) & 0xFF; // High byte of CRC (Modbus CRC is low byte first, then high byte)

  // Transmit the Modbus command
  HAL_UART_Transmit(&huart1, command, 8, HAL_MAX_DELAY);
  // It's often beneficial to add a small delay here after transmit completes
  // to ensure the last bit is sent before changing the DE/RE pin,
  // especially at high baud rates. Or, use UART_Transmit_IT for non-blocking.
  // A good practice is to wait for the transmit complete flag if possible.
  // For simplicity with HAL_MAX_DELAY, the delay might be minimal.
  HAL_Delay(1); // Small delay might be needed, or ensure TX complete

  // Clear Overrun Error Flag (OREF) if it was set
  // This is often cleared automatically by reading DR, but explicitly doing it
  // can prevent issues, though direct flag clearing might be implementation-specific.
  // __HAL_UART_CLEAR_FLAG(&huart1,UART_CLEAR_OREF);

  // Disable RS485 Transmit (DE/RE pin LOW for Receive)
  HAL_GPIO_WritePin(MAX3485_EN_GPIO_Port, MAX3485_EN_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Reads an expected response from the Modbus RTU slave.
 * Attempts to parse the response to extract pressure data if a specific
 * Modbus response pattern is found. Updates the global 'rs485' variable.
 *
 * @param expectedBytes The total number of bytes expected in the response.
 */
void readResponse(uint16_t expectedBytes) {
    // Dynamically sized array on stack is fine for small sizes.
    // For larger responses, consider static or heap allocation.
    uint8_t data[expectedBytes];
    memset(data, 0, expectedBytes); // Clear buffer before receiving

    HAL_StatusTypeDef ret;
    // Attempt to receive data with a timeout of 10ms.
    ret = HAL_UART_Receive(&huart1, data, expectedBytes, 10);

    if (ret == HAL_OK) {
        int16_t pressureRaw = 32767; // Sentinel value to indicate no valid pressure found

        // Search for the specific Modbus RTU response pattern:
        // Slave Address (0x01) | Function Code (0x03) | Byte Count (0x02) | Data_H | Data_L | CRC_L | CRC_H
        // The loop should not go beyond (expectedBytes - 5) to safely access data[t+4] etc.
        for (uint8_t t = 0; t <= (expectedBytes - 5); t++) { // Adjusted loop condition
            if (data[t] == 0x01 && data[t+1] == 0x03 && data[t+2] == 0x02) {
                pressureRaw = (data[t+3] << 8) | data[t+4]; // Extract the 16-bit raw pressure value
                // Optional: Validate CRC here to ensure data integrity
                // uint16_t received_crc = (data[t+6] << 8) | data[t+5]; // Modbus RTU CRC is LSB first
                // uint16_t calculated_crc = calculateCRC(&data[t], 5); // CRC calculated over first 5 bytes (Addr, Func, Count, DataH, DataL)
                // if (received_crc == calculated_crc) { /* data is valid */ }
                break; // Found the pattern, no need to continue searching
            }
        }

        // If a valid pressureRaw value was extracted (not the sentinel)
        if (pressureRaw != 32767) {
            rs485 = (float)pressureRaw / 10.0f; // Convert raw integer to float pressure
        }
    }
    // If ret != HAL_OK (timeout or error), rs485 retains its previous value or default 0.
}
