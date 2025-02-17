#include "mpu_stuff.h"

void MPU6050_Init(void)
{
    uint8_t Data;

    // Check WHO_AM_I register (should return 0x68)
    MPU_Read(MPU6050_ADDR, WHO_AM_I_REG, &check, 1);
    if (check == 0x68)
    {
        // Wake up MPU6050
        Data = 0;
        MPU_Write(MPU6050_ADDR, PWR_MGMT_1_REG, Data);

        // Set data rate (1kHz sample rate)
        Data = 0x07;
        MPU_Write(MPU6050_ADDR, SMPLRT_DIV_REG, Data);

        // Accelerometer ±2g
        Data = 0x00;
        MPU_Write(MPU6050_ADDR, ACCEL_CONFIG_REG, Data);

        // Gyroscope ±250°/s
        Data = 0x00;
        MPU_Write(MPU6050_ADDR, GYRO_CONFIG_REG, Data);
    }
}

void MPU6050_Read_Accel(void)
{
    uint8_t Rx_data[6];

    // Read 6 bytes of accelerometer data
    MPU_Read(MPU6050_ADDR, ACCEL_XOUT_H_REG, Rx_data, 6);

    Accel_X_RAW = (int16_t)(Rx_data[0] << 8 | Rx_data[1]);
    Accel_Y_RAW = (int16_t)(Rx_data[2] << 8 | Rx_data[3]);
    Accel_Z_RAW = (int16_t)(Rx_data[4] << 8 | Rx_data[5]);

    // Convert raw values to acceleration in g
    Ax = Accel_X_RAW / 16384.0;
    Ay = Accel_Y_RAW / 16384.0;
    Az = Accel_Z_RAW / 16384.0;
}