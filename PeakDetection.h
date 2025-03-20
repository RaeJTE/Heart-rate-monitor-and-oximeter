#ifndef PeakDetection
#define PeakDetection
#include <stm32f429xx.h>
#include "Buzz.h"
#include "timer.h"
#include "lcd.h"


void peakDetection(float heartRate[], int* numPeaks, int* peakPositions[15*5]);


#endif