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
	
	
	char a;
	a	= numToArray(2587);
	char* b = &a;
	//stringLCD(a[1], 4, 0, 0);
	//putLCD(a);
	for (int i = 0; i<4; i++)
	{
		putLCD(*b);
		b++;
	}
	
	char example[] = "Proj200 with guest number: ";
	//stringLCD(name, sizeof(name)/sizeof(name[0]), 0, 0);
	//stringLCD(example, sizeof(example)/sizeof(example[0]), 1, 2);	//Command to display name as defined at top of file, needs string length
	
	//endlessScrollLCD();
	
	
	while(1);
}
