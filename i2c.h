#ifndef I2C_H
#define I2C_H

#include "stm32f4xx.h"

// Global Variables
extern int16_t Accel_X_RAW, Accel_Y_RAW, Accel_Z_RAW;
extern float Ax, Ay, Az;
extern uint8_t check;


void I2C2_Config(void);
void I2C2_Start(void);
void I2C2_Write(uint8_t data);
void I2C2_Address(uint8_t Address);
void I2C2_Stop(void);
void I2C2_Read(uint8_t Address, uint8_t *buffer, uint8_t size);

void MPU_Write(uint8_t Address, uint8_t Reg, uint8_t Data);
void MPU_Read(uint8_t Address, uint8_t Reg, uint8_t *buffer, uint8_t size);

#endif