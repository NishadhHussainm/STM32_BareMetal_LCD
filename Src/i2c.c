#include <stdint.h>

#define RCC_BASE        0x40023800
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x40))

// GPIOB Register Definitions
#define GPIOB_BASE      0x40020400
#define GPIOB_MODER     (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_OTYPER    (*(volatile uint32_t *)(GPIOB_BASE + 0x04))
#define GPIOB_OSPEEDR   (*(volatile uint32_t *)(GPIOB_BASE + 0x08))
#define GPIOB_PUPDR     (*(volatile uint32_t *)(GPIOB_BASE + 0x0C))
#define GPIOB_AFRL      (*(volatile uint32_t *)(GPIOB_BASE + 0x20))

// I2C1 Register Definitions
#define I2C1_BASE       0x40005400
#define I2C1_CR1        (*(volatile uint32_t *)(I2C1_BASE + 0x00))
#define I2C1_CR2        (*(volatile uint32_t *)(I2C1_BASE + 0x04))
#define I2C1_OAR1       (*(volatile uint32_t *)(I2C1_BASE + 0x08))
#define I2C1_DR         (*(volatile uint32_t *)(I2C1_BASE + 0x10))
#define I2C1_SR1        (*(volatile uint32_t *)(I2C1_BASE + 0x14))
#define I2C1_SR2        (*(volatile uint32_t *)(I2C1_BASE + 0x18))
#define I2C1_CCR        (*(volatile uint32_t *)(I2C1_BASE + 0x1C))
#define I2C1_TRISE      (*(volatile uint32_t *)(I2C1_BASE + 0x20))

// Bit Definitions
#define RCC_AHB1ENR_GPIOBEN   (1 << 1)
#define RCC_APB1ENR_I2C1EN    (1 << 21)
#define I2C_CR1_PE           (1 << 0)
#define I2C_CR1_START        (1 << 8)
#define I2C_CR1_STOP         (1 << 9)
#define I2C_CR1_ACK          (1 << 10)
#define I2C_SR1_SB           (1 << 0)
#define I2C_SR1_ADDR         (1 << 1)
#define I2C_SR1_TXE          (1 << 7)
#define I2C_SR1_RXNE         (1 << 6)

// I2C Pin Definitions
#define I2C1_SDA_PIN  7  // PB7
#define I2C1_SCL_PIN  6  // PB6
#define EEPROM_ADDR   0xA0

void I2C1_Init(void) {
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC_APB1ENR |= RCC_APB1ENR_I2C1EN;

    GPIOB_MODER   |= (2 << (I2C1_SCL_PIN * 2)) | (2 << (I2C1_SDA_PIN * 2));
    GPIOB_OTYPER  |= (1 << I2C1_SCL_PIN) | (1 << I2C1_SDA_PIN);
    GPIOB_OSPEEDR |= (3 << (I2C1_SCL_PIN * 2)) | (3 << (I2C1_SDA_PIN * 2));
    GPIOB_PUPDR   |= (1 << (I2C1_SCL_PIN * 2)) | (1 << (I2C1_SDA_PIN * 2));
    GPIOB_AFRL    |= (4 << (I2C1_SCL_PIN * 4)) | (4 << (I2C1_SDA_PIN * 4));

    I2C1_CR1 |= (1 << 15);  // Reset I2C1
    I2C1_CR1 &= ~(1 << 15); // Clear reset

    I2C1_CR2  = 42;
    I2C1_CCR  = 210;
    I2C1_TRISE = 43;
    I2C1_CR1 |= I2C_CR1_PE;
}

void I2C1_Start(uint8_t address, uint8_t direction) {
    I2C1_CR1 |= I2C_CR1_START;
    while (!(I2C1_SR1 & I2C_SR1_SB));

    I2C1_DR = address | direction;
    while (!(I2C1_SR1 & I2C_SR1_ADDR));
    (void) I2C1_SR2;
}

void I2C1_WriteByte(uint8_t data) {
    I2C1_DR = data;
    while (!(I2C1_SR1 & I2C_SR1_TXE));
}

uint8_t I2C1_ReadByte(uint8_t ack) {
    if (ack) {
        I2C1_CR1 |= I2C_CR1_ACK;
    } else {
        I2C1_CR1 &= ~I2C_CR1_ACK;
    }

    while (!(I2C1_SR1 & I2C_SR1_RXNE));
    return I2C1_DR;
}

void I2C1_Stop(void) {
    I2C1_CR1 &= ~I2C_CR1_ACK;  // Ensure ACK is cleared
    I2C1_CR1 |= I2C_CR1_STOP;
}

void EEPROM_Write(uint8_t mem_addr, char data) {
    I2C1_Start(EEPROM_ADDR, 0);
    I2C1_WriteByte(mem_addr);
    I2C1_WriteByte(data);
    I2C1_Stop();
    for (volatile int i = 0; i < 50000; i++);
}

uint8_t EEPROM_Read(uint8_t mem_addr) {
    char data;
    I2C1_Start(EEPROM_ADDR, 0);
    I2C1_WriteByte(mem_addr);
    I2C1_Stop();  // Ensuring STOP before repeated start

    I2C1_Start(EEPROM_ADDR, 1);
    data = I2C1_ReadByte(0);
    I2C1_Stop();
    return data;
}

