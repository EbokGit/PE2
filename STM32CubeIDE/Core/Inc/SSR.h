/*
 * SSR.h
 *
 *  Created on: Jun 14, 2025
 *      Author: ebokm
 */

#ifndef INC_SSR_H_
#define INC_SSR_H_

/**
 * @brief Controls the Solid State Relay (SSR) based on the input command.
 *
 * This function sets or resets the GPIO pin connected to the SSR,
 * effectively turning it ON or OFF.
 *
 * @param command A string indicating the desired state: "ON" to turn the SSR on,
 * "OFF" to turn it off. Any other string will also turn it off.
 */
void relay(const char *command);

#endif /* INC_SSR_H_ */
