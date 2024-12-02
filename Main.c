//Includes
#include "lcd.h"

int main(void)
{
	//Initialisation
	initLCD4();
	cmdLCD(LCD_LINE1);
	
	LCD_CLR();
	
	char name[] = "Example";
	//stringLCD(name, sizeof(name)/sizeof(name[0]), 0, 0);
	stringLCD(name, sizeof(name)/sizeof(name[0]), 1, 2);	//Command to display name as defined at top of file, needs string length
	
	//putLCD('A');
	//putLCD('a');
	
	//cmdLCD(0b10100);
	
	//putLCD('B');
	while(1);
}
