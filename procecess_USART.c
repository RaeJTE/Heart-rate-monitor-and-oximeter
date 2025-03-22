#include "usart.h"
#include "proccess_USART.h"
#include "heart rate.h"
#include "stm32f4xx.h" 

extern volatile char rxBuffer[BUFFER_SIZE];// buffer to temporarily hold string
extern volatile uint8_t messageReady; // Flag to indicate input is ready




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

					heart_rate_main();


					}
        
				else if (comparestrings((const char*)rxBuffer, "rgb bar")){
							clear_terminal();//clear the terminal
							init_DAC();  // Configure DAC for analog output (PA4)
							USART_SendString ("RGB BAR");
							//Init_Timer2(); Jacob - commented out
							while(1){
							RGB_main(); // RGB BAR stuff
						  //USART_reset();// exit check
							//bar_graph(int_part, frac_part);
								}
							}
				else if (comparestrings((const char*)rxBuffer, "temperature")){
							clear_terminal();//clear the terminal
							USART_SendString ("TEMPERATURE (22)");
						  GPIO_Init();
							seg_main();
						  //USART_reset();// exit check
							}
				else if (comparestrings((const char*)rxBuffer, "monitor check")){
							clear_terminal();//clear the terminal
							USART_SendString ("CHECKING.................");

						  //USART_reset();// exit check
							}
							
							
				else if (comparestrings((const char*)rxBuffer, "acc")){
							clear_terminal();//clear the terminal
							USART_SendString ("ACCELERATION");
							init_DAC();  // Configure DAC for analog output (PA4)
					    I2C2_Config(); // set up acceleration related stuff
							MPU6050_Init();
							Init_Timer4(10);

							USART_SendString ("\033[2J\033[H ACCELERATION");


						
						  //USART_reset();// exit check
							}
								
							
	
						
					else {
            USART_SendString("Invalid input\r\n");
        }

        messageReady = 0;  // Reset flag
        rxBuffer[0] = '\0';  // Clear buffer
    }
}

