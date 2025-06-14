/*
 * SSR.c
 *
 *  Created on: May 17, 2025
 *      Author: ebokm
 */


#include "SSR.h" // Include the corresponding header for declarations
#include "main.h"
#include <string.h>        // Required for strcmp

/**
 * @brief Controls the Solid State Relay (SSR) based on the input command.
 *
 * This function sets or resets the GPIO pin connected to the SSR,
 * effectively turning it ON or OFF.
 *
 * @param command A string indicating the desired state: "ON" to turn the SSR on,
 * "OFF" to turn it off. Any other string will also turn it off.
 */
void relay(const char *command){

    // Compare the input string to "ON"
    if (strcmp(command, "ON") == 0) {
        // Set the GPIO pin HIGH to turn the SSR ON
        HAL_GPIO_WritePin(SSR_GPIO_Port, SSR_Pin, GPIO_PIN_SET);
    }
    // Compare the input string to "OFF"
    else if(strcmp(command, "OFF") == 0){
        // Set the GPIO pin LOW to turn the SSR OFF
        HAL_GPIO_WritePin(SSR_GPIO_Port, SSR_Pin, GPIO_PIN_RESET);
    }
    // If the string is neither "ON" nor "OFF", default to turning it OFF
    else{
        HAL_GPIO_WritePin(SSR_GPIO_Port, SSR_Pin, GPIO_PIN_RESET);
    }
}
