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
#include "segments.h"
#include "RGB_Bar.h"
#include "i2c.h"
#include "MPU_stuff.h"
#include "usart.h"
#include "timer.h"
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
	//Initialisation of RGB_Bar
	init_GPIO_RGB_Bar();
	//Initialisation of Segments
	GPIO_Init();
	//Initialisation of I2C
	I2C2_Config();
	//Initialisation of MPU
	MPU6050_Init();
	//Initialisation of USART
	init_USART();
	//Initialisation of timer 1
	init_Timer1();
	
	int n = 0;
	int test = 0;
	char* num;	//Creates a pointer to be used to store a string conversion of a number - pointer necessary because of pointer decay when moving between .c files
	int numLen;	//Variable to store length of string conversion of number
	while(1)
	{
		stringLCD("Begin", 5, 0, n);
		lcd_delayus(100000);
		LCD_CLR();
		test = read_adc();
		decIntToDecStr(test, &num, &numLen);
		stringLCD(num, numLen, 0, n);
		lcd_delayus(10000);
		n++;
		test = read_adc();
		decIntToDecStr(test, &num, &numLen);
		stringLCD(num, numLen, 1, n);
		lcd_delayus(100000);
		LCD_CLR();
	}
	
	for(int i = 0; i<5; i++)
	{
		LCD_CLR();
		test = read_adc();
		decIntToDecStr(test, &num, &numLen);
		stringLCD(num, numLen, 0, i);
		lcd_delayus(100000);
	}
	
	char* num2;	//Creates a pointer to be used to store a string conversion of a number - pointer necessary because of pointer decay when moving between .c files
	int numLen2;	//Variable to store length of string conversion of number
	int test2 = 0;
	
	for(int i = 0; i<5; i++)
	{
		LCD_CLR();
		test2 = read_adc();
		decIntToDecStr(test2, &num2, &numLen2);
		stringLCD(num2, numLen2, 0, i);
		lcd_delayus(100000);
	}
	
	
	stringLCD("Code complete", 13, 0,0);
	output_dac1(0);
	lcd_delayus(500000);
	LCD_CLR();
	
	
}
