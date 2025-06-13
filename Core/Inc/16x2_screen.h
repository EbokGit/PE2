/*
 * 16x2_screen.h
 *
 * Created on: May 4, 2025
 * Author: ebokm
 */

#ifndef INC_16X2_SCREEN_H_
#define INC_16X2_SCREEN_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>

void screen_render(uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
void send_to_screen(uint8_t data, uint8_t nob, uint8_t cod);
void screen_start(void);
void init_screen(void);
void write_to_screen(char* scherm);
void digit_to_screen(int32_t scherm);
void float_to_screen(float scherm);
void cursor_pos(uint8_t line, uint8_t pos);

#endif /* INC_16X2_SCREEN_H_ */
