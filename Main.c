//Includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "switch.h"
#include "lcd.h"
#include "DAC.h"
#include "ADC.h"
#include "Buzz.h"
#include "LED.h"
#include "usart.h"
#include "timer.h"
#include "RGB_Bar.h"
#include "segments.h"
#include "i2c.h"
#include "MPU_stuff.h"
//Definitions
#define name "Jacob Rae"
#define pi 3.14159

//4-bit mode not working


// Global Variables
int16_t Accel_X_RAW = 0, Accel_Y_RAW = 0, Accel_Z_RAW = 0;
float Ax, Ay, Az;
uint8_t check;

int main(void)
{
	//Initialisation of switches
	BLU_BTN_INIT(BLU_PORT, BLU_BTN);
	FOUR_BTN_INIT(FOUR_BTN_PORT, BTN0, BTN1, BTN2, BTN3);
	//Initialisation of green traffic LED
	LED_INIT();
	//Initialisation of LCD in 8-bit mode
	initLCD8();
	cmdLCD(LCD_LINE1);
	LCD_CLR();
	//Initiliases the ADC and DAC
	init_ADC();
	init_DAC();
	//Initialisation of Buzzer
	initBuzz();
	//Initialisation of MPU
	MPU6050_Init();
	//Initialises Usart
	init_USART();
	
	
	
	
	
	
	
	
	stringLCD("Code complete", 13, 0,0);
	output_dac1(0);
	lcd_delayus(500000);
	LCD_CLR();
	
	
}
