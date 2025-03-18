#include "ADC.h"
//Being used for testing purposes with DAC code

void init_ADC(void)
{
	//Nucleo board photodiode is C0
	
	// Enable GPIOA clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Configure PA7 as analog input
    GPIOA->MODER |= (3U << (2 * 7));  // Set Analog mode
    GPIOA->PUPDR &= ~(3U << (2 * 7)); // No pull-up, No pull-down
		
	// Enable ADC1 clock BEFORE configuring ADC
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // Ensure ADC is disabled before configuration
    ADC1->CR2 &= ~ADC_CR2_ADON;

    // Set ADC resolution
    ADC1->CR1 &= ~ADC_CR1_RES;  // 12-bit resolution

    // Enable ADC1 with continuous mode OFF
    ADC1->CR2 &= ~ADC_CR2_CONT; // Single conversion mode

    // Set sampling time for channel 7
    ADC1->SMPR2 &= ~(7U << (3 * 7));  // Clear sampling time bits
    ADC1->SMPR2 |= (3U << (3 * 7));   // Set sampling time to 28 cycles (adjust as needed)

    // Select channel 7 (PA7 corresponds to ADC1_IN7)
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;  // Clear previous selection
    ADC1->SQR3 |= (7U << 0);      // Set ADC1 channel 7 (PA7)

    // **Enable ADC**
    ADC1->CR2 |= ADC_CR2_ADON;
	
}


unsigned short read_adc(void)
{
	// **Clear EOC flag from previous conversion**
    ADC1->SR &= ~ADC_SR_EOC;
	
   // Start ADC conversion
   ADC1->CR2 |= ADC_CR2_SWSTART;

   // Wait for conversion to complete
   while ((ADC1->SR & ADC_SR_EOC) == 0);

   // Read and return ADC result
   return (uint16_t)ADC1->DR;						//return converted value
}
                                                                          