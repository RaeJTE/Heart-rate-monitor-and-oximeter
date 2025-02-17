#include "usart.h"
#include "stm32f4xx.h" 

volatile char rxBuffer[BUFFER_SIZE];// buffer to temporarily hold string
volatile uint8_t rxIndex = 0;
void USART3_IRQHandler(void);
volatile uint8_t messageReady = 0; // Flag to indicate input is ready


// Function to initialize USART
void init_USART(void)
{
	unsigned char i1,i2;
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;	//usart port clock enable
	
	USART_PORT->MODER&=~(		//clear pin function bits
		(3u<<(2*USART_TX_pin))
		|(3u<<(2*USART_RX_pin))
			);
	USART_PORT->MODER|=(		//reset pin function bits (alternate function)
		(2u<<(2*USART_TX_pin))
		|(2u<<(2*USART_RX_pin))
			);
	
	i1=USART_TX_pin/8;		// used to select AFR[reg] for TX_pin ... pins 0-7 AFR[0] pins 8-15 AFR[1]
	i2=USART_RX_pin>>3;		// same as above for RX_pin

		// ALTERNATE FUNCTION SELECT BITS
	USART_PORT->AFR[i1]&=~(0x0f<<(4*(USART_TX_pin-(i1*8)))); //clear pin function
	USART_PORT->AFR[i1]|=(0x07<<(4*(USART_TX_pin-(i1*8))));	// set usart as alternate function for TX_pin
	USART_PORT->AFR[i2]&=~(0x0f<<(4*(USART_RX_pin-(i2*8)))); // clear pin function
	USART_PORT->AFR[i2]|=(0x07<<(4*(USART_RX_pin-(i2*8))));	 //set usart as alternate function for RX_pin
	
	RCC->APB1ENR|=RCC_APB1ENR_USART3EN;	//usart clock enable
	USART_MODULE->CR1|=(	//USART CONFIG
			USART_CR1_TE		//transmit enable
			|USART_CR1_RE		//receive enable
			|USART_CR1_UE		//usart main enable bit
				);
				
	 // Enable RX interrupt for non-blocking
	USART_MODULE->CR1 |= USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART3_IRQn); // Enable USART3 interrupt in NVIC			
			
				
	CLEAR_BIT(USART_MODULE ->CR2, (1<<12|1<<13)); // Clear STOP bits = 1 STOP BIT
	CLEAR_BIT(USART_MODULE ->CR1, 1<<15); // 16 bit oversampling
	CLEAR_BIT(USART_MODULE ->CR1, 1<<12); // 1 start bit 8 Data bits
  CLEAR_BIT(USART_MODULE ->CR1, 1<<10); // Disable PARITY
	CLEAR_BIT(USART_MODULE ->CR1, 1<<9); // EVEN Parity			
				
	
	USART_MODULE->BRR=SystemCoreClock/(BAUDRATE);		//set baud rate	///////////////////////////BAUDE SET TO 230400
	
	clear_terminal();
	USART_SendString ("\033[0m"); // reset colours	
	USART_SendString ("\r\n \033[32m\033[4m\033[40m Enter mode on, off, heart rate, rgb bar, temperature");

} 





void USART_SendData(char Data) { // send char
while(!(USART3->SR & USART_SR_TC) ); //wait for transmission complete
USART3->DR = (Data & 0x01FF); //write byte to usart data register
}


void USART_SendString (const char *text) { // send string
		unsigned int idx = 0;
		USART_SendData ('\r');
		while (text[idx]) { // end of string is a null = 0
		USART_SendData(text[idx++]);}
		
	USART_SendData ('\n');
	USART_SendData ('\r');
}




void USART3_IRQHandler(void) {
    if (USART3->SR & USART_SR_RXNE) {  // Check if data received
        char receivedChar = (char)USART3->DR; // Read data

        if (receivedChar == '\r' || receivedChar == '\n') { // If Enter is pressed
            rxBuffer[rxIndex] = '\0';  // Null-terminate string
            messageReady = 1; // Set flag indicating input is ready
            rxIndex = 0;  // Reset buffer index for next message
        } 
        else if (rxIndex < BUFFER_SIZE - 1) {
            rxBuffer[rxIndex++] = receivedChar;  // Store character
        }

        USART_SendData(receivedChar);  // Echo input
    }
}


