#ifndef __EXTI_DRV_H
#define __EXTI_DRV_H

#include "stm32l1xx.h"

typedef struct
{
  uint8_t EXTI_PortSourceGPIOx;
  uint8_t EXTI_PinSourcex;
  uint16_t SYSCFG_EXTICR;
  EXTITrigger_TypeDef EXTI_Trigger;
  uint32_t priority;
}exti_drv_init_struct_typedef;

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler (void);
void EXTI15_10_IRQHandler(void);
void exti_drv_gpio_interrupt_init(exti_drv_init_struct_typedef* exti_drv_init_struct);

#endif
