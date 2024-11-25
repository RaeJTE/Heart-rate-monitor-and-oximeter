#include "lcd.h"

int main(void)
{
	initLCD();
	cmdLCD(LCD_LINE1);
	putLCD('h');
	
	while(1);
}
