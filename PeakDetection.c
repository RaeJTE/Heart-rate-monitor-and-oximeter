#include "PeakDetection.h"

//Peak detection with buzzing
void peakDetection(float heartRate[])
{	
	char* number;	//Creates a pointer to be used to store a string conversion of a number - pointer necessary because of pointer decay when moving between .c files
	int numberLen;	//Variable to store length of string conversion of number
	int prevVal = 0;
	int gradientUp = 0;
	int index = 0;
	while(1)
	{
		decIntToDecStr(heartRate[index], &number, &numberLen);
		stringLCD(number, numberLen, 1, 0); //Prints array values to LCD
		output_dac2(heartRate[index]);      //Outputs the array values on the DAC
          
		if(heartRate[index] >= prevVal)
		{
			gradientUp = 1;
		}
		if(heartRate[index] <= prevVal && gradientUp == 1)
		{
			tempBuzz(100, 1000);
			gradientUp = 0;
		}
		prevVal = heartRate[index];
		
		if(index < (15* samplingRate)-1)
		{
			index++;
		}
		else
		{
			index = 0;
		}
		TIM3Delay(1);
	}
}


