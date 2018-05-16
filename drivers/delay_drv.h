#ifndef __DELAY_DRV_H
#define __DELAY_DRV_H

#include "stm32l1xx.h"

#define F_APB1 8000000

#define delay_tim6_end_flag (TIM6->CR1&TIM_CR1_CEN)!=0
#define delay_tim6_rcc_off	RCC->APB1ENR &= ~RCC_APB1ENR_TIM6EN
#define delay_tim5_end_flag (TIM5->CR1&TIM_CR1_CEN)!=0
#define delay_tim5_rcc_off	RCC->APB1ENR &= ~RCC_APB1ENR_TIM5EN

void delay_ms(uint32_t delay);
void delay_20us(uint32_t delay);
void delay_ms_tim6_start(uint32_t delay);
void delay_ms_tim6_stop_and_off(void);
void delay_ms_tim5_start(uint32_t delay);
void delay_ms_tim5_stop_and_off(void);

#endif
