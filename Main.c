#include "lcd.h"

int main(void)
{
	initLCD();
	cmdLCD(LCD_LINE1);
	putLCD('J');
	putLCD('a');
	
	while(1);
}
