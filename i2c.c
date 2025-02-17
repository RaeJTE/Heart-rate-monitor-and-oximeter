#include "i2c.h"

void I2C2_Config(void)
{
    // Enable clocks
    RCC->APB1ENR |= (1 << 22);  // Enable I2C2 Clock
    RCC->AHB1ENR |= (1 << 1);   // Enable GPIOB Clock

    // Configure PB10 (SCL) and PB11 (SDA) as Alternate Function Open-Drain
    GPIOB->MODER |= (2 << 20) | (2 << 22);  // AF mode for PB10, PB11
    GPIOB->OTYPER |= (1 << 10) | (1 << 11); // Open-drain
    GPIOB->OSPEEDR |= (3 << 20) | (3 << 22); // High speed
    GPIOB->PUPDR |= (1 << 20) | (1 << 22); // Pull-up
    GPIOB->AFR[1] |= (4 << 8) | (4 << 12);  // AF4 (I2C2) for PB10, PB11

    // Reset I2C2
    I2C2->CR1 |= (1 << 15);// TURN OFF
    I2C2->CR1 &= ~(1 << 15);// TURN BACK ON

    // Set I2C clock frequency (PCLK1 = 45 MHz)
    I2C2->CR2 |= (45 << 0);

    // Configure (100kHz)
    I2C2->CCR = 225;
    I2C2->TRISE = 46;

    // Enable I2C2
    I2C2->CR1 |= (1 << 0);
}

void I2C2_Start(void)// ENABLE I2C
{
    I2C2->CR1 |= (1 << 10); // Enable ACK
    I2C2->CR1 |= (1 << 8);  // Generate START condition
    while (!(I2C2->SR1 & (1 << 0))); // Wait for SB bit
}

void I2C2_Address(uint8_t Address)
{
    I2C2->DR = Address;
    while (!(I2C2->SR1 & (1 << 1))); // Wait for ADDR bit
    (void)I2C2->SR2; // Clear ADDR flag
}

void I2C2_Write(uint8_t data)
{
    while (!(I2C2->SR1 & (1 << 7))); // Wait for TXE
    I2C2->DR = data;
    while (!(I2C2->SR1 & (1 << 2))); // Wait for BTF
}

void I2C2_Stop(void)
{
    I2C2->CR1 |= (1 << 9); // Stop condition
}

void I2C2_Read(uint8_t Address, uint8_t *buffer, uint8_t size)// READ SLAVE (MPU)
{
    int remaining = size;

    I2C2->DR = Address;
    while (!(I2C2->SR1 & (1 << 1))); // Wait for ADDR
    (void)I2C2->SR2; // Clear ADDR flag

    while (remaining > 2)
    {
        while (!(I2C2->SR1 & (1 << 6))); // Wait for RXNE
        *buffer++ = I2C2->DR;
        I2C2->CR1 |= (1 << 10); // ACK
        remaining--;
    }

    while (!(I2C2->SR1 & (1 << 6))); // Read second last byte
    *buffer++ = I2C2->DR;
    I2C2->CR1 &= ~(1 << 10); // NACK
    I2C2->CR1 |= (1 << 9); // STOP

    while (!(I2C2->SR1 & (1 << 6))); // Read last byte
    *buffer = I2C2->DR;
}

void MPU_Write(uint8_t Address, uint8_t Reg, uint8_t Data)// SEND 
{
    I2C2_Start();// INITIALIZE COMMUNICATION
    I2C2_Address(Address);// LOCATE
    I2C2_Write(Reg);//
    I2C2_Write(Data);// DATA TO SEND
    I2C2_Stop();// END COMMUNICATION
}

void MPU_Read(uint8_t Address, uint8_t Reg, uint8_t *buffer, uint8_t size)
{
    I2C2_Start();
    I2C2_Address(Address);
    I2C2_Write(Reg);
    I2C2_Start();
    I2C2_Read(Address + 0x01, buffer, size);// STORE RECIEVED DATA IN BUFFER
    I2C2_Stop();// END
}