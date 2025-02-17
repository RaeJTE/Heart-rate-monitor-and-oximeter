#include "switch.h"

void BLU_BTN_INIT(GPIO_TypeDef *PORT, unsigned int BIT)
{
	//Enable port
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	
	//Configure port
	PORT->MODER |= (0UL << (2*BIT));		//Set BIT to input mode
	PORT->OSPEEDR |= (0UL << (2*BIT));	//Make BIT Speed 2Mhz to save power
	PORT->PUPDR |= (3UL <<(2*BIT));			// Turn off Pullup and Pull down resistors for BIT
}

void FOUR_BTN_INIT(GPIO_TypeDef *PORT, unsigned int BIT0, unsigned int BIT1, unsigned int BIT2, unsigned int BIT3)
{
	FOUR_BTN_PORT_ENABLE();	//Activates the port for the four directional buttons
	//Sets the pins for the four buttons to be inputs
	set_BTN_input(BIT0);
	set_BTN_input(BIT1);
	set_BTN_input(BIT2);
	set_BTN_input(BIT3);
	//Sets the pins for the four buttons to be low speed to conserve power
	set_BTN_lowspeed(BIT0);
	set_BTN_lowspeed(BIT1);
	set_BTN_lowspeed(BIT2);
	set_BTN_lowspeed(BIT3);
	//Sets the pins for the four buttons to not use internal pull-up or pull-down resistors
	set_BTN_not_pull_up(BIT0);
	set_BTN_not_pull_up(BIT1);
	set_BTN_pull_up(BIT2);	//Add pull-up pull down resistor
	set_BTN_pull_up(BIT3);	//Add pull-up pull down resistor
}

int readBTNValue(GPIO_TypeDef *PORT, unsigned int BIT) //Reads whether a given button is being pressed - made easier by the 4 buttons using pins 0,1,2,3
{	
	int value = PORT->IDR;	//Check pages 23 and 31 of GPIO lecture notes
	value &= (1<<BIT);
	return value;
}

