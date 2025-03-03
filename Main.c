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
//#include "MPU_stuff.h"	//MPU init breaking LCD for some reason?
//Definitions
#define names "Edward Drover - Taylor and Jacob Rae"
#define pi 3.14159

//LCD 4-bit mode not working

// Global Variables
int16_t Accel_X_RAW = 0, Accel_Y_RAW = 0, Accel_Z_RAW = 0;
float Ax, Ay, Az;
uint8_t check;

int main(void)
{
	//Initialisation of switches
	BLU_BTN_INIT(BLU_PORT, BLU_BTN);
	FOUR_BTN_INIT(FOUR_BTN_PORT, BTN0, BTN1, BTN2, BTN3);
	//Initialisation of LEDs
	//LED_INIT();
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
	//MPU6050_Init();
	//Initialises Usart
	init_USART();
	//Initialises RGB LED strip
	init_GPIO_RGB_Bar();
	//Initialises segment LED display
	//GPIO_Init();
	
	int n = 0;
	int test[] = {1, 2, 3};
	char* num;	//Creates a pointer to be used to store a string conversion of a number - pointer necessary because of pointer decay when moving between .c files
	int numLen;	//Variable to store length of string conversion of number

	for(n = 0; n<10; n++)
	{
		stringLCD("Begin", 5, 0, n);
		lcd_delayus(100000);
		LCD_CLR();
		//test[n] = read_adc();
		decIntToDecStr(test[n], &num, &numLen);
		stringLCD(num, numLen, 0, n);
		lcd_delayus(100000);
		/*test[n] = read_adc();
		decIntToDecStr(test[n], &num, &numLen);
		stringLCD(num, numLen, 1, n);
		lcd_delayus(100000);*/
		LCD_CLR();
	}
	
	stringLCD("End", 3, 0, n);
	lcd_delayus(100000);
	
	for(int i = 0; i<5; i++)
	{
		LCD_CLR();
		test[i] = read_adc();
		decIntToDecStr(test[i], &num, &numLen);
		stringLCD(num, numLen, 0, i);
		lcd_delayus(100000);
	}
	
	char* num2;	//Creates a pointer to be used to store a string conversion of a number - pointer necessary because of pointer decay when moving between .c files
	int numLen2;	//Variable to store length of string conversion of number
	int test2[] = {};
	
	for(int i = 0; i<5; i++)
	{
		LCD_CLR();
		test2[i] = read_adc();
		decIntToDecStr(test2[i], &num2, &numLen2);
		stringLCD(num2, numLen2, 0, i);
		lcd_delayus(100000);
	}
	
	
	
	stringLCD("Code complete", 13, 0,0);
	output_dac1(0);
	lcd_delayus(500000);
	LCD_CLR();
	
}
