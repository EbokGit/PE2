/*
 * 16x2_screen.h
 *
 *  Created on: May 4, 2025
 *      Author: ebokm
 */

#ifndef INC_16X2_SCREEN_H_
#define INC_16X2_SCREEN_H_

void screen_render(uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7){

		if (d4 == 1){
			HAL_GPIO_WritePin(TXB_16x2_D4_GPIO_Port, TXB_16x2_D4_Pin, GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(TXB_16x2_D4_GPIO_Port, TXB_16x2_D4_Pin, GPIO_PIN_RESET);
		}

		if (d5 == 1){
			HAL_GPIO_WritePin(TXB_16x2_D5_GPIO_Port, TXB_16x2_D5_Pin, GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(TXB_16x2_D5_GPIO_Port, TXB_16x2_D5_Pin, GPIO_PIN_RESET);
		}

		if (d6 == 1){
			HAL_GPIO_WritePin(TXB_16x2_D6_GPIO_Port, TXB_16x2_D6_Pin, GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(TXB_16x2_D6_GPIO_Port, TXB_16x2_D6_Pin, GPIO_PIN_RESET);
		}

		if (d7 == 1){
			HAL_GPIO_WritePin(TXB_16x2_D7_GPIO_Port, TXB_16x2_D7_Pin, GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(TXB_16x2_D7_GPIO_Port, TXB_16x2_D7_Pin, GPIO_PIN_RESET);
		}

	}

	void send_to_screen(uint8_t data, uint8_t nob, uint8_t cod){

		HAL_Delay(1);

		if (cod == 'c'){ // c = command 		d = data
			HAL_GPIO_WritePin(TXB_16x2_RS_GPIO_Port, TXB_16x2_RS_Pin, GPIO_PIN_RESET);
		}

		else{
			HAL_GPIO_WritePin(TXB_16x2_RS_GPIO_Port, TXB_16x2_RS_Pin, GPIO_PIN_SET);
		}

		if (nob == 'b'){ // b = byte		n = nibble
			uint8_t d4 = (data >> 4) & 0x01; // Bit 0
			uint8_t d5 = (data >> 5) & 0x01; // Bit 1
			uint8_t d6 = (data >> 6) & 0x01; // Bit 2
			uint8_t d7 = (data >> 7) & 0x01; // Bit 3

			HAL_GPIO_WritePin(TXB_16x2_E_GPIO_Port, TXB_16x2_E_Pin, GPIO_PIN_RESET);
			screen_render(d4, d5, d6, d7);
			HAL_GPIO_WritePin(TXB_16x2_E_GPIO_Port, TXB_16x2_E_Pin, GPIO_PIN_SET);
			HAL_Delay(1);
			screen_render(d4, d5, d6, d7);
			HAL_GPIO_WritePin(TXB_16x2_E_GPIO_Port, TXB_16x2_E_Pin, GPIO_PIN_RESET);
			screen_render(d4, d5, d6, d7);
			screen_render(0, 0, 0, 0); // pins standaart 0
		}

		uint8_t d4 = (data >> 0) & 0x01; // Bit 0
		uint8_t d5 = (data >> 1) & 0x01; // Bit 1
		uint8_t d6 = (data >> 2) & 0x01; // Bit 2
		uint8_t d7 = (data >> 3) & 0x01; // Bit 3

		HAL_GPIO_WritePin(TXB_16x2_E_GPIO_Port, TXB_16x2_E_Pin, GPIO_PIN_RESET);
		screen_render(d4, d5, d6, d7);
		HAL_GPIO_WritePin(TXB_16x2_E_GPIO_Port, TXB_16x2_E_Pin, GPIO_PIN_SET);
		HAL_Delay(1);
		screen_render(d4, d5, d6, d7);
		HAL_GPIO_WritePin(TXB_16x2_E_GPIO_Port, TXB_16x2_E_Pin, GPIO_PIN_RESET);
		screen_render(d4, d5, d6, d7);
		screen_render(0, 0, 0, 0); // pins standaart 0
	}

	void screen_start(){

		send_to_screen(0b0011, 'n', 'c');
		send_to_screen(0b0011, 'n', 'c');
		send_to_screen(0b0011, 'n', 'c');
	}

	void init_screen(){

		HAL_Delay(30); //wachten tot het scherm volledig is opgestart
		screen_start();
		send_to_screen(0b0010, 'n', 'c');		//4 bit modus
		send_to_screen(0b00101000, 'b', 'c');	//4 bit modus
		send_to_screen(0b00001111, 'b', 'c');	//display on
		send_to_screen(0b00000001, 'b', 'c');	//clear display
		send_to_screen(0b00000110, 'b', 'c');	//entry mode
	}

	void write_to_screen(char* scherm){

		uint8_t lengte = strlen(scherm);

		for (uint8_t i = 0; i < lengte; i++) {
				send_to_screen(scherm[i], 'b', 'd');
		}
	}

	void digit_to_screen(int32_t scherm) {
	    char scherm_str[12];
	    int len;

	    len = snprintf(scherm_str, sizeof(scherm_str), "%ld", scherm);
	    if (len < 0 || len >= sizeof(scherm_str)) {
	        return;
	    }

	    for (int i = 0; i < len; i++) {
	        send_to_screen(scherm_str[i], 'b', 'd');
	    }
	}

	void float_to_screen(float scherm) {
		char scherm_str[20];
		int len;

		len = snprintf(scherm_str, sizeof(scherm_str), "%.1f", scherm);
		if (len < 0 || len >= sizeof(scherm_str)) {
			return;
		}

		for (int i = 0; i < len; i++) {
			send_to_screen(scherm_str[i], 'b', 'd');
		}
	}

	void cursor_pos(uint8_t line, uint8_t pos) {
		uint8_t address;

		if (line == 1) {
			address = 0x00 + (pos - 1); // Line 1 starts at 0x00
		}
		else{
			address = 0x40 + (pos - 1); // Line 2 starts at 0x40
		}

		send_to_screen(0b10000000 | address, 'b', 'c');

	}

#endif /* INC_16X2_SCREEN_H_ */
