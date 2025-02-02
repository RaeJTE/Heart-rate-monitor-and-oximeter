#include <stm32f4xx.h>
#include "Buzz.h"
#include "LCD.h"
#include "pitches.h"


//Melody and durationOfNotes from https://github.com/hibit-dev/buzzer/tree/master/src/movies/star_wars
//The instructions on how to play the specific tune is not my work.
int melody[] = { NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_F5, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_F5, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,

  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5,
  NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,
  NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_C5,
  NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,

  NOTE_C6, NOTE_G5, NOTE_G5, REST, NOTE_C5,
  NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,
  NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C6, NOTE_C6,
  NOTE_F6, NOTE_DS6, NOTE_CS6, NOTE_C6, NOTE_AS5, NOTE_GS5, NOTE_G5, NOTE_F5,
  NOTE_C6};

int durationsOfNotes[] = {8, 8, 8,
  2, 2,
  8, 8, 8, 2, 4,
  8, 8, 8, 2, 4,
  8, 8, 8, 2, 8, 8, 8,
  2, 2,
  8, 8, 8, 2, 4,

  8, 8, 8, 2, 4,
  8, 8, 8, 2, 8, 16,
  4, 8, 8, 8, 8, 8,
  8, 8, 8, 4, 8, 4, 8, 16,
  4, 8, 8, 8, 8, 8,

  8, 16, 2, 8, 8,
  4, 8, 8, 8, 8, 8,
  8, 8, 8, 4, 8, 4, 8, 16,
  4, 8, 4, 8, 4, 8, 4, 8,
  1};


void initBuzz(void)
{
	//ENABLE PORT
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	//ONLY GPIO B clock enable
	
	//CONFIGURE PORT:GPIOB  PIN:13 TO OUTPUT for Buzzer
	BUZZ_PORT->MODER &= ~(3UL << (2*BUZZ_PIN));			//Clear GPIOB1 & GPIOB0 - default INPUT state
	BUZZ_PORT->MODER |= (1UL << (2*BUZZ_PIN));			//ONLY set  GPIOB0 make Bit13 OUTPUT
	BUZZ_PORT->OTYPER &= ~(1UL << BUZZ_PIN);				// Make Bit13 output PUSH-PULL
	BUZZ_PORT->OSPEEDR &= ~(3UL << (2*BUZZ_PIN));		//Make Bit13 Speed 2Mhz to save power
	BUZZ_PORT->PUPDR &= ~(3UL <<(2*BUZZ_PIN));			// Turn off Pullup and Pull down resistors for Bit13
}

void endlessBuzz(void)
{
	while(1)
	{
		BUZZ_PORT->ODR^=(0b00000001<<BUZZ_PIN);	//Toggles buzzer
		lcd_delayus(1000);
	}
}

void tempBuzz(int time_ms, int freq_Hz)	//Actual timings very approximate for now until incorporation of proper timers
{
	int i =0;
	int period_us = 1000000/freq_Hz;
	while(i<(100*time_ms/period_us))
	{
		BUZZ_PORT->ODR^=(0b00000001<<BUZZ_PIN);	//Toggles buzzer
		lcd_delayus(1/period_us);
		i++;
	}
}


//Code adapted from https://github.com/hibit-dev/buzzer/blob/master/src/movies/star_wars/star_wars.ino
//Not fully original
void playMelody(void)
{
	int size = sizeof(durationsOfNotes) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durationsOfNotes[note];
    tempBuzz(melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    lcd_delayus(pauseBetweenNotes);

    //stop the tone playing:
    tempBuzz(0,0);
  }
}


