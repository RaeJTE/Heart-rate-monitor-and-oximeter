#ifndef MPU_STUFF_H
#define MPU_STUFF_H

#include <stm32f4xx.h> // bring in library
#include "i2c.h"




// MPU6050 Registers
#define MPU6050_ADDR 0xD2  // (0x69 << 1) for write, 0xD3 for read
#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75


// Global Variables
extern int16_t Accel_X_RAW, Accel_Y_RAW, Accel_Z_RAW;
extern float Ax, Ay, Az;
extern uint8_t check;




// function prototypes
void MPU6050_Init(void);
void MPU6050_Read_Accel(void);
void MPU_Write(uint8_t Address, uint8_t Reg, uint8_t Data);
void MPU_Read(uint8_t Address, uint8_t Reg, uint8_t *buffer, uint8_t size);
void MPU_IRQ(void);
void MPU_interupt(void);



#endif