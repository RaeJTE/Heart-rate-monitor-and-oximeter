#include "lcd.h"

int main(void)
{
	initLCD();
	cmdLCD(LCD_LINE1);
	
	char name[] = "Jacob Rae"; //Phrase to display
	show(name, sizeof(name)/sizeof(name[0]));	//Command to display phrase called "name"
	
	lcd_delayus(100000);
	
	char greeting[] = "Hello world"; //Phrase to display
	show(greeting, sizeof(greeting)/sizeof(greeting[0])); //Command to display phrase called "greeting"
	
	for(int i = 0; i<41-sizeof(greeting)/sizeof(greeting[0]); i++){
		cmdLCD(0b10100);
	}
	putLCD('A');

	while(1);
}
