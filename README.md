# pe2
practice enterprice 2

# AquaLevel System - Embedded Firmware

This repository contains the embedded C firmware for the AquaLevel system, developed for the PE2 project at Thomas More. The system is designed to monitor water levels using a differential pressure sensor and control a solenoid valve, with user interaction via push buttons, a WS2812B LED strip, and an alphanumeric screen for visual feedback.

The primary focus of this README is to explain the codebase and provide guidance for understanding and adapting it for similar embedded projects.

## Table of Contents

- [Features](#features)
- [Hardware Overview](#hardware-overview)
- [Software Architecture](#software-architecture)
- [Setup and Compilation](#setup-and-compilation)
- [Code Structure and Explanation](#code-structure-and-explanation)
  - [Main Application Flow](#main-application-flow)
  - [LED Control (WS2812B)](#led-control-ws2812b)
  - [Alphanumeric Screen](#alphanumeric-screen)
  - [RS485 Communication (Water Level Sensor)](#rs485-communication-water-level-sensor)
  - [User Input (Buttons)](#user-input-buttons)
  - [Solenoid Valve Control](#solenoid-valve-control)
- [Adaptability for Similar Projects](#adaptability-for-similar-projects)
- [Contributing](#contributing)
- [License](#license)

## Features

* **Water Level Monitoring:** Reads data from a differential pressure sensor via RS485. 
* **User Interface:**
    * 4 push buttons for user input. 
    * WS2812B LED strip for visual feedback (e.g., water level indication). 
    * **Alphanumeric screen for displaying text information.** 
* **Actuation:** Controls a solenoid valve. 
* **Microcontroller:** STM32F301C8T6TR. 

## Hardware Overview

* **Microcontroller:** STM32F301C8T6TR 
* **Power Supply Units (PSU):** 24V 1A [cite: 10], 5V 10A [cite: 11], 3V3 
* **Water Level Sensor:** Differential pressure meter with RS485 output 
* **RS485 Transceiver:** MAX3485 
* **User Input:** 4 Push Buttons 
* **Actuation:** Solid State Relay (SSR) controlling a 230V 50Hz solenoid valve 
* **User Interface (Output):**
    * TXB0108PWR (Level Shifter) 
    * WS2812B LED Strip 
    * **Alphanumeric Screen** 

## Software Architecture

The software is built using the STM32CubeIDE ecosystem, leveraging the Hardware Abstraction Layer (HAL) provided by STMicroelectronics. The core logic is implemented in C. Key aspects of the architecture include:

* **Interrupt-driven Communication:** UART for RS485 [cite: 115], and DMA for WS2812B control.
* **Timer-based Events:** Timers are used for PWM generation (WS2812B).
* **Modular Design:** Functions are separated logically for different peripherals (LEDs, RS485, Buttons, Screen, etc.). 

## Setup and Compilation

1.  **Prerequisites:**
    * STM32CubeIDE (or an equivalent ARM GCC toolchain and ST-Link programmer).
    * ST-Link V2/V3 debugger/programmer.
2.  **Clone the repository:**
    ```bash
    git clone [https://github.com/EbokGit/pe2.git](https://github.com/EbokGit/pe2.git)
    cd pe2
    ```
3.  **Open in STM32CubeIDE:** Import the project into STM32CubeIDE as an existing STM32CubeIDE project.
4.  **Build:** Clean and build the project.
5.  **Flash:** Connect your STM32F301C8T6TR board via an ST-Link debugger and flash the compiled firmware.

## Code Structure and Explanation

The `Core` directory (common in STM32CubeIDE projects) typically contains the main application code.

### Main Application Flow

The `main.c` file contains the `main()` function, which initializes the HAL, configures system clock, and then enters the main super-loop.

```c
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics. All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "16x2_screen.h"
#include "ui.h"
#include "max3485.h"
#include "SSR.h"
#include "LED.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2; 
DMA_HandleTypeDef hdma_tim2_ch2_ch4; 
UART_HandleTypeDef huart1; 

/* USER CODE BEGIN PV */
extern volatile uint8_t page; 
extern volatile uint8_t select; 
extern volatile uint8_t conf; 
extern volatile uint8_t update; 
extern volatile float rs485; 
extern volatile int16_t max_level; 
extern volatile int16_t min_level; 
extern volatile int16_t max_well_level; 
extern volatile int16_t min_well_level; 
extern volatile uint8_t brightness; 
uint32_t pm = 0; //used for debounce 
uint32_t cm = 0; //used for debounce 
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void); 
static void MX_GPIO_Init(void); 
static void MX_DMA_Init(void); 
static void MX_USART1_UART_Init(void); 
static void MX_TIM2_Init(void); 
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) 
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init(); 

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config(); 

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init(); 
  MX_DMA_Init(); 
  MX_USART1_UART_Init(); 
  MX_TIM2_Init(); 
  /* USER CODE BEGIN 2 */
  init_screen(); 
  ui(); 
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) 
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
    if(update == 1){ 
        update = 0; 
        ui(); 
    }
    sendCommand(0x01, 0x03, 0x0004, 0x01); 
    HAL_Delay(2); 
    readResponse(7); 
    if(HAL_GPIO_ReadPin(SSR_GPIO_Port, SSR_Pin) == 0 && rs485 <= min_level){ 
        relay("ON"); 
    }
    else if(HAL_GPIO_ReadPin(SSR_GPIO_Port, SSR_Pin) == 1 && rs485 <= max_level){ 
    }
    else if(HAL_GPIO_ReadPin(SSR_GPIO_Port, SSR_Pin) == 1 && rs485 >= max_level){ 
        relay("OFF"); 
    }
    else{
        relay("OFF"); 
    }
    float level_size = 133.0f / (max_well_level - min_well_level); 
    uint8_t min = (min_level * level_size); 
    uint8_t max = (max_level * level_size); 
    uint8_t min_well = (min_well_level * level_size); 
    uint8_t max_well = ((max_well_level - min_well_level) * level_size); 
    uint8_t level = (rs485 * level_size); 
    for(uint8_t l = 0; l<=133; l++){ 
        if(l <= level){ 
            Set_LED(l, 0, 0, brightness); 
        }
        else{
            Set_LED(l, 0, 0, 0); 
        }
    }
    Set_LED(min, (brightness + 100), 0, 0); 
    Set_LED(max, 0, (brightness + 100), 0); 
    Set_LED(min_well, (brightness - 5), (brightness - 5), (brightness - 5)); 
    Set_LED(max_well, (brightness - 5), (brightness - 5), (brightness - 5)); 
    WS2812_Send(&htim2); 
  }
  /* USER CODE END 3 */
}
