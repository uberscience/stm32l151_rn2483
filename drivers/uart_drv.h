#ifndef __USART_H
#define __USART_H

#include "stm32l1xx.h"
#include <stdio.h>
#include <string.h>

#define BAUDRATE_USART1 57600
#define BAUDRATE_USART2 57600

volatile char usart1RXData[256],usart2RXData[256];
volatile uint8_t usart1_data_counter, usart2_data_counter, newdata;

void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void uart_drv_init(USART_TypeDef* USARTx);
void uart_drv_transmit_char(uint8_t data, USART_TypeDef* USARTx);
void uart_drv_transmit_str (char* str,	  USART_TypeDef* USARTx);
void CLEAR_STR(volatile char *str);
uint8_t USART_RX_HANDLER(char *rxdata, char *finddata);

#endif
