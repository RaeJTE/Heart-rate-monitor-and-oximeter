#include "usart.h"
#include <stdio.h>

void send_usart(unsigned char d)
{
    while (!(USART_MODULE->SR & USART_SR_TC)); // Wait until transmission is complete
    USART_MODULE->DR = d;                      // Write byte to USART data register
}

void send_usart_string(const char *str)
{
    while (*str)
    {
        send_usart(*str++); // Send characters one by one
    }
}

void init_USART(void)
{
    unsigned char i1, i2;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // USART port clock enable

    USART_PORT->MODER &= ~((3u << (2 * USART_TX_pin)) | (3u << (2 * USART_RX_pin))); // Clear pin function bits
    USART_PORT->MODER |= ((2u << (2 * USART_TX_pin)) | (2u << (2 * USART_RX_pin)));  // Set pin function bits (alternate function)

    i1 = USART_TX_pin / 8; // Determine AFR register for TX pin
    i2 = USART_RX_pin >> 3; // Determine AFR register for RX pin

    // Alternate function select bits
    USART_PORT->AFR[i1] &= ~(0x0F << (4 * (USART_TX_pin - (i1 * 8))));
    USART_PORT->AFR[i1] |= (0x07 << (4 * (USART_TX_pin - (i1 * 8))));
    USART_PORT->AFR[i2] &= ~(0x0F << (4 * (USART_RX_pin - (i2 * 8))));
    USART_PORT->AFR[i2] |= (0x07 << (4 * (USART_RX_pin - (i2 * 8))));

    RCC->APB1ENR |= RCC_APB1ENR_USART3EN; // USART clock enable
    USART_MODULE->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE); // Enable USART, TX, RX
    USART_MODULE->BRR = SystemCoreClock / (BAUDRATE); // Set baud rate
}
