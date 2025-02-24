#include "ADC.h"

void init_ADC(void)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOFEN;	//GPIOA clock enable
	ADC_input_port->MODER|=(3u<<(2*ADC_input_pin));	//ADC input pin is analogue mode
	
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;		//ADC clock enable
	
	// Set ADC resolution to 12 bits
	ADC1->CR1 &= ~ADC_CR1_RES;  // 12-bit resolution
	
	ADC1->SQR1&=~ADC_SQR1_L;		//set sequence length to 1
	ADC1->SQR3&=~ADC_SQR3_SQ1;		//clear channel select bits
	ADC1->SQR3|=ADC_Channel;		//set channel
	ADC1->CR2 |= ADC_CR2_CONT; // set to continuous
	
	// Set external trigger for injected group (using Timer 1 CC4 event)
  ADC1->CR2 |= ADC_CR2_JEXTSEL_0; // External trigger for injected group: Timer 1 CC4 event
  ADC1->CR2 |= ADC_CR2_JEXTEN_0;  // Trigger on rising edge of the selected external event
	// CHECK RM0090 PG 422 FOR JEXTSEL
	//(uses timer 1 cc4 for triggers)
	
	ADC1->CR2|=ADC_CR2_ADON;//enable ADC
	
}

unsigned short read_adc(void)
{
	ADC1->CR2|=ADC_CR2_SWSTART;				//start ADC conversion
	while((ADC1->SR&ADC_SR_EOC)==0){__NOP();}	//wait for ADC conversion complete
	return ADC1->DR;									//return converted value
}
                                                                 