/*
 * LED.h
 *
 *  Created on: May 21, 2025
 *      Author: ebokm
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include <stdint.h> // For uint8_t, uint32_t
#include "main.h"

// Define the maximum number of LEDs.
// It's good practice to make this configurable here.
#define MAX_LED 134

// Function declarations (prototypes)
// These are the functions that other .c files can call.

/**
 * @brief Sets the color for a specific LED in the internal buffer.
 *
 * @param LEDnum The index of the LED (0 to MAX_LED-1).
 * @param Red The red component (0-255).
 * @param Green The green component (0-255).
 * @param Blue The blue component (0-255).
 */
void Set_LED(int LEDnum, int Red, int Green, int Blue);

/**
 * @brief Sends the buffered LED data to the WS2812 LEDs via PWM DMA.
 * Requires a timer handle for the PWM.
 */
void WS2812_Send(TIM_HandleTypeDef *htim_ptr);

#endif /* INC_LED_H_ */
