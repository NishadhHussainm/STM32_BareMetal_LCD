#ifndef LCD_H
#define LCD_H

#include <stdint.h>

// LCD Pin Definitions (Change these based on your setup)
#define RS (1 << 0)  // PB0
#define EN (1 << 1)  // PB1
#define D4 (1 << 2)  // PB2
#define D5 (1 << 3)  // PB3
#define D6 (1 << 4)  // PB4
#define D7 (1 << 5)  // PB5
#define LCD_DATA_MASK (D4 | D5 | D6 | D7)

// Function Prototypes
void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_Char(char data);
void LCD_String(char *str);
void LCD_Clear(void);
void delay_ms(int ms);

#endif
