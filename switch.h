#include <stm32f4xx.h>

#ifndef _switch_H_	//Ensures no double definition of _switch_H_
#define _switch_H_

//Blue button is C-16

//Outputs
#define LED_PORT GPIOB	//Defines the port used for LED outputs
#define LED_GRN 0	//Defines the pin used by green LED
//Inputs
	//Blue button
	#define BLU_PORT GPIOC	//Defines the port used by the blue button
	#define BLU_BTN 13	//Defines the pin used by the blue button
	//ABCD buttons
	#define FOUR_BTN_PORT GPIOG	//Defines the port used for switch inputs
	#define BTN0	0	//Defines pin used by button 0
	#define BTN1	1	//Defines pin used by button 1
	#define BTN2	2	//Defines pin used by button 2
	#define BTN3	3	//Defines pin used by button 3
//Initialisation commands
#define FOUR_BTN_PORT_ENABLE() 		RCC->AHB1ENR 					|= RCC_AHB1ENR_GPIOGEN							//Defines command to clock to four button port (port G) to enable it

#define set_BTN_input(BTN_num)				FOUR_BTN_PORT->MODER 		|= 0ul<<(2*BTN_num)	//Defines command to set a button of given number to input mode
#define set_BTN_lowspeed(BTN_num)			FOUR_BTN_PORT->OSPEEDR 	|= 0ul<<(2*BTN_num)	//Defines command to set a button of given number to 2MHz (low speed) operation to save power
#define set_BTN_not_pull_up(BTN_num)	FOUR_BTN_PORT->PUPDR 		|= 3ul<<(2*BTN_num)	//Defines command to set a button of given number to not use internal pull up configuration
//Activation commands
#define LEDon(PORT, BIT)   ((PORT->ODR) |= (1U << BIT))		// Macro to set port bit - not BSRR (Here to test responsiveness of buttons)
#define LEDoff(PORT, BIT)   ((PORT->ODR) &= ~(1U << (BIT))) // Macro to clear port bit - not BSRR (Here to test responsiveness of buttons)

void LED_INIT(GPIO_TypeDef *PORT, unsigned int BIT);	//Initialises green traffic LED
void BLU_BTN_INIT(GPIO_TypeDef *PORT, unsigned int BIT);	//Initialises Blue button
void FOUR_BTN_INIT(GPIO_TypeDef *PORT, unsigned int BIT0, unsigned int BIT1, unsigned int BIT2, unsigned int BIT3);	//Initialises the four directional buttons
void Toggle_LED (void); //Toggles green LED
void switchInit(void);	//Initialises 4 buttons
int readBTNValue(GPIO_TypeDef *PORT, unsigned int BIT);	//Reads whether a specified 1 of the 4 buttons has been pressed - made easier by the 4 buttons using pins 0,1,2,3

#endif