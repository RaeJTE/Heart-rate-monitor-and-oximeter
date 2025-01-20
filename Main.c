//Includes
#include <stdio.h>
#include "switch.h"
#include "lcd.h"
//Definitions
#define name "Jacob Rae"

int main(void)
{
	//Initialisation
	initLCD4();
	cmdLCD(LCD_LINE1);
	
	LCD_CLR();
	

	
	char example[] = "Proj200 with guest number: ";
	stringLCD(name, sizeof(name)/sizeof(name[0])-1, 0, 0);
	stringLCD(example, sizeof(example)/sizeof(example[0])-1, 0, 10);	//Command to display name as defined at top of file, needs string length
	endlessScrollLCD(); //Causes LCD screen to scroll endlessly
	
	while(1)
	{
		int pin_0_on = readPinValue(0);
	
		char* num;
		int numLen;
		decIntToDecStr(56795, &num, &numLen);
		stringLCD(num, numLen, 0, 0);
		decIntToHexStr(1, &num, &numLen);
		stringLCD(num, numLen, 0, sizeof(name)/sizeof(name[0])+sizeof(example)/sizeof(example[0])+2);

	
	}
	while(1);
}
