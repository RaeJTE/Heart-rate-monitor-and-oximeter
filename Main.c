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
//Definitions
#define name "Jacob Rae"
#define pi 3.14159
#define freq 10	//remember to also update value in timer.c Timer3 IRQ handler || If 1000 loop freezes after ~1s, if 200 breaks out of loop early or freezes after ~10s, if 100 loop freezes after ~20s

//4-bit mode not working

// Global Variables
int16_t Accel_X_RAW = 0, Accel_Y_RAW = 0, Accel_Z_RAW = 0;
float Ax, Ay, Az;
uint8_t check;
int readADC[15*freq];
int i = 0;

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
	//init_GPIO_RGB_Bar();
	//Initialisation of Segments
	//GPIO_Init();
	//Initialisation of I2C
	I2C2_Config();
	//Initialisation of MPU
	MPU6050_Init();
	//Initialisation of USART
	init_USART();
	//Initialisation of timers
	Init_Timer2();	//Used for delays
	Init_Timer3(freq);	//Used for reading ADC

	char* num;	//Creates a pointer to be used to store a string conversion of a number - pointer necessary because of pointer decay when moving between .c files
	int numLen;	//Variable to store length of string conversion of number
	
	output_dac1(0); //Max output at 65535	-	IR LED
	output_dac2(0);	//Max output at 65535	- RED LED
	
	int n = sizeof(readADC)/sizeof(readADC[0]);
	int test[n];
	
	memcpy(test, readADC, n * sizeof(readADC[0]));
		
	/*while(1)
	{
		decIntToDecStr(readADC[0], &num, &numLen);
		stringLCD(num, numLen, 0, 0);
		lcd_delayus(40000);
		LCD_CLR();
	};*/
	
	stringLCD("Begin", 5, 0, 0);
	decIntToDecStr(i, &num, &numLen);
	stringLCD(num, numLen, 1, 0);
	TIM2Delay(600);
	LCD_CLR();
	decIntToDecStr(i, &num, &numLen);
	stringLCD(num, numLen, 1, 0);
	TIM2Delay(1000);
	LCD_CLR();
	
	decIntToDecStr(1352523, &num, &numLen);
	stringLCD(num, numLen, 0, 0);
	TIM2Delay(1000);
	decIntToDecStr(234634634, &num, &numLen);
	stringLCD(num, numLen, 0, 0);
	TIM2Delay(1000);
	LCD_CLR();
		
	for(int j = 0; j < (15*freq)-1; j++)
	//int j = 0; while(j<(15*freq)-1)
	{
		decIntToDecStr(readADC[j], &num, &numLen);
		stringLCD(num, numLen, 0, 0);
		TIM2Delay(20);
		//LCD_CLR();
		//j++;
		stringLCD("Cont", 4, 1, 0);
		TIM2Delay(1000);
		LCD_CLR();
	}
	
	
	stringLCD("Code complete", 13, 0,0);
	output_dac1(0);
	output_dac2(0);
	TIM2Delay(50);
	LCD_CLR();
	
	
}
