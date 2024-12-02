//Includes
#include "lcd.h"
//Definitions
#define name "Jacob Theodore Eliott Rae"

int main(void)
{
	//Initialisation
	initLCD4();
	cmdLCD(LCD_LINE1);
	
	LCD_CLR();
	
	
	
	stringLCD(varString, varLen+1, 0, 0);
	
	char example[] = "Proj200 with guest number: ";
	//stringLCD(name, sizeof(name)/sizeof(name[0]), 0, 0);
	//stringLCD(example, sizeof(example)/sizeof(example[0]), 1, 2);	//Command to display name as defined at top of file, needs string length
	
	//endlessScrollLCD();
	
	
	while(1);
}
