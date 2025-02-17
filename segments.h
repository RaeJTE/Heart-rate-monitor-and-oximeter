#include <stm32f429xx.h>
#ifndef SEGMENTS_H
#define SEGMENTS_H

// func declerations

void GPIO_Init(void);// gpio initialization

// Func to set the segments for a given digit
void displayDigit(uint8_t digit, uint8_t position);

int seg_main(void);

// Define pin mappings for segments
#define SEG_A (1 << 6)
#define SEG_B (1 << 7)
#define SEG_C (1 << 8)
#define SEG_D (1 << 5)
#define SEG_E (1 << 3)
#define SEG_F (1 << 2)
#define SEG_G (1 << 4)



// Define pin mappings for digit enable lines
#define DIGIT1_EN (1 << 10)
#define DIGIT2_EN (1 << 11)

#endif