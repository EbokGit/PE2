/*
 * LED.c
 *
 *  Created on: Jun 14, 2025
 *      Author: ebokm
 */


#include "LED.h" // Include the corresponding header file for declarations
#include "main.h"

// Internal data storage for LED colors
// and making them internal to the module.
static uint8_t LED_Data[MAX_LED][4];
static uint8_t datasentflag = 0;

// Internal buffer for PWM data
static uint32_t pwmData[(24 * MAX_LED) + 50];

/**
 * @brief Sets the color for a specific LED in the internal buffer.
 *
 * @param LEDnum The index of the LED (0 to MAX_LED-1).
 * @param Red The red component (0-255).
 * @param Green The green component (0-255).
 * @param Blue The blue component (0-255).
 */
void Set_LED(int LEDnum, int Red, int Green, int Blue)
{
    // Ensure LEDnum is within bounds
    if (LEDnum >= 0 && LEDnum < MAX_LED) {
        LED_Data[LEDnum][0] = LEDnum;    // Store LED number (optional, often not needed here)
        LED_Data[LEDnum][1] = Green;     // WS2812 expects GRB order
        LED_Data[LEDnum][2] = Red;
        LED_Data[LEDnum][3] = Blue;
    }
}

/**
 * @brief Sends the buffered LED data to the WS2812 LEDs via PWM DMA.
 * This function assumes the TIM_HandleTypeDef is correctly initialized
 * for PWM generation and DMA.
 *
 * @param htim_ptr Pointer to the TIM_HandleTypeDef structure for the PWM timer.
 */
void WS2812_Send(TIM_HandleTypeDef *htim_ptr)
{
    uint32_t indx = 0;
    uint32_t color;

    // Generate PWM data for each LED
    for (int i = 0; i < MAX_LED; i++)
    {
        // Combine GRB components into a single 24-bit color value
        // WS2812B expects Green (8-bit), Red (8-bit), Blue (8-bit)
        color = ((uint32_t)LED_Data[i][1] << 16) | ((uint32_t)LED_Data[i][2] << 8) | ((uint32_t)LED_Data[i][3]);

        // Convert 24-bit color into 24 PWM pulses
        // Iterate from MSB (bit 23) down to LSB (bit 0)
        for (int j = 23; j >= 0; j--) // Changed loop variable from 'i' to 'j' to avoid conflict with outer loop 'i'
        {
            if ((color >> j) & 0x01) // Check if the j-th bit is 1
            {
                pwmData[indx] = 60;  // High pulse for a '1' bit (e.g., 2/3 of 90 for TIM_CLK=90MHz, 800kHz data rate)
                                     // Assuming your timer period is set appropriately (e.g., to 90 for 1.25us period)
            }
            else
            {
                pwmData[indx] = 30;  // High pulse for a '0' bit (e.g., 1/3 of 90)
            }
            indx++;
        }
    }

    // Add reset pulse (at least 50us of low signal)
    // This is achieved by sending 50 zero-value PWM pulses if timer period is ~1.25us
    for (int i = 0; i < 50; i++)
    {
        pwmData[indx] = 0; // Low pulse for reset
        indx++;
    }

    // Start PWM generation via DMA
    // Pass the provided timer handle pointer
    HAL_TIM_PWM_Start_DMA(htim_ptr, TIM_CHANNEL_2, (uint32_t *)pwmData, indx);

    // Wait for the DMA transfer to complete
    // This is a blocking wait. Consider a non-blocking approach for real-time systems.
    while (!datasentflag){};
    datasentflag = 0; // Reset flag for next transfer
}

// HAL Timer PWM Pulse Finished Callback
// This function must be implemented here if it's specific to this LED driver.
// The name must match the HAL driver's callback prototype exactly.
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    // Check if the callback is for the correct timer and channel
    // (Optional but good practice if you have multiple timers/channels)
    // if (htim->Instance == TIM2 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) // Check specific timer instance and channel
    {
        HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_2); // Stop the DMA transfer
        datasentflag = 1;                          // Set flag to signal completion
    }
}
