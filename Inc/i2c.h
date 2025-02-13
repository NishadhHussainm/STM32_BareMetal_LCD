#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define EEPROM_ADDR   0xA0

void I2C1_Init(void);
void I2C1_Start(uint8_t address, uint8_t direction);
void I2C1_WriteByte(uint8_t data);
uint8_t I2C1_ReadByte(uint8_t ack);
void I2C1_Stop(void);
void EEPROM_Write(uint8_t mem_addr, char data);
uint8_t EEPROM_Read(uint8_t mem_addr);

#endif // I2C_H
