#include <stdint.h>
#include <string.h>
#include "i2c.h"
#include "lcd.h"

// Define buffer variables


#define BUFFER_SIZE 10

int main(void) {
    char tx_buffer[BUFFER_SIZE] = "Nishadh";
    char rx_buffer[BUFFER_SIZE];
    uint8_t mem_addr = 0x10;
    I2C1_Init();

    while (1) {

        for (uint8_t i = 0; i < strlen(tx_buffer); i++) {
            EEPROM_Write(mem_addr + i, tx_buffer[i]);


            for (volatile int j = 0; j < 50000; j++);
        }


        for (uint8_t i = 0; i < strlen(tx_buffer); i++) {
            rx_buffer[i] = EEPROM_Read(mem_addr + i);
        }


        rx_buffer[strlen(tx_buffer)] = '\0';
        LCD_String(rx_buffer);


        for (volatile int i = 0; i < 800000; i++);
    }
}

