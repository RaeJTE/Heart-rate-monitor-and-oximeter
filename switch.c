#include "switch.h"

void LEDInit(void)
{
	LED_PORT_ENABLE();	//Clocks the port being used for inputs to enable it
	//Green traffic LED
	set_LED_GRN_output(); //Sets to output mode
	set_LED_GRN_pushPull(); //Sets to push-pull output
	set_LED_GRN_lowspeed();	//Sets to 2MHz (low speed) operation to save power
	set_LED_GRN_pull_up();	//Sets to pull up configuration
}

void Toggle_LED(void)
{
	GPIOB->ODR^=(1u<<LED_GRN);								//Toggles green traffic LED
}

void switchInit(void)
{
	switch_PORT_ENABLE();	//Clocks the port being used for inputs to enable it
	//Button 0
	set_BTN_input(BTN0_PIN);	//Sets to input mode
	set_BTN_lowspeed(BTN0_PIN);	//Sets to 2MHz (low speed) operation to save power
	set_BTN_pull_up(BTN0_PIN);	//Sets to pull up configuration
	//Button 1
	set_BTN_input(BTN1_PIN);	//Sets to input mode
	set_BTN_lowspeed(BTN1_PIN);	//Sets to 2MHz (low speed) operation to save power
	set_BTN_pull_up(BTN1_PIN);	//Sets to pull up configuration
	//Button 2
	set_BTN_input(BTN2_PIN);	//Sets to input mode
	set_BTN_lowspeed(BTN2_PIN);	//Sets to 2MHz (low speed) operation to save power
	set_BTN_pull_up(BTN2_PIN);	//Sets to pull up configuration
	//Button 3
	set_BTN_input(BTN3_PIN);	//Sets to input mode
	set_BTN_lowspeed(BTN3_PIN);	//Sets to 2MHz (low speed) operation to save power
	set_BTN_pull_up(BTN3_PIN);	//Sets to pull up configuration
}

int readBTNValue(int BTNnum) //Reads whether a given button is being pressed - made easier by the 4 buttons using pins 0,1,2,3
{	
	int value = switch_PORT->IDR&=(1<<BTNnum);
	return value;
}

