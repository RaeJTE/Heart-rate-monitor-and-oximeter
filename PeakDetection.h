#ifndef PeakDetection
#define PeakDetection
#include <stm32f429xx.h>
#include "Buzz.h"
#include "timer.h"
#include "lcd.h"


int peakDetection(float heartRate[], int* peakLocations[(15*4)-1]);


#endif