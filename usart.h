#ifndef USART_H
#define USART_H

#include <stm32f4xx.h>

// Configuration
#define USART_MODULE USART3
#define USART_PORT GPIOD
#define USART_TX_pin 8
#define USART_RX_pin 9
#define BAUDRATE 9600

void init_USART(void);
void send_usart(unsigned char d);
void send_usart_string(const char *str);// function prototypes

#endif