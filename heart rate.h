#ifndef heart_rate_h
#define heart_rate_h

#include <stdio.h>
#include <string.h>	//used for memcpy so readADC array can run continuously and analysis can be performed on it at a fixed point in time
#include <stdlib.h>
#include <math.h>
#include "switch.h"
#include "lcd.h"
#include "DAC.h"
#include "ADC.h"
#include "Buzz.h"
#include "LED.h"
#include "segments.h"
#include "RGB_Bar.h"
#include "i2c.h"
#include "MPU_stuff.h"
#include "usart.h"
#include "timer.h"
#include "PeakDetection.h"
#include <stm32f429xx.h>


extern int16_t Accel_X_RAW, Accel_Y_RAW, Accel_Z_RAW;
extern float Ax, Ay, Az;
extern uint8_t check;
extern unsigned int int_part;
extern unsigned int frac_part;


extern int accel_check;
void motion_check(int accel_check);




void heart_rate_main(void);



#endif