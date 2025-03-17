#include "PeakDetection.h"

void readHeart(void)
{
	init_Timer1();
	
	int test[] = {};
	char* num;	//Creates a pointer to be used to store a string conversion of a number - pointer necessary because of pointer decay when moving between .c files
	int numLen;	//Variable to store length of string conversion of number
		
	for(int i = 0; i < 10; i++)
	{
		stringLCD("Begin", 5, 0, i);
		lcd_delayus(100000);
		LCD_CLR();
		test[i] = read_adc();
		decIntToDecStr(test[i], &num, &numLen);
		stringLCD(num, numLen, 0, i);
		lcd_delayus(100000);
		LCD_CLR();
	}
	
}