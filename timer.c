#include "timer.h"

unsigned short ADC_DATA;
float voltage;
unsigned char str[20];  // Buffer to store voltage string
volatile int ADCcounter = 0;
volatile uint8_t ADCout[15*samplingRate];
volatile unsigned int msTime;

//Utility for timers code
void float_to_string(float num, char *str)
{
    // Convert float to intager representation
    int integer_part = (int)num;                // Get intager part
    int decimal_part = (int)((num - integer_part) * 100000);  // Get first 2 decimal places

    // Handle rounding for decimal part if necessary
    if (decimal_part < 0) decimal_part = -decimal_part;  // Avoid negative decimals

    // Convert to string manually
    char *p = str;
    if (integer_part == 0) {
        *p++ = '0';
    } else {
        // Extract digits of intager part
        char temp[10];
        int i = 0;
        while (integer_part > 0) {
            temp[i++] = (integer_part % 10) + '0';  // Convert digit to ASCII
            integer_part /= 10;
        }
        while (i > 0) {
            *p++ = temp[--i];  // Reverse the order
        }
    }
    *p++ = '.';  // Add decimal point

    // Extract digits of decimal part
    if (decimal_part == 0) {
        *p++ = '0';
       
			*p++ = '0';
    } else {
        if (decimal_part < 10) *p++ = '0';  // Add leading if necessary
        char temp[10];
        int i = 0;
        while (decimal_part > 0) {
            temp[i++] = (decimal_part % 10) + '0';  // Convert digit to ASCII
            decimal_part /= 10;
        }
        while (i > 0) {
            *p++ = temp[--i];  // Reverse the order
        }
    }

    *p = '\0'; 
}




//Timers code

void Init_Timer2(uint32_t frequency) // frequency in Hz
{
    uint32_t timer_clock = 16000000 / 256; // 16 MHz / Prescaler
    uint32_t arr_value = (timer_clock / frequency) - 1;

    // Enable timer 2 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Enable the update interrupt for Timer 2
    TIM2->DIER |= TIM_DIER_UIE; 

    // Prescaler value (90 MHz / 256 = 351 kHz)
    TIM2->PSC = 256 - 1;  // Divide by 256 -> Timer clock = 351 kHz

    // Set the auto-reload register (ARR) based on desired frequency
    TIM2->ARR = arr_value;

    // Initialize the counter to 0
    TIM2->CNT = 0;

    // Enable Timer 2 interrupt in the NVIC
    NVIC->ISER[0] |= (1u << 28);  // Enable Timer 2 interrupt in the NVIC

    // Start the timer
    TIM2->CR1 |= TIM_CR1_CEN;    // Start the timer
}


// Timer 2 interrupt handler for ADC reading
void TIM2_IRQHandler(void)
{
    // Check if the update interrupt flag is set
    if (TIM2->SR & TIM_SR_UIF) {
			  ADC_DATA = read_adc();  // Read ADC value from LDR (PC0)
        output_dac1(ADC_DATA);   // Send the ADC value to DAC
			
				ADCout[ADCcounter] = ADC_DATA;
			
				if(ADCcounter < (15* samplingRate)-1)
				{
					ADCcounter++;
				}
				else
				{
					ADCcounter = 0;
				}
			
        // Clear the interrupt flag
        TIM2->SR &= ~TIM_SR_UIF;
    }
}


void Init_Timer3(void)	//Timer 3 used for delays in ms
{
    // Enable Timer 3 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // Timer clock
    uint32_t timerClock = 16000000;
		uint32_t frequency = 1000;
	
		// Prescaler selection (assuming ARR = 1000 for fine granularity)
    uint32_t prescaler = (timerClock / (frequency * 1000)) - 1;
    uint32_t arr = (timerClock / ((prescaler + 1) * frequency));

    // Prescaler value (90 MHz / 256 = 351 kHz)
    TIM3->PSC = prescaler;  // Divide by 256 -> Timer clock = 351 kHz

    // Set the autso-reload register (ARR) for 100 ms period
    TIM3->ARR = arr;

    // Initialize the counter to 0
    TIM3->CNT = 0;

    // Enable update interrupt
    TIM3->DIER |= TIM_DIER_UIE;

    // Enable Timer 3 interrupt in NVIC
    NVIC_EnableIRQ(TIM3_IRQn);

    // Enable global interrupts
    __enable_irq();

    // Start Timer 3
    TIM3->CR1 |= TIM_CR1_CEN;   // Start Timer 3
}

void TIM3_IRQHandler(void)
{
	// Check if the update interrupt flag is set
	if (TIM3->SR & TIM_SR_UIF)
	{
		//Clear the interrupt flag
		TIM3->SR &= ~TIM_SR_UIF;
		//Increment time tracker
		msTime++;
	}
}

void TIM3Delay (float msDelay)	//Function to use Timer 3 for a delay measured in ms
{
	msTime = 0;
	while(msTime <= msDelay)
	{
	}
}



void interrupt_priority(void){
	    // Set priority for each timer interrupt
	NVIC_SetPriority(TIM2_IRQn, 0);  // Timer 2 ISR: Priority 0
	NVIC_SetPriority(TIM3_IRQn, 1);  // Timer 3 ISR: Priority 1
	NVIC_SetPriority(TIM5_IRQn, 2);  // Timer 5 ISR: Priority 2
	
}







