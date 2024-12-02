//Includes
#include "lcd.h"

int main(void)
{
	//Initialisation
	initLCD();
	cmdLCD(LCD_LINE1);
	
	char name[] = "Example";
	stringLCD(name, sizeof(name)/sizeof(name[0]), 1, 2);	//Command to display name as defined at top of file, needs string length
	
	while(1);
}
