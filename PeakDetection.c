#include "PeakDetection.h"

//Peak detection with buzzing
void peakDetection(float heartRate[], int* numPeaks, int* peakPositions[15*5])	//15*5 is enough for the peaks of a 5Hz signal over 15s, we are not expecting signals with higher frequency than 4Hz.
{	
	char* number;	//Creates a pointer to be used to store a string conversion of a number - pointer necessary because of pointer decay when moving between .c files
	int numberLen;	//Variable to store length of string conversion of number
	int prevVal = 0;
	int gradientUp = 0;
	int holding = 0;
	*numPeaks = 0;
	const int tolerance = 2;	//currently only working as >= 4 for some reason
		
	for(int index = 0; index <= 15*samplingRate; index++)
		{
			decIntToDecStr(heartRate[index], &number, &numberLen);
			//stringLCD("123", numberLen, 1, 0); //Prints array values to LCD - using LCD adds in considerable delay that throws off output frequency
			output_dac2(heartRate[index]*1);      //Outputs the array values on the DAC - multiplied by 10 for easier viewing and to reduce effects of DAC noise (distinct from the noise in the raw data from the ADC)
			//output_dac2(100);	//100 = 8.5mV - test output for calibrating tolerance value
          
			if(heartRate[index] >= (prevVal-tolerance))
			{
				gradientUp = 1;
			}
			if(heartRate[index] >= (prevVal+tolerance) && heartRate[index] <= (prevVal-tolerance))
			{
				holding++;	//100 points = 100ms
			}
			if(heartRate[index] <= (prevVal+tolerance) && gradientUp == 1 && holding >= 10)
			{
				tempBuzz(100, 1000);
				*peakPositions[*numPeaks] = index;
				*numPeaks++;
				gradientUp = 0;
				holding = 0;
			}
			prevVal = heartRate[index];
			TIM3Delay(0);
		}
}


void peakDetectionByLevelCrossing(float heartRate[])
{
	char* number;	//Creates a pointer to be used to store a string conversion of a number - pointer necessary because of pointer decay when moving between .c files
	int numberLen;	//Variable to store length of string conversion of number
	int prevVal = 0;
	int crossed = 0;
	int holding = 0;
	int index = 0;
	int tolerance = 10;	//100 = 8.5mV
	
	while(1)
	{
		decIntToDecStr(heartRate[index], &number, &numberLen);
		stringLCD(number, numberLen, 1, 0); //Prints array values to LCD
		output_dac2(heartRate[index]*1);      //Outputs the array values on the DAC
		//output_dac2(100);	//100 = 8.5mV
          
		if(heartRate[index] >= 150)
		{
			crossed++;
		}
		if(crossed >= 100)
		{
			holding++;	//100 points = 100ms
		}
		if(1)
		{
			tempBuzz(100, 1000);
			crossed = 0;
			holding = 0;
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


