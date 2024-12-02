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

void initLCD(void)
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
	clr_LCD_RS();					//all lines default low
	clr_LCD_RW();
	clr_LCD_E();
	
	lcd_delayus(40000);		//40ms startup delay
	cmdLCD(0b0011<<4);
	lcd_delayus(50);
	cmdLCD(0b0010<<4);	//Function set: 2 Line, 4-bit, 5x7 dots
	cmdLCD(0b1000<<4);
	lcd_delayus(50);
	cmdLCD(0b1100<<4);	//Display on, Cursor blinking command
	lcd_delayus(40);
	cmdLCD(0b0001<<4);	//Clear LCD
	lcd_delayus(1540);
	cmdLCD(0b0110<<4);	//Entry mode, auto increment with no shift
}

void stringLCD(char text[], int length) //To print strings on LCD, length must be calculated before as array decays into pointer to array when passed into function
{
	WaitLCDBusy();				//wait for LCD to be not busy
	LCD_CLR();
	for(int i=0; i<length-1; i++)
	{
		WaitLCDBusy();				//wait for LCD to be not busy
		putLCD(text[i]);
	}
	
}


