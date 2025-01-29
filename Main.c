//Includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "switch.h"
#include "lcd.h"
#include "DAC.h"
#include "ADC.h"
//Definitions
#define name "Jacob Rae"
#define pi 3.14159

//4-bit mode not working

int main(void)
{
	//Initialisation of switches
	BLU_BTN_INIT(BLU_PORT, BLU_BTN);
	//Initialisation of green traffic LED
	LED_INIT(LED_PORT, LED_GRN);
	//Initialisation of LCD in 8-bit mode
	initLCD8();
	cmdLCD(LCD_LINE1);
	LCD_CLR();
	//Initiliases the ADC and DAC
	init_ADC();
	init_DAC();
	
	//Creating variables to be used later
	unsigned short ADC_DATA;	//Variable to store ADC data, rapidly overwritten

	stringLCD(name, sizeof(name)/sizeof(name[0])-1, 0, 0); //Command to display name as defined at top of main.c on LCD
	char* num;	//Creates a pointer to be used to store a string conversion of a number - pointer necessary because of pointer decay when moving between .c files
	int numLen;	//Variable to store length of string conversion of number
	decIntToDecStr(56795, &num, &numLen);
	stringLCD(num, numLen, 1, 0);	//Command to display decimal number on LCD
	decIntToHexStr(56795, &num, &numLen);
	stringLCD(num, numLen, 1, numLen+3); //Command to display hexadecimal number on LCD
	//endlessScrollLCD(); //Causes LCD screen to scroll endlessly
	
	lcd_delayus(100000);	//Delay to allow reading of LCD display
	
	LCD_CLR();
	char message[] = "8-bit mode";	//Creates a variable for a message to be displayed on the LCD
	//stringLCD(message, sizeof(message)/sizeof(message[0])-1, 0, 0); //Command to display message as defined above on LCD
	stringLCD(message, sizeof(message)/sizeof(message[0])-1, 1, 5); //Command to display message as defined above on LCD second line shifted to the right
	char messageHidden[] = "The Blue button scrolls.";	//Creates a variable for a message that requires blue button functionality to see
	stringLCD(messageHidden, sizeof(messageHidden)/sizeof(messageHidden[0])-1, 0, 16);	//Displayes a message ont he LCD which requires scrolling to see
	
	lcd_delayus(100000);	//Delay to allow reading of LCD display

	int BLUE_BTN_PRESSES = 0; //Variable which will be used to check whether the blue button is being held

	/*while(1)	//While loop to repeatedly check for button presses, may be replaced with interrupts once code is merged with partner's work
	{
		if(readBTNValue(BLU_PORT, BLU_BTN))	//Scrolls LCD when blue button is pressed, holding works to continuously scroll - holding long enough will activate endless scroll
		{
			scrollLCD(1);
			Toggle_LED();
			BLUE_BTN_PRESSES++;	//Used to check whether the blue button is being held
		}
		else
		{
			BLUE_BTN_PRESSES = 0;	//Used to indicate the blue button has been released
		}
		if(BLUE_BTN_PRESSES >= 10)	//If blue button is held (no releases are detected over 'held' period) activates endless scroll mode
		{
			endlessScrollLCD();
		}
		if(readBTNValue(FOUR_BTN_PORT, BTN0))	//Displays message saying when button 0 is pressed
		{
			stringLCD("Button 0 pressed", 16, 0, 0);
			lcd_delayus(100000);
			LCD_CLR();
		}
		if(readBTNValue(FOUR_BTN_PORT, BTN1))	//Displays message saying when button 1 is pressed
		{
			stringLCD("Button 1 pressed", 16, 0, 0);
			lcd_delayus(100000);
			LCD_CLR();
		}
		
		//Having issues with BTN2 and BTN3 detecting presses constantly - already added in pupdr resistors but maybe re-look at that
		
		if(readBTNValue(FOUR_BTN_PORT, BTN2))	//Displays message saying when button 2 is pressed
		{
			stringLCD("Button 2 pressed", 16, 0, 0);
			lcd_delayus(100000);
			LCD_CLR();
		}
		if(readBTNValue(FOUR_BTN_PORT, BTN3))	//Displays message saying when button 3 is pressed
		{
			stringLCD("Button 3 pressed", 16, 0, 0);
			lcd_delayus(100000);
			LCD_CLR();  
		}
		
		lcd_delayus(100);	//Switch debounce delay
	}*/
	
	LCD_CLR();
	
	
	//Arbitrary DC voltages on DAC1
	output_dac1(100);			//Generates a constant output from DAC2, use values from 0-900
	lcd_delayus(1000);
	output_dac1(400);			//Generates a constant output from DAC2, use values from 0-900 
	lcd_delayus(1000);
	output_dac1(72);			//Generates a constant output from DAC2, use values from 0-900 
	lcd_delayus(1000);
	
	unsigned short i = 0;	//For counting in loops
	while(i < 100)	//While loop for square wave DAC output, finite so multiple waves can be tested in succession
	{
		output_dac1(300);			//Generates a constant output from DAC1, use values from 0-8000ish based on values read in and re-outputted from LDR in intiial tests with example code
		lcd_delayus(1000);
		output_dac1(0);	//0s output from DAC2, with time delays creates a square wave
		lcd_delayus(100);
		i++;
	}

	i = 0;
	int dataPoints = 3600;	//Defines how many data points we want to take
	//For some reason previous code keeps breaking when I try to use arrays, so maybe avoid those.
	
	while (i < dataPoints)
	{
		float radians = i*(pi/180);
		int y1_value = 400 + 100*sin(radians);
		decIntToDecStr(y1_value, &num, &numLen);
		stringLCD(num, numLen, 0, 0);
		output_dac2(y1_value);
		i++;
		lcd_delayus(500);	//Defines the time interval between data points
	}
	
	i = 0;
	while(i < dataPoints)
	{
		int y2_value = 400+2*(100/pi)*asin(sin(i*2*pi/360));
		decIntToDecStr(y2_value, &num, &numLen);
		stringLCD(num, numLen, 0, 0);
		output_dac2(y2_value);
		i++;
		lcd_delayus(500);	//Defines the time interval between data points
	}
	
	//Complex wave made by multiplying two existing waves together with scaling factor to make it fit on the same display as previous two waves
	i = 0;
	while(i < dataPoints)
	{
		float radians = i*(pi/180);
		int y1_value = 400 + 100*sin(radians);
		int y2_value = 400+2*(100/pi)*asin(sin(i*2*pi/360));
		int y3_value = y1_value*y2_value/800;
		decIntToDecStr(y3_value, &num, &numLen);
		stringLCD(num, numLen, 0, 0);
		output_dac2(y3_value);
		i++;
		lcd_delayus(500);	//Defines the time interval between data points
		
	}
		
	stringLCD("Code complete", 13, 0,0);
	output_dac1(0);
	output_dac2(0);
	lcd_delayus(500000);
	LCD_CLR();
	
	
	//------CURRENTLY NOT WORKING AS INTENDED------
	
	
	/*
	//Delay before changing to 4-bit mode
	lcd_delayus(50000);
	RCC->AHB1ENR |= ~RCC_AHB1ENR_GPIOBEN;	//Turns port B off to show that 4-bit initialisation works on its own
	lcd_delayus(20000);
	
	initLCD4();	//Initialisation of LCD in 4-bit mode
	cmdLCD(LCD_LINE1);
	LCD_CLR();
	*/
	
	
}
