#include <stm32f4xx.h>

#ifndef _switch_H_	//Ensures no double definition of _switch_H_
#define _switch_H_

//Outputs
#define LED_PORT GPIOC	//Defines the port used for LED outputs
#define LED_GRN 6	//Defines the pin used by green traffic LED
//Inputs
#define switch_PORT GPIOG	//Defines the port used for switch inputs
#define switch_PORT_ENABLE RCC->AHB1ENR |= (1<<5)
#define BTN0_pin	0	//Defines pin used by button 0
#define BTN1_pin	1	//Defines pin used by button 1
#define BTN2_pin	2	//Defines pin used by button 2
#define BTN3_pin	3	//Defines pin used by button 3
//Initialisation commands
#define set_LED_GRN_output LED_PORT->MODER |= (01<<(2*LED_GRN))	//Defines command to set green traffic LED to output mode
#define set_LED_GRN_pushPull LED_PORT->OTYPER |= (0<<(2*LED_GRN))	//Defines command to set green traffic LED to push pull output mode
#define set_BTN0_input()	switch_PORT->MODER |= 00<<(2*BTN0_pin)	//Defines command to set button 0 to input mode
#define set_BTN0_lowspeed() switch_PORT->OSPEEDER |= 00<<(2*BTN0_PIN)	//Defines command to set button 0 to low speed operation to save power
#define set_BTN0_pull_up() switch_PORT->PUPDR |= 01<<(2*BTN0_PIN)	//Defines command to set button 0 to pull up configuration




#endif