#include "switch.h"

int readPinValue(int pin)
{	
	int value = switch_PORT->IDR&=(1<<pin);
	return value;
}

