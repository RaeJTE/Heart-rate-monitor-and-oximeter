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
	//Initialisation of LCD
	initLCD4();
	cmdLCD(LCD_LINE1);
	LCD_CLR();

	char example[] = "Proj200 with guest number: ";
	stringLCD(name, sizeof(name)/sizeof(name[0])-1, 0, 0);
	stringLCD(example, sizeof(example)/sizeof(example[0])-1, 1, 0);	//Command to display name as defined at top of file, needs string lengt
	char* num;
	int numLen;
	//decIntToDecStr(56795, &num, &numLen);
	//stringLCD(num, numLen, 0, 0);	//Command to display decimal number on LCD
	decIntToHexStr(1, &num, &numLen);
	stringLCD(num, numLen, 1, sizeof(example)/sizeof(example[0])); //Command to display hexadecimal number on LCD
	//endlessScrollLCD(); //Causes LCD screen to scroll endlessly
	
	int pin_0_prev = 0;
	while(1)
	{
		int pin_0_press = readPinValue(0);
		if(pin_0_press == 1 && pin_0_prev == 0)
		{
			scrollLCD(1);
		}
		pin_0_prev = pin_0_press;
		lcd_delayus(20000);
	}
	
}
