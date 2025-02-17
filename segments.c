#include "segments.h"


void GPIO_Init(void)
{
    // Enable GPIOE
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

    // Set pe2-pe11 as output ///not certain on these
    GPIOE->MODER = 0x55555555; // pe2-pe11 as push-pull
    GPIOE->OTYPER = 0x00000000; // pe2-pe11 as push-pull
    GPIOE->OSPEEDR = 0xAAAAAAAA; //sets pe2 to pe11 as high speed
    GPIOE->PUPDR = 0x00000000; // pe2-pe11 as no pull-up, no pull-down
}




// Function to set the segments for a given digit
void displayDigit(uint8_t digit, uint8_t position)
{
    // Clear all segments using BSRR
    GPIOE->BSRR = (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G) << 16;

    // Set segments based on digit
    switch (digit)
    {
    case 2:
        GPIOE->BSRR = (SEG_A | SEG_B | SEG_G | SEG_E | SEG_D); // Correct segments for '2'
        break;
    default:
        break;
    }

    // Enable the appropriate digit
    if (position == 1)
    {
        GPIOE->BSRR = DIGIT1_EN;
        GPIOE->BSRR = DIGIT2_EN << 16;
    }
    else if (position == 2)
    {
        GPIOE->BSRR = DIGIT2_EN;
        GPIOE->BSRR = DIGIT1_EN << 16;
    }
}






int seg_main(void)
{
    // Initialize GPIO
    GPIO_Init();

    while (1)
    {
        // Display '2' on first digit
        displayDigit(2, 1);

        // Display '2' on second digit
        displayDigit(2, 2);
    }
	}


