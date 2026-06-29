#include "uart.h"

/* RCC Registers */
volatile uint32_t *pRCC_AHB1ENR = (uint32_t *)0x40023830;
volatile uint32_t *pRCC_APB1ENR = (uint32_t *)0x40023840;

/* GPIOA Registers */
volatile uint32_t *pGPIOA_MODER = (uint32_t *)0x40020000;
volatile uint32_t *pGPIOA_AFRL  = (uint32_t *)0x40020020;

/* USART2 Registers */
volatile uint32_t *pUSART2SR    = (uint32_t *)0x40004400;
volatile uint32_t *pUSART2DR    = (uint32_t *)0x40004404;
volatile uint32_t *pUSART2BRR   = (uint32_t *)0x40004408;
volatile uint32_t *pUSART2CR1   = (uint32_t *)0x4000440C;

void UART2_Init(uint32_t baudrate)
{
    /* Enable GPIOA Clock */
    *pRCC_AHB1ENR |= (1<<0);

    /* Enable USART2 Clock */
    *pRCC_APB1ENR |= (1<<17);

    /* PA2 -> Alternate Function */
    *pGPIOA_MODER &= ~(3<<4);
    *pGPIOA_MODER |=  (2<<4);

    /* AF7 for PA2 */
    *pGPIOA_AFRL &= ~(0xF<<8);
    *pGPIOA_AFRL |=  (7<<8);

    /* PA3 -> Alternate Function */
    *pGPIOA_MODER &= ~(3<<6);
    *pGPIOA_MODER |=  (2<<6);

    /* AF7 for PA3 */
    *pGPIOA_AFRL &= ~(0xF<<12);
    *pGPIOA_AFRL |=  (7<<12);

    /* BRR for 16 MHz and 115200 baud */
    *pUSART2BRR = 0x008B;

    /* Enable Transmitter */
    *pUSART2CR1 |= (1<<3);

    /* Enable Receiver */
    *pUSART2CR1 |= (1<<2);

    /* Enable USART2 */
    *pUSART2CR1 |= (1<<13);
}

void UART2_SendChar(char ch)
{
    while(((*pUSART2SR & (1<<7))) == 0);

    *pUSART2DR = ch;
}

void UART2_SendString(char *str)
{
    while(*str != '\0')
    {
        UART2_SendChar(*str);
        str++;
    }
}

char UART2_ReadChar(void)
{
    while(((*pUSART2SR & (1<<5))) == 0);

    return *pUSART2DR;
}

