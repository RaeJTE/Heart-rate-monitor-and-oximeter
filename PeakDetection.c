#include "PeakDetection.h"

//Peak detection with buzzing
int peakDetection(float heartRate[], int* peakLocations[(15*5)-1])	//15*5 is enough for the peaks of a 5Hz signal over 15s, we are not expecting signals with higher frequency than 4Hz.
{	
	stringLCD("Measuring", 9, 0, 0);
	
	char* number;	//Creates a pointer to be used to store a string conversion of a number
	int numberLen;	//Variable to store length of string conversion of number
	int threshOver = 0;
	int threshUnder = 0;
	int total = 0;
	int numOfPeaks = 0;
	int blockRepeat = 0;
	
	for(int index = 0; index <= (15*samplingRate)-1; index++)
	{
		total += heartRate[index];
	}
	
	int mean = total/(15*samplingRate);
		
	for(int index = 0; index <= (15*samplingRate)-1; index++)
		{
			decIntToDecStr(heartRate[index], &number, &numberLen);
			//stringLCD("123", numberLen, 1, 0); //Prints array values to LCD - using LCD adds in considerable delay that throws off output frequency
			output_dac2(heartRate[index]*1);      //Outputs the array values on the DAC - multiplied by 10 for easier viewing and to reduce effects of DAC noise (distinct from the noise in the raw data from the ADC)
			//output_dac2(100);	//100 = 8.5mV - test output for calibrating tolerance value
          
			if (heartRate[index] >= mean)
			{
				threshOver++;
			}
			else if (heartRate[index] < mean && heartRate[index-1] < mean)
			{
				threshOver = 0;
				blockRepeat = 0;
			}
				
			if(threshOver == 10 && blockRepeat == 0)
			{
				threshOver = 0;
				peakLocations[numOfPeaks] = index;	//Ignore warning here
				numOfPeaks++;
				blockRepeat = 1;
			}
			if(threshOver == 10)
			{
				tempBuzz(10, 1000);
			}
			TIM3Delay(1);
		}
	return numOfPeaks-1;
}

