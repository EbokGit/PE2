/*
 * max3485.h
 *
 *  Created on: May 4, 2025
 *      Author: ebokm
 */

#ifndef INC_MAX3485_H_
#define INC_MAX3485_H_

UART_HandleTypeDef huart1;

volatile float rs485 = 0;

// Function to calculate CRC16 (Modbus RTU)
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


// Function to send Modbus RTU command
void sendCommand(uint8_t address, uint8_t functionCode, uint16_t startAddress, uint16_t numData) {

  uint8_t command[8];
  uint16_t crc;

  HAL_GPIO_WritePin(MAX3485_EN_GPIO_Port, MAX3485_EN_Pin, GPIO_PIN_SET);

  command[0] = address;
  command[1] = functionCode;
  command[2] = (startAddress >> 8) & 0xFF; // High byte of start address
  command[3] = startAddress & 0xFF;        // Low byte of start address
  command[4] = (numData >> 8) & 0xFF;     // High byte of number of data
  command[5] = numData & 0xFF;            // Low byte of number of data

  crc = calculateCRC(command, 6);
  command[6] = crc & 0xFF;        // Low byte of CRC
  command[7] = (crc >> 8) & 0xFF; // High byte of CRC

  HAL_UART_Transmit(&huart1, command, 8, HAL_MAX_DELAY);
  __HAL_UART_CLEAR_FLAG(&huart1,UART_CLEAR_OREF);

  HAL_GPIO_WritePin(MAX3485_EN_GPIO_Port, MAX3485_EN_Pin, GPIO_PIN_RESET);
}

void readResponse(uint16_t expectedBytes) {

	uint8_t data[expectedBytes];

	HAL_StatusTypeDef ret;
	ret = HAL_UART_Receive(&huart1, data, expectedBytes, 10);

	if(ret == HAL_OK){

		int16_t pressureRaw = 32767;

		for(uint8_t t = 0; t <= expectedBytes; t++){
			if(data[t] == 0x01 && data[t+1] == 0x03 && data[t+2] == 0x02){
				pressureRaw = (data[t+3] << 8) | data[t+4];
			}
		}

		if(pressureRaw != 32767){
			rs485 = (float)pressureRaw / 10.0f;

		}

	}

}

#endif /* INC_MAX3485_H_ */
