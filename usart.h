#ifndef _USART_H_
#define _USART_H_
#include <stm32f4xx.h>
#include "ADC.h"
#include "DAC.h"
#include "RGB_Bar.h"
#include "segments.h"
#include "i2c.h"
#include "MPU_stuff.h"// INCLUDES


// DEFINES
#define USART_MODULE	USART3
#define USART_PORT		GPIOD
#define USART_TX_pin	8
#define USART_RX_pin	9
#define BAUDRATE			230400 //////////BAUDE


//MACROS
#define SET_BIT(REG, BIT) ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT) ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT) ((REG) & (BIT))
#define CLEAR_REG(REG) ((REG) = (0x0))
#define WRITE_REG(REG, VAL) ((REG) = (VAL))
#define READ_REG(REG) ((REG))
//#define MODIFY_REG(REG, CLEARMASK, SETMASK) WRITE_REG((REG),(((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
#define POSITION_VAL(VAL) (__CLZ(__RBIT(VAL))) 

#define BUFFER_SIZE 100 // BUFFER TO HOLD USER INPUT

// FUNCTION PROTOTYPES
void process_USART_Input(void);
void USART3_IRQHandler(void);
int comparestrings(const char *str1, const char *str2);

void send_usart(unsigned char d);
void init_USART(void);

void USART_SendData(char Data);
void USART_SendString (const char *text);

void send_integer(int num);
void send_float(float value);


//void USART_reset(void); // doesnt work

void clear_terminal (void); // clears terminal

//Moved from RGB_Bar
void USART_Vout(unsigned short ADC_DATA, unsigned int int_part, unsigned int frac_part);
void bar_graph(unsigned int int_part, unsigned int frac_part);
void send_Vout (unsigned int int_part, unsigned int frac_part);

// Global Variables
extern int16_t Accel_X_RAW, Accel_Y_RAW, Accel_Z_RAW;
extern float Ax, Ay, Az;
extern uint8_t check;




#endif

