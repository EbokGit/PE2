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
    * WS2812B LED strip for visual feedback (e.g., water level indication, system status).
    * **Alphanumeric screen for displaying text information.**
* **Actuation:** Controls a solenoid valve.
* **Microcontroller:** STM32F301C8T6TR.

## Hardware Overview

(Based on the provided PE2.pdf document and your additional information)

* **Microcontroller:** STM32F301C8T6TR
* **Power Supply Units (PSU):** 24V 1A, 5V 10A, 3V3
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

* **Interrupt-driven Communication:** UART for RS485, potentially for the alphanumeric screen (if serial), and DMA for WS2812B control.
* **Timer-based Events:** Timers are used for PWM generation (WS2812B) and potentially for debouncing buttons or timing other events.
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
int main(void)
{
  /* MCU Configuration */
  HAL_Init(); // Initialize the HAL Library
  SystemClock_Config(); // Configure the system clock
  MX_GPIO_Init(); // Initialize GPIOs
  MX_DMA_Init(); // Initialize DMA
  MX_USART1_UART_Init(); // Initialize UART1 for RS485 (example)
  MX_TIM2_Init(); // Initialize TIM2 for PWM (example for WS2812B)
  // ... potentially other peripheral initializations for the screen (e.g., I2C, SPI, or another UART)

  /* Application specific initializations */
  LED_Init(); // Initialize the LED strip
  Screen_Init(); // Initialize the alphanumeric screen
  // ... other initializations

  while (1)
  {
    /* Main application loop */
    // Check for new sensor data
    // Process button presses
    // Update LED strip
    // Update alphanumeric screen with relevant information
    // Control solenoid valve based on logic
  }
}
