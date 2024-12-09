//Includes
#include <stdio.h>
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
	stringLCD(example, sizeof(example)/sizeof(example[0])-1, 1, 0);	//Command to display name as defined at top of file, needs string length
	
	char intToStr[100];	//Character array used to store integers that have been converted to character arrays for use as effective strings
	int num = 2701;	//Integer to be converted into string
	sprintf(intToStr, "%d", num);	//Converts an integer into a character array
	stringLCD(intToStr, floor(log10(abs(num)))+1, 1, sizeof(example)/sizeof(example[0])-1); //Prints character array of converted integer
	
	endlessScrollLCD(); //Causes LCD screen to scroll endlessly
	
	
	while(1);
}
