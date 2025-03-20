//Includes
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
//Definitions
#define name "Jacob Rae"
#define pi 3.14159
//SamplingRate defined in timer.h

// Global Variables
int16_t Accel_X_RAW = 0, Accel_Y_RAW = 0, Accel_Z_RAW = 0;
float Ax, Ay, Az;
uint8_t check;
int j = 0;
extern volatile uint8_t ADCout[15*samplingRate];
float copyADCout[15*samplingRate];	//Equivalent arry to above but that does not rapidly update

int main(void)
{
	//Initialisation of switches
	BLU_BTN_INIT(BLU_PORT, BLU_BTN);
	FOUR_BTN_INIT(FOUR_BTN_PORT, BTN0, BTN1, BTN2, BTN3);
	//Initialisation of LCD in 8-bit mode
	initLCD8();
	cmdLCD(LCD_LINE1);
	LCD_CLR();
	//Initiliases the ADC and DAC
	init_ADC();
	init_DAC();
	//Initialisation of Buzzer
	initBuzz();
	//Initialisation of LEDs
	LED_INIT();
	//Initialisation of I2C
	I2C2_Config();
	//Initialisation of MPU
	MPU6050_Init();
	//Initialisation of USART
	init_USART();
	//Initialisation of timers
	Init_Timer2(samplingRate);	//Used for reading ADC
	Init_Timer3();	//Used for timer based delays
	
	//Initialisation of variables
	char* num;	//Creates a pointer to be used to store a string conversion of a number - pointer necessary because of pointer decay when moving between .c files
	int numLen;	//Variable to store length of string conversion of number
	int numPeaks;
	int* peakPositions;
	
	stringLCD("Begin in", 8, 0, 0);
	TIM3Delay(2500);
	LCD_CLR();
	stringLCD("5", 1, 0, 0);
	TIM3Delay(2500);
	LCD_CLR();
	stringLCD("4", 1, 0, 0);
	TIM3Delay(2500);
	LCD_CLR();
	stringLCD("3", 1, 0, 0);
	TIM3Delay(2500);
	LCD_CLR();
	stringLCD("2", 1, 0, 0);
	TIM3Delay(2500);
	LCD_CLR();
	stringLCD("1", 1, 0, 0);
	TIM3Delay(2500);
	LCD_CLR();
	
	//Reads in the rapidly updating array to a non updating array
	for(j = 0; j < (15* samplingRate)-1; j++)
	{
		copyADCout[j] = ADCout[j];
	}
	
	peakDetection(copyADCout, &numPeaks, &peakPositions);
	
	LCD_CLR();
	
	float BPM = (60 * numPeaks) / 15;	//Translates peaks detected in 15s to average number of peaks in a minute and thus bpm
	decIntToDecStr(BPM, &num, &numLen);
	
	stringLCD("Avg hrtrate /bpm", 16, 0, 0);
	stringLCD(num, numLen, 1, 0);
	TIM3Delay(50000);
	LCD_CLR();	
	
	
	
	/*
	*********************************************
	********SIMULATED TEST SIGNALS***************
	*********************************************
	*/
	
	
	
	/*int dataPoints = 360000;	//Defines how many data points we want to take
	//For some reason previous code kept breaking when I used for loops here - possible from use of i specificly?
	
	for (int i = 0; i < dataPoints; i++)
	{
		float radians = i*(pi/180);
		int y1_value = 400 + 100*sin(radians);
		decIntToDecStr(y1_value, &num, &numLen);
		stringLCD(num, numLen, 0, 0);
		output_dac2(y1_value);
		lcd_delayus(500);	//Defines the time interval between data points
	}*/
	
	
	
}
