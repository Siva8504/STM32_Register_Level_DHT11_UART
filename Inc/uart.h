/*
 * uart.h
 *
 *  Created on: Jun 28, 2026
 *      Author: HP
 */

#ifndef UART_H_
#define UART_H_


#include <stdint.h>

void UART2_Init(uint32_t baudrate);

void UART2_SendChar(char ch);

void UART2_SendString(char *str);

void UART2_SendNumber(uint32_t num);

char UART2_ReadChar(void);



#endif /* UART_H_ */
