#include "timer.h"
#include "LED.h"


extern unsigned int int_part;
extern unsigned int frac_part;

// Timer 1 used for ADC
// Timer 3 used for blue pwm
// timer 2 used for rgb bar


// check rm0090 (13.13.3) for adc clock 1

// CHECK RM0090 PG 422 FOR JEXTSEL
//(uses timer 1 cc4 for triggers)


void init_Timer1(void)// ADC
{
    // Enable Timer 1 clock
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

	
		// Set Timer 1 to 1 khz trigger for ADC
    TIM1->PSC = 179999;             // Prescaler = 15 (16 MHz / 16 = 1 MHz timer frequency)
    TIM1->ARR = 179999;            // Auto-reload value for 1 kHz frequency (1ms period)

	

		
    // Enable Timer 1 trigger output (TRGO) to generate a signal on the CC4 pin
    TIM1->CR2 |= TIM_CR2_MMS_1; // TRGO = update event every 1 ms
	

    // Enable Timer 1
    TIM1->CR1 |= TIM_CR1_CEN;

}









//BLUE PWM STUFF

// Function to hold the Blue LED at 50% power
void Hold_Blue_LED(void)
{

    // setting PWM duty cycle to 50% for the Blue LED

//    TIM5->CCR1 = TIM5->ARR / 2;  // Set CCR1 to 50% of the ARR value (for 50% duty cycle)
    TIM5->CCER |= TIM_CCER_CC1E; // Enable the output on channel 1 (for the Blue LED)
}



void Init_Timer3(uint32_t frequency) // BLUE LED
{
    // Enable Timer 3 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // Timer clock
    uint32_t timerClock = 90000000;

    // Prescaler selection (assuming ARR = 1000 for fine granularity)
    uint32_t prescaler = (timerClock / (frequency * 1000)) - 1;
    uint32_t arr = (timerClock / ((prescaler + 1) * frequency));

    // Apply prescaler and ARR
    TIM3->PSC = prescaler;  // PSC is zero-based
    TIM3->ARR = arr;        // Auto-reload value

    // Enable update interrupt
    TIM3->DIER |= TIM_DIER_UIE;
    
    // Enable Timer 3 interrupt in NVIC
    NVIC_EnableIRQ(TIM3_IRQn);
    
    // Enable global interrupts
    __enable_irq();

    // Start Timer 3
    TIM3->CR1 |= TIM_CR1_CEN;
}
// Timer 3 (BLUE LED) ISR
void TIM3_IRQHandler(void)
{
    if (TIM3->SR & TIM_SR_UIF)  // Check if update interrupt flag is set
    {
        TIM3->SR &= ~TIM_SR_UIF;  // Clear the update interrupt flag
        Toggle_LED('B');          // Toggle blue LED
			// using the toggle, will easilt create a 50% duty cycle
    }
}

// DONE WITH BLUE PWM



// Vout at 10hz timer stuff
void TIM2_IRQHandler(void)
{
    // Check if the update interrupt flag is set
    if (TIM2->SR & TIM_SR_UIF) {
        // Clear the interrupt flag
        TIM2->SR &= ~TIM_SR_UIF;
			  //Vout to terminal
				USART_Vout( ADC_DATA, int_part, frac_part);
			// select either bar chart or numerical voltage
			
    }
}


void Init_Timer2(void) // 10hz (rgb bar terminal out)
{
    // Enable timer 2 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Enable the update interrupt for Timer 2
    TIM2->DIER |= TIM_DIER_UIE; 

    // Prescaler value (90 MHz / 256 = 351 kHz)
    TIM2->PSC = 256 - 1;  // Divide by 256 -> Timer clock = 351 kHz

    // Set the auto-reload register (ARR) for 100 ms period
    TIM2->ARR = 35099; // 351 kHz * 0.1s = 35099

    // Initialize the counter to 0
    TIM2->CNT = 0;

    // Enable Timer 2 interrupt in the NVIC
    NVIC->ISER[0] |= (1u << 28);  // Enable Timer 2 interrupt in the NVIC

    // Start the timer
    TIM2->CR1 |= TIM_CR1_CEN;    // Start the timer
}










//TIMNER 5 = RED LED
// Timer 5 Initialisation for LED3
void Init_Timer5(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // Enable Timer 5 clock
    TIM5->PSC = 9000 - 1;               // Prescaler: Divide clock by 9000 (90 MHz / 9000 = 10 kHz)
    TIM5->ARR = 5000;                   // Auto-reload value for 500 ms (10 kHz / 5000 = 2 Hz)
    TIM5->DIER |= TIM_DIER_UIE;         // Enable update interrupt
    NVIC_EnableIRQ(TIM5_IRQn);          // Enable Timer 5 interrupt
    TIM5->CR1 |= TIM_CR1_CEN;           // Start Timer 5
}
// Timer 5 ISR (Interrupt Service Routine) for LED3
void TIM5_IRQHandler(void)
{
    if (TIM5->SR & TIM_SR_UIF)          // Check if update interrupt flag is set
    {
        TIM5->SR = ~TIM_SR_UIF;         // Clear update interrupt flag
        //GPIOB->ODR ^= (1 << 7);         // Toggle LED3 (GPIOB Pin 7)
			Toggle_LED('R');                // toggles red led
    }
}



void interrupt_priority(void){
	    // Set priority for each timer interrupt
    NVIC_SetPriority(TIM5_IRQn, 1);  // Timer 5 ISR: Priority 1
    NVIC_SetPriority(TIM2_IRQn, 2);  // Timer 2 ISR: Priority 2
    NVIC_SetPriority(TIM3_IRQn, 0);  // Timer 3 ISR: Priority 0
	
	
	
	
	
}







