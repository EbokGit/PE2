/*
 * SSR.h
 *
 *  Created on: May 17, 2025
 *      Author: ebokm
 */

#ifndef INC_SSR_H_
#define INC_SSR_H_

void relay(const char *kraan){

    if (strcmp(kraan, "ON") == 0) {
        HAL_GPIO_WritePin(SSR_GPIO_Port, SSR_Pin, GPIO_PIN_SET);
    }

    else if(strcmp(kraan, "OFF") == 0){
        HAL_GPIO_WritePin(SSR_GPIO_Port, SSR_Pin, GPIO_PIN_RESET);
    }

    else{
        HAL_GPIO_WritePin(SSR_GPIO_Port, SSR_Pin, GPIO_PIN_RESET);
    }
}

#endif /* INC_SSR_H_ */
