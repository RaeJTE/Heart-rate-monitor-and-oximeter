#ifndef _LCD_H_
#define _LCD_H_
#define LCD_PORT	GPIOD
#define LCD_RS_pin	11
#define LCD_RW_pin	12
#define LCD_E_pin		13

#define LCD_D0_pin	0



#define LCD_LINE1		0x80
#define LCD_LINE2		0xc0

#define set_LCD_RS()	LCD_PORT->BSRR=(1u<<LCD_RS_pin)
#define clr_LCD_RS()	LCD_PORT->BSRR=(1u<<(LCD_RS_pin+16))
#define set_LCD_RW()	LCD_PORT->BSRR=(1u<<LCD_RW_pin)
#define clr_LCD_RW()	LCD_PORT->BSRR=(1u<<(LCD_RW_pin+16))
#define set_LCD_E()		LCD_PORT->BSRR=(1u<<LCD_E_pin)
#define clr_LCD_E()		LCD_PORT->BSRR=(1u<<(LCD_E_pin+16))

#define LCD_CLR()		cmdLCD(0x01)

#define set_LCD_bus_input()		LCD_PORT->MODER&=~(0xffff<<(2*LCD_D0_pin))
#define set_LCD_bus_output()	LCD_PORT->MODER|=(0x5555<<(2*LCD_D0_pin))

#include <stm32f4xx.h>

void lcd_delayus(unsigned int us); //Wait defined time using approximate block delay
void WaitLCDBusy(void); //Wait until LCD is available
void set_LCD_data(unsigned char d);  //Clears and sets data lines on LCD
void LCD_strobe(void); //10us high pulse on LCD enable line
void LCD_home(void); //Moves cursor to 0,0
void cmdLCD(unsigned char cmd); //sends a byte to the LCD control register
void putLCD(unsigned char put); //Prints character to LCD
void stringLCD(char text[], int length,int line, int pos); //Prints string to LCD
void scrollLCD(int time);
void endlessScrollLCD(void);
char numToArray(int var);	//
void initLCD4(void); //Initialises LCD in 4-bit mode
void initLCD8(void); //Initialises LCD in 8-bit mode

#endif