void send_integer(int num) {
    char buffer[10];  // Buffer to hold ASCII representation
    int i = 0;

    if (num < 0) {  // Handle negative numbers
        USART_SendData('-');
        num = -num;
    }

    // Extract digits from the number
    do {
        buffer[i++] = (num % 10) + '0';  // Get last digit, convert to ASCII
        num /= 10;
    } while (num > 0);

    // Send digits in correct order
    while (i > 0) {
        USART_SendData(buffer[--i]);  // Send from the last digit to the first
    }
}





void send_float(float value) {
    int int_part = (int)value;   // Extract integer part
    int frac_part = (int)((value - int_part) * 100);  // Extract two decimal places

    send_integer(int_part);   // Send integer part
    USART_SendData('.');       // Decimal point
    send_integer(frac_part);   // Send fractional part
}




void process_USART_Input(void) {
    if (messageReady) {  // Check if Enter was pressed
        clear_terminal();//clear the terminal
				USART_SendString("\r\nReceived: ");
        USART_SendString((const char*)rxBuffer);  // Echo input
        USART_SendString("\r");

        // Compare input with "on" or "off"
        if (comparestrings((const char*)rxBuffer, "on")) {
					clear_terminal();//clear the terminal
            USART_SendString("\r\n\033[30m\033[6m\033[42m Turning ON");
            // Perform action for "on"
						//USART_reset();// exit check
        } 
        else if (comparestrings((const char*)rxBuffer, "off")) {
					clear_terminal();//clear the terminal
            USART_SendString("Turning OFF\r\n");
            // Perform action for "off"
						//USART_reset();// exit check
        } 
				else if (comparestrings((const char*)rxBuffer, "heart rate")){
						clear_terminal();//clear the terminal
						USART_SendString ("\r\n\033[31m\033[4mheart rate");
						Init_Timer5();
						//USART_reset();// exit check
					}
        
				else if (comparestrings((const char*)rxBuffer, "rgb bar")){
							clear_terminal();//clear the terminal
							USART_SendString ("RGB BAR");
							Init_Timer2();
							while(1){
							RGB_main();} // RGB BAR stuff
						  //USART_reset();// exit check
							//bar_graph(int_part, frac_part);
							}
				else if (comparestrings((const char*)rxBuffer, "temperature")){
							clear_terminal();//clear the terminal
							USART_SendString ("TEMPERATURE (22)");
						  GPIO_Init();
							seg_main();
						  //USART_reset();// exit check
							}
				else if (comparestrings((const char*)rxBuffer, "acc")){
							clear_terminal();//clear the terminal
							USART_SendString ("ACCELERATION");
					    I2C2_Config(); // set up acceleration related stuff
							MPU6050_Init();
					    while (1) 
							{	
								USART_SendString ("\033[2J\033[H ACCELERATION");
								MPU6050_Read_Accel(); // read acceleration values
								USART_SendString("\r\nX = ");
								send_float(Ax);
								USART_SendString("\r\nY = ");
								send_float(Ay);
								USART_SendString("\r\nZ = ");
								send_float(Az);
								for (volatile int i = 0; i < 100000; i++); // Simple delay
								
							}
						  //USART_reset();// exit check
							}
								
							
	
						
					else {
            USART_SendString("Invalid input\r\n");
        }

        messageReady = 0;  // Reset flag
        rxBuffer[0] = '\0';  // Clear buffer
    }
}



int comparestrings(const char *str1, const char *str2) {
    // Compare each character of both strings
    while (*str1 && *str2) {  
			if (*str1 != *str2) {
      return 0;  // Return 0 if the characters don't match
        }
        str1++;
        str2++;
    }
    
    // If both strings reach null terminator at the same time, they are equal
    return (*str1 == '\0' && *str2 == '\0');
}


// reset function doesnt work
void USART_reset(void) {
    if (messageReady) {  // Check if Enter was pressed
        USART_SendString("\r\nReceived: ");
        USART_SendString((const char*)rxBuffer);  // Echo input
        USART_SendString("\r");

        // Compare input with "on" or "off"
        if (comparestrings((const char*)rxBuffer, "exit")) {
				// Set the VECTKEY to unlock the AIRCR register, and set SYSRESETREQ to trigger a reset
				SCB->AIRCR = (0x5FA << 16) | (1 << 2);  // VECTKEY = 0x5FA, SYSRESETREQ = 1

        } 

						
					else {
            USART_SendString("Invalid input! Please type exit to leave.\r\n");
        }

        messageReady = 0;  // Reset flag
        rxBuffer[0] = '\0';  // Clear buffer
    }
}
void clear_terminal() { // function to clear terminal
    USART_SendString("\033[2J\033[H");  // Clear the screen and move cursor to top-left
}

