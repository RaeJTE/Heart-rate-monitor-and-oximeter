#include "LED.h"

//Infra-red LED on PCB is on A4
//Red LED on PCB board is A5

// FLASH BLUE, HALF DUTY CYCLE FOR PWM 

// BLUE = LED 3

void LED_INIT(void){
    // ENABLE PORTS
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable GPIO A clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // Enable GPIO B clock
	
		// CONFIGURE PORT: GPIOA PIN:4 TO OUTPUT for infra-red LED on PCB board
    GPIOA->MODER |= (1 << (2 * 4)); // Set GPIOA5 as output
	
		// CONFIGURE PORT: GPIOA PIN:5 TO OUTPUT for red LED on PCB board
    GPIOA->MODER |= (1 << (2 * 5)); // Set GPIOA5 as output

		// CONFIGURE PORT: GPIOB PIN:0 TO OUTPUT for LED1
    GPIOB->MODER |= (1 << (2 * 0)); // Set GPIOB0 as output
	  
		// CONFIGURE PORT: GPIOB PIN:14 TO OUTPUT for LED2
		GPIOB->MODER |= (1 << (2 * 14)); // Set GPIOB14 as output
	
    // CONFIGURE PORT: GPIOB PIN:7 TO OUTPUT for LED3 
    GPIOB->MODER |= (1 << (2 * 7)); // Set GPIOB14 as output

    // ENSURE LEDs START OFF
		GPIOA->BSRR = (1 << (4 + 16));  // infra-red LED on PCB board OFF (set to low)
		GPIOA->BSRR = (1 << (5 + 16));  // red LED on PCB board OFF (set to low)
    GPIOB->BSRR = (1 << (0 + 16));  // LED1 OFF (set to low)
    GPIOB->BSRR = (1 << (14 + 16)); // LED2 OFF (set to low)
    GPIOB->BSRR = (1 << (7 + 16));  // LED3 OFF (set to low)

}

void toggle_PCB_IF(void)
{
	if (GPIOA->ODR & (1 << 4))  // Check if LED is on
		GPIOA->BSRR = (1 << (4 + 16));  // Reset pin (turn off)
  else
		GPIOA->BSRR = (1 << 4);  // Set pin (turn on)
}

void toggle_PCB_RED(void)
{
	if (GPIOA->ODR & (1 << 5))  // Check if LED is on
		GPIOA->BSRR = (1 << (5 + 16));  // Reset pin (turn off)
  else
		GPIOA->BSRR = (1 << 5);  // Set pin (turn on)
}


// function to toggle blue led
void Toggle_BLUE(void)
{

        if (GPIOB->ODR & (1 << 7))  // Check if LED is on
            GPIOB->BSRR = (1 << (7 + 16));  // Reset pin (turn off)
        else
            GPIOB->BSRR = (1 << 7);  // Set pin (turn on)
}

// function to toggle green led
void ON_GRN(void)
{
	GPIOB->BSRR = (1 << 0);  // Set pin (turn on)
}



void Toggle_LED(uint8_t led)
{
    // Toggle the given LED based on the passed argument.
    if (led == 'G')  // Green LED (GPIOB Pin 0)
    {
        if (GPIOB->ODR & (1 << 0))  // Check if LED is on
            GPIOB->BSRR = (1 << (0 + 16));  // Reset pin (turn off)
        else
            GPIOB->BSRR = (1 << 0);  // Set pin (turn on)
    }
    else if (led == 'R')  // Red LED (GPIOB Pin 14)
    {
        if (GPIOB->ODR & (1 << 14))  // Check if LED is on
            GPIOB->BSRR = (1 << (14 + 16));  // Reset pin (turn off)
        else
            GPIOB->BSRR = (1 << 14);  // Set pin (turn on)
    }
    else if (led == 'B')  // Blue LED (GPIOB Pin 7)
    {
        if (GPIOB->ODR & (1 << 7))  // Check if LED is on
            GPIOB->BSRR = (1 << (7 + 16));  // Reset pin (turn off)
        else
            GPIOB->BSRR = (1 << 7);  // Set pin (turn on)
    }
}






