
#include "heart rate.h"
// LEDS alternate in heart rate mode on for 2s off for 2s
// heart rate and oxy
// stop when mooved
//IF CURRENT ACC IS 0.5 MORE OR LESS THAN PREVIOUS ACC FLAG MOVEMENT AND WAIT UNTILL RESOLVED

// DO SOMETHING FOR OXY CALC
// Global Variables
// 
/*oid motion_check(int accel_check){
	
	while (accel_check == 1){
	        USART_SendString("\r\n\033[31m\033[4m HOLD STILL!!!");} 
}
*/
// send int and frac part of adc in for bar graph of pulse ;)

// could sent heart rate to rgb bar


void heart_rate_main()
	{		
		//THE FOLLOWING IS FOR MOTION CHECK
		clear_terminal();//clear the terminal
		init_DAC();  // Configure DAC for analog output (PA4)
		I2C2_Config(); // set up acceleration related stuff
		MPU6050_Init();
		Init_Timer4(10);
		USART_SendString ("\033[2J\033[H ACCELERATION");
		// MOTION CHECK STUFF DONE
		
		/*
		////////// Treat this as main.c:		///////////////////////////////////////////////////////////////////////////////////////////////	
		
		//PLEASE READ
		
		(All of your files have been added except the main) */
		
		// Please let me know (add comments etc) of any changes you make to my files :)
		
		// if you could also verify the code works using your pico scope it would be appreciated, thanks
		
		// to run this code you need to open putty with:
		// speed = 230400
		// 8 data bits
		// 1 stop bits
		// even parity
		// no flow control
		
		// then navigate to heart rate in the serial
	
		// :)

		//Initialisations
		//Initialisation of LCD in 8-bit mode
		initLCD8();
		cmdLCD(LCD_LINE1);
		LCD_CLR();
		//Initialisation of ADC
		init_ADC();
		//Initialisation of Buzzer
		initBuzz();
		//Initialisation of timers
		Init_Timer2(samplingRate);
		Init_Timer3();

		//Variables for use throughout heart_rate_main
		int j = 0;
		extern volatile uint8_t ADCout[15*samplingRate];
		float copyADCout[15*samplingRate];	//Equivalent arry to above but that is not updated by interrupts
		char* num;	//Creates a pointer to be used to store a string conversion of a number - pointer necessary because of pointer decay when moving between .c files
		int numLen;	//Variable to store length of string conversion of number
		int* peakPositions [(15*5)-1];
		int numOfPeaks;
		
	
		//Long delays needed to give ADC array time to fill.
		stringLCD("Begin in", 8, 0, 0);
		TIM3Delay(2500);
		LCD_CLR();
		stringLCD("5", 1, 0, 0);
		TIM3Delay(2500);
		LCD_CLR();
		stringLCD("4", 1, 0, 0);
		TIM3Delay(2500);
		LCD_CLR();
		stringLCD("3", 1, 0, 0);
		TIM3Delay(2500);
		LCD_CLR();
		stringLCD("2", 1, 0, 0);
		TIM3Delay(2500);
		LCD_CLR();
		stringLCD("1", 1, 0, 0);
		TIM3Delay(2500);
		LCD_CLR();
				
		
		//Reads in the rapidly updating array to a non updating array
		for(j = 0; j < (15* samplingRate)-1; j++)
		{
			copyADCout[j] = ADCout[j];
		}
	/*
		//Number of peaks is returned by the peakDetection function, for positions must pass in an array of size (15*5)-1
		numOfPeaks = peakDetection(copyADCout, *peakPositions);
	
		LCD_CLR();
	
		float BPM = (60 * numOfPeaks) / 15;	//Translates peaks detected in 15s to average number of peaks in a minute and thus bpm
		decIntToDecStr(BPM, &num, &numLen);
	
		stringLCD("Avg hrtrate /bpm", 16, 0, 0);
		stringLCD(num, numLen, 1, 0);
		TIM3Delay(5000);
		LCD_CLR();
		
		*/
		
		
		////////// End of main.c		///////////////////////////////////////////////////////////////////////////////////////////////	
		
	}

