#include <stm32f4xx.h>

#ifndef _switch_H_	//Ensures no double definition of _switch_H_
#define _switch_H_

//Outputs
#define LED_PORT GPIOC	//Defines the port used for LED outputs
#define LED_GRN 6	//Defines the pin used by green traffic LED
//Inputs
#define switch_PORT GPIOG	//Defines the port used for switch inputs
#define BTN0_PIN	0	//Defines pin used by button 0
#define BTN1_PIN	1	//Defines pin used by button 1
#define BTN2_PIN	2	//Defines pin used by button 2
#define BTN3_PIN	3	//Defines pin used by button 3
//Initialisation commands
#define LED_PORT_ENABLE()				RCC->AHB1ENR					|= 1<<2							//Defines command to clock to LED port to enable it
#define switch_PORT_ENABLE() 		RCC->AHB1ENR 					|= 1<<5							//Defines command to clock to switch port to enable it

#define set_LED_GRN_output()		LED_PORT->MODER				|= 1<<(2*LED_GRN)	//Defines command to set green traffic LED to output mode
#define set_LED_GRN_pushPull()	LED_PORT->OTYPER 			|= 0<<(1*LED_GRN)		//Defines command to set green traffic LED to push pull output mode
#define set_LED_GRN_lowspeed()	LED_PORT->OSPEEDR 		|= 0<<(2*LED_GRN)	//Defines command to set green traffic LED to 2MHz (low speed) operation to save power
#define set_LED_GRN_pull_up()		LED_PORT ->PUPDR 			|= 0<<(2*LED_GRN)	//Defines command to set green traffic LED to internal pull up configuration

#define set_BTN_input(BTN_num)				switch_PORT->MODER 		|= 0<<(2*BTN_num)	//Defines command to set a button of given number to input mode
#define set_BTN_lowspeed(BTN_num)			switch_PORT->OSPEEDR 	|= 0<<(2*BTN_num)	//Defines command to set a button of given number to 2MHz (low speed) operation to save power
#define set_BTN_pull_up(BTN_num)			switch_PORT->PUPDR 		|= 1<<(2*BTN_num)	//Defines command to set a button of given number to internal pull up configuration



void LEDInit(void);	//Initialises green traffic LED
void Toggle_LED (void); //Toggles LED
void switchInit(void);	//Initialises 4 buttons
int readBTNValue(int pin);	//Reads whether a specified 1 of the 4 buttons has been pressed - made easier by the 4 buttons using pins 0,1,2,3

#endif