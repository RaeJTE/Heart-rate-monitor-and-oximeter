//Includes
#include <stdio.h>
#include "switch.h"
#include "lcd.h"
//Definitions
#define name "Jacob Rae"

int main(void)
{
	//Initialisation of switches
	switchInit();
	//Initialisation of green traffic LED
	LEDInit();
	//Initialisation of LCD
	initLCD4();
	cmdLCD(LCD_LINE1);
	LCD_CLR();

	
	stringLCD(name, sizeof(name)/sizeof(name[0])-1, 0, 0); //Command to display name as defined at top of main.c on LCD
	char* num;	//Creates a pointer to be used to store a string conversion of a number - pointer necessary because of pointer decay when moving between .c files
	int numLen;	//Variable to store length of string conversion of number
	decIntToDecStr(56795, &num, &numLen);
	stringLCD(num, numLen, 1, 0);	//Command to display decimal number on LCD
	//decIntToHexStr(56795, &num, &numLen);
	//stringLCD(num, numLen, 1, 0); //Command to display hexadecimal number on LCD
	//endlessScrollLCD(); //Causes LCD screen to scroll endlessly
	
	int pin_0_prev = 0;
	while(1)
	{
		
		/*int pin_0_press = readBTNValue(0);
		if(pin_0_press == 1 && pin_0_prev == 0)
		{
			scrollLCD(1);
		}
		pin_0_prev = pin_0_press;*/
		lcd_delayus(20000);
		Toggle_LED();
	}
	
}
