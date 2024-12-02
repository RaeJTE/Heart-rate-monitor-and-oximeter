//Includes
#include "lcd.h"

int main(void)
{
	//Initialisation
	initLCD();
	cmdLCD(LCD_LINE1);
	
	char name[] = "Example";
	stringLCD(name, sizeof(name)/sizeof(name[0]));	//Command to display name as defined at top of file, needs string length
	
/*	lcd_delayus(300000);
	
	//Moving cursor
	for(int i = 0; i<41-sizeof(name)/sizeof(name[0]); i++){
		cmdLCD(0b10100);
	}
	
	char project[] = "Proj200";
	stringLCD(project, sizeof(project)/sizeof(project[0]));
*/
	
	
	while(1);
}
