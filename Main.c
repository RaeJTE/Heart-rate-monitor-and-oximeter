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
extern unsigned short ADC_DATA_RGB;
extern int accel_check;
int accel_check = 0;
int16_t Accel_X_RAW = 0, Accel_Y_RAW = 0, Accel_Z_RAW = 0;
int16_t Accel_X_PREV = 0, Accel_Y_PREV = 0, Accel_Z_PREV = 0;
float Ax, Ay, Az;
uint8_t check;
int j = 0;
unsigned int int_part = 0;
unsigned int frac_part = 0;
extern volatile uint8_t ADCout[15*samplingRate];
float copyADCout[15*samplingRate];	//Equivalent arry to above but that is not updated by interrupts

int main(void)
{
	
	SystemCoreClockUpdate();  // clock is updated
	

	//PLL_Config(); DO NOT USE BUGGERS THINGS UP (think it redefines clock)
	init_ADC();  // Configure ADC for Potentiometer (PA0)
	//init_DAC();  // Configure DAC for analog output (PA5) A5 used for red monitor led
	//Init_LED();  // Configure LEDs (PC2, PC3, PC6)
	//init_Timer1();
	//BLUE PWM STUFF;
	LED_INIT();				 // Initialize LEDS
	Toggle_LED('G');	 // Turn on green for refference
	Hold_Blue_LED();   // Hold Blue LED at 50% brightness
	//Init_Timer3(5);		 // BLUE    Set interrupt frequency to 1000 Hz (toggle frequency of blue LED)


	//Init_Timer2();  // Initialize Timer 2 for 10 Hz adc sample
		unsigned int i;
	//	PLL_Config();
	//	SystemCoreClockUpdate();

	init_USART();

	while(1)
	{		

		process_USART_Input();
		
		
	
		{
			__NOP();
		}
	}
	
	
	
	/*
	*********************************************
	**********SIMULATED TEST SIGNALS*************
	*********************************************
	*/
	
	
	
	/*int dataPoints = 360000;	//Defines how many data points we want to take
	//For some reason previous code kept breaking when I used for loops here - possible from use of i specificly?
	
	for (int i = 0; i < dataPoints; i++)
	{
		float radians = i*(pi/180);
		int y1_value = 400 + 100*sin(radians);
		int y2_value = 400 + 100*sin(radians) - 80*cos(2*radians);
		decIntToDecStr(y1_value, &num, &numLen);
		stringLCD(num, numLen, 0, 0);
		output_dac2(y1_value);
		lcd_delayus(500);	//Defines the time interval between data points
	}*/
	
	
	
}
