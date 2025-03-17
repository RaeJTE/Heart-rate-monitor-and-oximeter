#include "RGB_Bar.h"

unsigned short ADC_DATA;

unsigned int int_part = 0;
unsigned int frac_part = 0;
unsigned int value = 0;

// Function to initialise GPIO for the LED RGB Bar
void init_GPIO_RGB_Bar(void) {
    // Enable GPIOE
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

    // Configure PE2–PE9  as outputs
    GPIOE->MODER &= ~((3 << (2 * 2)) | (3 << (3 * 2)) | (3 << (4 * 2)) | (3 << (5 * 2)) |
                      (3 << (6 * 2)) | (3 << (7 * 2)) | (3 << (8 * 2)) | (3 << (9 * 2)));
    GPIOE->MODER |= ((1 << (2 * 2)) | (1 << (3 * 2)) | (1 << (4 * 2)) | (1 << (5 * 2)) |
                     (1 << (6 * 2)) | (1 << (7 * 2)) | (1 << (8 * 2)) | (1 << (9 * 2)));

    // Configure PE12–PE14 as outputs for RGB bank enable
    GPIOE->MODER &= ~((3 << (12 * 2)) | (3 << (13 * 2)) | (3 << (14 * 2)));
    GPIOE->MODER |= ((1 << (12 * 2)) | (1 << (13 * 2)) | (1 << (14 * 2)));

    // Configure PE0 (/LED_BAR_OE) as output (output enable for the RGB bar)
    GPIOE->MODER &= ~(3 << (0 * 2));
    GPIOE->MODER |= (1 << (0 * 2));

    // Set LED_BAR_OE (PE0) to 0 to enable the bar
    GPIOE->BSRR = (1 << (0 + 16)); // Activate the RGB Bar (output enable active low)
}

// Function to control the RGB LED Bar
void control_RGB_Bar(unsigned short ADC_DATA) {
    // Clear all LEDs
    GPIOE->ODR &= ~((0xFF << 2) | (1 << 12) | (1 << 13) | (1 << 14)); 

    if (ADC_DATA <= 1365) { // first third - illuminate Red LEDs progressively
        uint8_t num_leds = ADC_DATA / 171; // 1365 / 8 = 171 per LED
        GPIOE->ODR |= (1 << 12);            // Enable Red Bank
        GPIOE->ODR |= ((1 << num_leds) - 1) << 2; // Illuminate LEDs progressively
    } else if (ADC_DATA <= 2730) { // Second third: Illuminate Green LEDs progressively
        uint8_t num_leds = (ADC_DATA - 1366) / 171; // Adjust range for second third
        GPIOE->ODR |= (1 << 13);            // Enable Green Bank
        GPIOE->ODR |= ((1 << num_leds) - 1) << 2; // Illuminate LEDs progressively
    } else { // Final third: Illuminate Blue LEDs progressively
        uint8_t num_leds = (ADC_DATA - 2731) / 171; // Adjust range for final third
        GPIOE->ODR |= (1 << 14);            // Enable Blue Bank
        GPIOE->ODR |= ((1 << num_leds) - 1) << 2; // Illuminate LEDs progressively
    }
}

// Function to initialise ADC for PA0 (potentiometer)
void init_ADC_PA0(void) {
    // Enable GPIOA clock for PA0
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Set PA0 as analogue mode
    GPIOA->MODER |= (3 << (0 * 2)); // Set PA0 (pin 0) to analogue mode

    // Enable ADC1 clock
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // Configure ADC1
    ADC1->SQR3 = 0;                // Channel 0 is the first in sequence
    ADC1->SQR1 = 0;                // Only 1 conversion in the sequence
    ADC1->CR2 |= ADC_CR2_ADON;     // Enable ADC1
}

// Function to read ADC value from PA0
unsigned short read_ADC_PA0(void) {
    ADC1->CR2 |= ADC_CR2_SWSTART;  // Start conversion
    while (!(ADC1->SR & ADC_SR_EOC)); // Wait until conversion is complete
    return ADC1->DR;               // Return ADC value
}

// Function to initialise DAC2 for output to PA5
void init_DAC2(void) {
    // Enable DAC clock
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;

    // Enable DAC channel 2 (connected to pin PA5)
    DAC->CR |= DAC_CR_EN2;         // Enable DAC2
}

// Function to output to DAC2
void output_DAC2(unsigned short value) {
    DAC->DHR12R2 = value;          // Write 12-bit value to DAC channel 2
}

void RGB_main(void) {


    // Initialise peripherals
    init_GPIO_RGB_Bar(); // Configure GPIO for RGB Bar
    init_ADC_PA0();      // Configure ADC1 for PA0
    init_DAC2();         // Configure DAC2 for output


		// Read potentiometer value from ADC
		ADC_DATA = read_ADC_PA0();

		// Output the ADC value to DAC2
		output_DAC2(ADC_DATA);

		// Control the RGB LED Bar based on ADC value
		control_RGB_Bar(ADC_DATA);
		
}


// Function to turn off all LEDs in the RGB bar and disable the RGB bank
void turn_off_RGB_Bar(void) {
    // Set all RGB LED pins (PE2–PE9) to low (turn off LEDs)
    GPIOE->ODR &= ~((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9));

    // Disable all RGB bank LEDs by clearing PE12, PE13, PE14
    GPIOE->ODR &= ~((1 << 12) | (1 << 13) | (1 << 14));  // Clear PE12, PE13, PE14 to turn off the RGB banks

    // Disable the LED bar output enable (PE0) by setting it high
    GPIOE->BSRR = (1 << 0); // Set PE0 high to disable the RGB bar
}
 