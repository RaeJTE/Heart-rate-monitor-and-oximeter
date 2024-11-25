#include "lcd.h"

int main(void)
{
	initLCD();
	cmdLCD(LCD_LINE1);
	
	char name[] = "Jacob Rae"; //Phrase to display
	show(name, sizeof(name)/sizeof(name[0]));	//Command to display phrase called "name"
	
	lcd_delayus(300000);
	
	char greeting[] = "Hello world"; //Phrase to display
	show(greeting, sizeof(greeting)/sizeof(greeting[0])); //Command to display phrase called "greeting"
	while(1);
}
