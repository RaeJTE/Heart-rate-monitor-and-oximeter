#include <stm32f4xx.h>

#ifndef _Buzz_H
#define _Buzz_H

#define BUZZ_PORT GPIOB
#define BUZZ_PIN 13


void initBuzz(void);
void endlessBuzz(void);
void tempBuzz(int time_ms, int freq);


#endif

