#include <stdio.h>
#include <math.h>
#include "lcd.h"

void lcd_delayus(unsigned int us)		//blocking delay for LCD, argument is approximate number of micro-seconds to delay
{
	unsigned char i;
	while(us--)
	{
		for(i=0; i<SystemCoreClock/4000000; i++){__NOP();}
	}
}

void WaitLCDBusy(void)
{
	set_LCD_bus_input(); //So LCD bus receives inputs
	set_LCD_RW();	//So microcontroller looking to read from LCD not write to it
	clr_LCD_RS();
	int port = 1;
	while(port)	//So code loops until bit 7 (indicating LCD busy) clears
	{
		set_LCD_E();
		port = LCD_PORT->IDR & (0b1<<7);
		clr_LCD_E();
	}
	set_LCD_bus_output(); //So LCD can be updated again
	
}

void set_LCD_data(unsigned char d)
{
	LCD_PORT->BSRR=(0xff<<(LCD_D0_pin+16));	//clear data lines
	LCD_PORT->BSRR=(d<<LCD_D0_pin);					//put data on lines
}

void LCD_strobe(void)		//10us high pulse on LCD enable line
{
	lcd_delayus(10);
	set_LCD_E();
	lcd_delayus(10);
	clr_LCD_E();
}

void LCD_home (void)
{
	cmdLCD(0b10);
}

void cmdLCD(unsigned char cmd)		//sends a byte to the LCD control register
{
	WaitLCDBusy();				//wait for LCD to be not busy
	clr_LCD_RS();					//control command
	clr_LCD_RW();					//write command
	set_LCD_data(cmd);		//set data on bus
	LCD_strobe();					//apply command
}

void putLCD(unsigned char put)	//sends a char to the LCD display
{
	WaitLCDBusy();				//wait for LCD to be not busy
	set_LCD_RS();					//text command
	clr_LCD_RW();					//write command
	set_LCD_data(put);		//set data on bus
	LCD_strobe();					//apply command
}

void stringLCD(char text[], int length, int line, int pos) //To print strings on LCD, length must be calculated before as array decays into pointer to array when passed into function
	//for length use -1 with length of character array to remove end signifying character, not needed for intToStr length as floor(log10(abs()))) method does not look at end signifying characters
{
	WaitLCDBusy();				//wait for LCD to be not busy
	LCD_home();
	if(line == 1)	//Moves to second line if told to do so via line variable
	{
		for(int i = 0; i<40; i++)	//Moves a given number of spaces forward on the LCD
		{
			cmdLCD(0b10100);
		}
	}
	for(int i = 0; i<pos; i++)	//Moves a given number of spaces forward on the LCD
	{
		cmdLCD(0b10100);
	}
	for(int i=0; i<length; i++)
	{
		putLCD(text[i]);
	}
	
}

void decIntToDecStr(int numIn, char* a[], int* b) //Converts a decimal integer into a string that can be printed
{
	sprintf(*a, "%d", numIn);
	*b = floor(log10(numIn))+1;
}

void decIntToHexStr(int numIn, char* a[], int* b) //Converts a decimal integer into a string of the hexadecimal value of that integer
{
	sprintf(*a, "%x", numIn);
	*b = floor((log(numIn))/log(16))+1;
}

void scrollLCD(int places)	//Causes LCD screen to scroll a given number of positions, currently a blocking function pending timers and interrupts work
{
	for(int i = 0; i<places; i++)
	{
		lcd_delayus(30000);
		cmdLCD(0b11000);
	}
}

void endlessScrollLCD(void)	//Causes LCD screen to scroll endlessly, currently a blocking function pending timers and interrupts work
{
	while(1)
	{
		lcd_delayus(30000);
		cmdLCD(0b11000);
	}
}

void initLCD4(void)	//Initialises the LCD in 4-bit mode
{
		SystemCoreClockUpdate();
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;	//enable LCD port clock
	
	
			//CONFIG LCD GPIO PINS
		LCD_PORT->MODER&=~(					//clear pin direction settings
			(3u<<(2*LCD_RS_pin))
			|(3u<<(2*LCD_RW_pin))
			|(3u<<(2*LCD_E_pin))
			|(0xffff<<(2*LCD_D0_pin))
			);
	
	
	LCD_PORT->MODER|=(				//reset pin direction settings to digital outputs
			(1u<<(2*LCD_RS_pin))
			|(1u<<(2*LCD_RW_pin))
			|(1u<<(2*LCD_E_pin))
			|(0x5555<<(2*LCD_D0_pin)) //0x5555 = 0b 0101 0101 0101 0101
		);

	
			//LCD INIT COMMANDS
	clr_LCD_RS();				//all lines default low
	clr_LCD_RW();
	clr_LCD_E();
	
	lcd_delayus(41000);		//41ms startup delay
	cmdLCD(0b0011);	//Function set 1: 4-bit, this requires all other instructions to be sent in 2 lines (see page 42 of HD44780U datasheet - individual commands on page 24)
	
	lcd_delayus(60);
	cmdLCD(0b0010); //Function set 2: These lines sets 4-bit operation, 2-line display, 5x8 dot character display
	cmdLCD(0b1000);
	
	lcd_delayus(60);
	cmdLCD(0b0010); //Function set 3: These lines sets 4-bit operation, 2-line display, 5x8 dot character display
	cmdLCD(0b1000);
	
	lcd_delayus(60);
	cmdLCD(0b0000);	//Display on
	cmdLCD(0b1110);
	
	lcd_delayus(60);
	cmdLCD(0b0000);	//Clear LCD
	cmdLCD(0b0001);
	
	lcd_delayus(2000);
	cmdLCD(0b0000);	//Entry mode: auto increment with no shift
	cmdLCD(0b0110);
}

void initLCD8(void)	//Initialises the LCD in 4-bit mode
{
		SystemCoreClockUpdate();
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;	//enable LCD port clock
	
	
			//CONFIG LCD GPIO PINS
		LCD_PORT->MODER&=~(					//clear pin direction settings
			(3u<<(2*LCD_RS_pin))
			|(3u<<(2*LCD_RW_pin))
			|(3u<<(2*LCD_E_pin))
			|(0xffff<<(2*LCD_D0_pin))
			);
	
	
	LCD_PORT->MODER|=(				//reset pin direction settings to digital outputs
			(1u<<(2*LCD_RS_pin))
			|(1u<<(2*LCD_RW_pin))
			|(1u<<(2*LCD_E_pin))
			|(0x5555<<(2*LCD_D0_pin)) //0x5555 = 0b 0101 0101 0101 0101
		);

	
			//LCD INIT COMMANDS
	clr_LCD_RS();				//all lines default low
	clr_LCD_RW();
	clr_LCD_E();
	
	lcd_delayus(41000);		//41ms startup delay
	cmdLCD(0b00111000);	//Function set: 2 Line, 8-bit, 5x7 dots
	lcd_delayus(60);
	cmdLCD(0b00001100);	//Display on, Cursor blinking command
	lcd_delayus(60);
	cmdLCD(0b00000001);	//Clear LCD
	lcd_delayus(2000);
	cmdLCD(0b00000110);	//Entry mode, auto increment with no shift
}

