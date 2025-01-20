#include <stm32f4xx.h>

#ifndef _LCD_H_	//Ensures no double definition of _LCD_H_
#define _LCD_H_

#define LCD_PORT	GPIOD	//Defines the port used for the LCD (port D)
#define LCD_RS_pin	11	//Defines pin used as LCD register select pin
#define LCD_RW_pin	12	//Defines pin used as LCD read/write pin
#define LCD_E_pin		13	//Defines pin used as LCD enable pin

#define LCD_D0_pin	0



#define LCD_LINE1		0x80	//Defines location of top line of LCD
#define LCD_LINE2		0xc0	//Defines location of bottom line of LCD

#define set_LCD_RS()	LCD_PORT->BSRR=(1u<<LCD_RS_pin)	//Defines command to set LCD register select pin
#define clr_LCD_RS()	LCD_PORT->BSRR=(1u<<(LCD_RS_pin+16))	//Defines command to clear LCD register select pin
#define set_LCD_RW()	LCD_PORT->BSRR=(1u<<LCD_RW_pin)	//Defines command to set LCD read/write pin
#define clr_LCD_RW()	LCD_PORT->BSRR=(1u<<(LCD_RW_pin+16))	//Defines command to clear LCD read/write pin
#define set_LCD_E()		LCD_PORT->BSRR=(1u<<LCD_E_pin)	//Defines command to set LCD enable pin
#define clr_LCD_E()		LCD_PORT->BSRR=(1u<<(LCD_E_pin+16))	//Defines command to clear LCD enable pin

#define LCD_CLR()		cmdLCD(0x01)	//Defines command to clear LCD display

#define set_LCD_bus_input()		LCD_PORT->MODER&=~(0xffff<<(2*LCD_D0_pin))
#define set_LCD_bus_output()	LCD_PORT->MODER|=(0x5555<<(2*LCD_D0_pin))

void lcd_delayus(unsigned int us); //Wait defined time using approximate block delay
void WaitLCDBusy(void); //Wait until LCD is available
void set_LCD_data(unsigned char d);  //Clears and sets data lines on LCD
void LCD_strobe(void); //10us high pulse on LCD enable line
void LCD_home(void); //Moves cursor to 0,0
void cmdLCD(unsigned char cmd); //sends a byte to the LCD control register
void putLCD(unsigned char put); //Prints character to LCD
void stringLCD(char text[], int length,int line, int pos); //Prints string to LCD in a given position
void decIntToDecStr(int num, char* a[], int* b);
void decIntToHexStr(int num, char* a[], int* b);
void scrollLCD(int time);	//Causes LCD screen to scroll a given number of positions, currently a blocking function pending timers and interrupts work
void endlessScrollLCD(void);	//Causes LCD screen to scroll endlessly, currently a blocking function pending timers and interrupts work
void initLCD4(void); //Initialises LCD in 4-bit mode
void initLCD8(void); //Initialises LCD in 8-bit mode

#endif
