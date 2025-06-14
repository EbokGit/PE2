/*
 * ui.h
 *
 *  Created on: May 4, 2025
 *      Author: ebokm
 */

#ifndef INC_UI_H_
#define INC_UI_H_

#include <stdint.h> // For uint8_t, int16_t, uint16_t
#include "16x2_screen.h" // Assuming screen functions are in this header.
#include "max3485.h"     // For 'rs485' variable (already there)

// Declare global variables that need to be accessible from other files.
// Use 'extern' to indicate that these variables are defined in exactly one .c file (ui.c in this case).
extern volatile uint8_t page;
extern uint8_t menu;
extern volatile uint8_t select;
extern volatile uint8_t conf;

extern volatile uint8_t update;

extern volatile int16_t max_well_level;
extern volatile int16_t min_well_level;
extern volatile int16_t max_level;
extern volatile int16_t min_level;

extern volatile float diameter;
extern volatile uint16_t X;
extern volatile uint16_t Y;

extern volatile uint8_t brightness;

extern const char *form; // extern for the pointer itself, the string literal is in .c

// Function declarations (prototypes)
// This is the main UI function that will be called externally.
/**
 * @brief Manages the user interface logic, including menu navigation and display updates.
 * This function implements a state machine based on 'menu' and 'page' variables.
 */
void ui(void);

#endif /* INC_UI_H_ */
