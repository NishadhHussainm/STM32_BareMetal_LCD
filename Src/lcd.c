#include <stdint.h>

#define GPIOB_BASE      0x40020400
#define GPIOB_MODER     (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_ODR       (*(volatile uint32_t *)(GPIOB_BASE + 0x14))

#define RS (1 << 0)  // PB0
#define EN (1 << 1)  // PB1
#define D4 (1 << 2)  // PB2
#define D5 (1 << 3)  // PB3
#define D6 (1 << 4)  // PB4
#define D7 (1 << 5)  // PB5
#define LCD_DATA_MASK (D4 | D5 | D6 | D7)

void delay_ms(int ms) {
    for (volatile int i = 0; i < (ms * 1000); i++);
}

void LCD_Command(uint8_t cmd) {
    GPIOB_ODR = (GPIOB_ODR & ~LCD_DATA_MASK) | ((cmd >> 4) << 2);
    GPIOB_ODR &= ~RS;
    GPIOB_ODR |= EN;
    delay_ms(1);
    GPIOB_ODR &= ~EN;

    GPIOB_ODR = (GPIOB_ODR & ~LCD_DATA_MASK) | ((cmd & 0x0F) << 2);
    GPIOB_ODR |= EN;
    delay_ms(1);
    GPIOB_ODR &= ~EN;
}

void LCD_Char(char data) {
    GPIOB_ODR = (GPIOB_ODR & ~LCD_DATA_MASK) | ((data >> 4) << 2);
    GPIOB_ODR |= RS;
    GPIOB_ODR |= EN;
    delay_ms(1);
    GPIOB_ODR &= ~EN;

    GPIOB_ODR = (GPIOB_ODR & ~LCD_DATA_MASK) | ((data & 0x0F) << 2);
    GPIOB_ODR |= EN;
    delay_ms(1);
    GPIOB_ODR &= ~EN;
}

void LCD_Init() {
    GPIOB_MODER |= (1 << (0 * 2)) | (1 << (1 * 2)) | (1 << (2 * 2)) |
                   (1 << (3 * 2)) | (1 << (4 * 2)) | (1 << (5 * 2));
    delay_ms(20);

    LCD_Command(0x02); // 4-bit mode
    LCD_Command(0x28); // 2-line, 5x8 dots
    LCD_Command(0x0C); // Display ON, Cursor OFF
    LCD_Command(0x06); // Entry mode
   // LCD_Command(0x01); // Clear screen
}

void LCD_String(char *str) {
    while (*str) {
        LCD_Char(*str++);
    }
}
