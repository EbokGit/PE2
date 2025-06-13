/*
 * LED.h
 *
 *  Created on: May 21, 2025
 *      Author: ebokm
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#define MAX_LED 134

uint8_t LED_Data[MAX_LED][4];
uint8_t datasentflag = 0;

TIM_HandleTypeDef htim2;

void Set_LED (int LEDnum, int Red, int Green, int Blue)
{
	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][1] = Green;
	LED_Data[LEDnum][2] = Red;
	LED_Data[LEDnum][3] = Blue;
}

uint32_t pwmData[(24*MAX_LED)+50];

void WS2812_Send (void)
{
	uint32_t indx=0;
	uint32_t color;

	for (int i= 0; i<MAX_LED; i++)
	{

		color = ((LED_Data[i][1]<<16) | (LED_Data[i][2]<<8) | (LED_Data[i][3]));

		for (int i=23; i>=0; i--)
		{
			if (color&(1<<i))
			{
				pwmData[indx] = 60;  // 2/3 of 90
				indx++;
			}
			else  // 1/3 of 90
			{
				pwmData[indx] = 30;
				indx++;
			}
		}

	}

	for (int i=0; i<50; i++)
	{
		pwmData[indx] = 0;
		indx++;
	}

	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2 , (uint32_t *)pwmData, indx);

	while (!datasentflag){};
		datasentflag = 0;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_2);
	datasentflag=1;
}

#endif /* INC_LED_H_ */
