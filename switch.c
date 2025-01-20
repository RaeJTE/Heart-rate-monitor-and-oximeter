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


int readPinValue(int pin)
{	
	int value = switch_PORT->IDR&=(1<<pin);
	return value;
}

