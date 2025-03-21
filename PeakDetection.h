#ifndef PeakDetection
#define PeakDetection
#include <stm32f429xx.h>
#include "Buzz.h"
#include "timer.h"
#include "lcd.h"


int peakDetection(float heartRate[], int* peakLocations[(15*5)-1]);	//Number of peaks is returned by the peakDetection function, for positions must pass in an array of size (15*5)-1


#endif