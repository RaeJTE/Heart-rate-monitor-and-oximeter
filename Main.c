//Includes
#include <stdio.h>
#include "switch.h"
#include "lcd.h"
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
	
	initLCD4();	//Initialisation of LCD in 4-bit mode
	cmdLCD(LCD_LINE1);
	LCD_CLR();
	
	char message[] = "4-bit mode";	//Creates a variable for a message to be displayed on the LCD
	stringLCD(message, sizeof(message)/sizeof(message[0])-1, 0, 0); //Command to display message as defined above on LCD
	stringLCD(message, sizeof(message)/sizeof(message[0])-1, 1, 5); //Command to display message as defined above on LCD second line shifted to the right
	char messageHidden[] = "The Blue button scrolls.";	//Creates a variable for a message that requires blue button functionality to see
	stringLCD(messageHidden, sizeof(messageHidden)/sizeof(messageHidden[0])-1, 0, 16);
	
	while(1)
	{
		lcd_delayus(2000);
		if (readBTNValue(BLU_PORT, BLU_BTN))
		{
			scrollLCD(1);
			Toggle_LED();
		}
	}
	
}
