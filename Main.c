//Includes
#include <stdio.h>
#include "switch.h"
#include "lcd.h"
#include "DAC.h"
//Definitions
#define name "Jacob Rae"

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

	stringLCD(name, sizeof(name)/sizeof(name[0])-1, 0, 0); //Command to display name as defined at top of main.c on LCD
	char* num;	//Creates a pointer to be used to store a string conversion of a number - pointer necessary because of pointer decay when moving between .c files
	int numLen;	//Variable to store length of string conversion of number
	decIntToDecStr(56795, &num, &numLen);
	stringLCD(num, numLen, 1, 0);	//Command to display decimal number on LCD
	decIntToHexStr(56795, &num, &numLen);
	stringLCD(num, numLen, 1, numLen+3); //Command to display hexadecimal number on LCD
	//endlessScrollLCD(); //Causes LCD screen to scroll endlessly
	
	//Delay before changing to 4-bit mode
	lcd_delayus(20000);
	RCC->AHB1ENR |= ~RCC_AHB1ENR_GPIOBEN;	//Turns port B off to show that 4-bit initialisation works on its own
	lcd_delayus(20000);
	
	initLCD4();	//Initialisation of LCD in 4-bit mode
	cmdLCD(LCD_LINE1);
	LCD_CLR();
	
	char message[] = "4-bit mode";	//Creates a variable for a message to be displayed on the LCD
	//stringLCD(message, sizeof(message)/sizeof(message[0])-1, 0, 0); //Command to display message as defined above on LCD
	stringLCD(message, sizeof(message)/sizeof(message[0])-1, 1, 5); //Command to display message as defined above on LCD second line shifted to the right
	char messageHidden[] = "The Blue button scrolls.";	//Creates a variable for a message that requires blue button functionality to see
	stringLCD(messageHidden, sizeof(messageHidden)/sizeof(messageHidden[0])-1, 0, 16);	//Displayes a message ont he LCD which requires scrolling to see

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
	
	
	//------CURRENTLY NOT WORKING AS INTENDED------
	
	while(1)	//While loop for DAC output
	{
		stringLCD("DAC active", 10, 0, 0);	//Used for testing so I could tell DACs were meant to be on
		//Turns output high on both DACS
		output_dac1(1);
		output_dac2(1);
		lcd_delayus(100000);	//Delay so high level can be seen
		//Sets output low on both DACs
		output_dac1(0);
		output_dac2(0);
		lcd_delayus(100000);	//Delay so low level can be seen
	}
	
}
