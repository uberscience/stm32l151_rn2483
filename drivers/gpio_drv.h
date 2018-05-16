#ifndef __GPIO_DRV_H
#define __GPIO_DRV_H

#include "stm32l1xx.h"

void gpio_drv_out_stdmode_init (GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void gpio_drv_set_state (GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, FunctionalState NewState);
void gpio_drv_in_stdmode_init (GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
ITStatus gpio_drv_read_pin_state(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

#endif
