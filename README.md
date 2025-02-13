# STM32_BareMetal_LCD

## Overview
This project demonstrates how to interface an LCD display with an STM32 microcontroller using bare-metal programming (without an RTOS or HAL library). It includes GPIO-based control for the LCD and I2C communication for EEPROM data storage.

## Features
- LCD display interfaced using GPIO
- EEPROM read/write via I2C
- Bare-metal programming approach
- Optimized performance with direct register access

## Hardware Requirements
- STM32 Microcontroller (e.g., STM32F4xx)
- 16x2 or 20x4 LCD Display
- I2C-based EEPROM (e.g., 24C04)
- Jumper wires and breadboard (for testing)
- Power supply (3.3V or 5V based on hardware requirements)

## Software Requirements
- ARM GCC Toolchain
- STM32CubeIDE 
- OpenOCD or ST-Link Utility for flashing

## Installation & Usage
1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/STM32_BareMetal_LCD.git
   ```
2. Navigate to the project directory:
   ```sh
   cd STM32_BareMetal_LCD
   ```
3. Compile the project using Makefile:
   ```sh
   make
   ```
4. Flash the firmware:
   ```sh
   openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program main.elf verify reset exit"
   ```
5. Reset the board and observe the LCD output.

## Code Structure
```
STM32_BareMetal_LCD/
├── src/
│   ├── main.c        # Main application code
│   ├── lcd.c         # LCD driver functions
│   ├── i2c_eeprom.c  # I2C EEPROM read/write functions
│   └── system_stm32.c # System initialization
├── inc/
│   ├── lcd.h         # LCD function declarations
│   ├── i2c_eeprom.h  # EEPROM function declarations
│   ├── stm32f4xx.h   # STM32 register definitions
├── Makefile          # Compilation instructions
├── README.md         # Project documentation
└── .gitignore        # Ignore compiled binaries
```

## LCD Connection Table
| LCD Pin | STM32 Pin |
|---------|----------|
| RS      | PB0      |
| RW      | PB1      |
| E       | PB2      |
| D4      | PB4      |
| D5      | PB5      |
| D6      | PB6      |
| D7      | PB7      |

## EEPROM Communication
- Uses I2C1 (SCL: PB8, SDA: PB9)
- Read/Write operations are implemented in `i2c.c`



## Author
[Nishadh Hussain M]

