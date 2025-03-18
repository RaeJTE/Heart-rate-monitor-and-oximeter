#include "timer.h"

unsigned short ADC_DATA;
float voltage;
unsigned char str[20];  // Buffer to store voltage string

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


void Init_Timer2(uint32_t frequency) // frequency in Hz
{
    uint32_t timer_clock = 90000000 / 256; // 90 MHz / Prescaler
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


// Vout at 10hz timer stuff
void TIM2_IRQHandler(void)
{
    // Check if the update interrupt flag is set
    if (TIM2->SR & TIM_SR_UIF) {
			  ADC_DATA = read_adc();  // Read ADC value from LDR (PC0)
        //output_dac1(ADC_DATA);   // Send the ADC value to DAC
        
        // Calculate voltage: ADC_DATA * (3.3 / 4095)
        voltage = (ADC_DATA * 3.3f) / 4095.0f;
			
        // Convert voltage to string
        float_to_string(voltage, (char *)str);
        
        // Send voltage string via UART
        for (char *p = (char *)str; *p; p++)
        {
            send_usart(*p);  // Send character via UART
        }
        send_usart('\n');   // Newline for terminal asthetics
				send_usart('\r');   // Newline for terminal asthetics
			
        // Clear the interrupt flag
        TIM2->SR &= ~TIM_SR_UIF;
			  //Vout to terminal
				//USART_Vout( ADC_DATA, int_part, frac_part);
				// select either bar chart or numerical voltage
			
    }
}


void Init_Timer3(uint32_t frequency)
{
    // Enable Timer 3 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // Calculate the prescaler and ARR values for the desired frequency
    uint32_t timerClock = 90000000; // Timer clock is 90 MHz (system clock)
    
    // Calculate the period required to achieve the target frequency
    uint32_t period = timerClock / frequency;
    
    // Find the appropriate prescaler and ARR values
    uint32_t prescaler = period / 2000;  // Default ARR value (2000  for 0.5 Hz)
    uint32_t arr = period / (prescaler + 1);

    // Apply the prescaler and ARR values to Timer 3
    TIM3->PSC = prescaler - 1;   // Subtract 1 since PSC is zero-based
    TIM3->ARR = arr;             // Set the new auto-reload value

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
		TIM2->SR &= ~TIM_SR_UIF;
	}
}



void interrupt_priority(void){
	    // Set priority for each timer interrupt
	NVIC_SetPriority(TIM2_IRQn, 0);  // Timer 2 ISR: Priority 0
	NVIC_SetPriority(TIM3_IRQn, 1);  // Timer 3 ISR: Priority 1
	NVIC_SetPriority(TIM5_IRQn, 2);  // Timer 5 ISR: Priority 2
	
}







