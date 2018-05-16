#include "gpio_drv.h"

void gpio_drv_out_stdmode_init (GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	     if(GPIOx == GPIOA)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	else if(GPIOx == GPIOB)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	else if(GPIOx == GPIOC)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	else if(GPIOx == GPIOD)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	else if(GPIOx == GPIOE)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	else if(GPIOx == GPIOF)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	else if(GPIOx == GPIOG)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOG, ENABLE);
	else if(GPIOx == GPIOH)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOH, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void gpio_drv_set_state (GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, FunctionalState NewState)
{
	if (NewState != DISABLE)
	  {
		GPIO_SetBits(GPIOx,GPIO_Pin);
	  }
	  else
	  {
		GPIO_ResetBits(GPIOx,GPIO_Pin);
	  }
}

void gpio_drv_in_stdmode_init (GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStructure;

    	 if(GPIOx == GPIOA)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	else if(GPIOx == GPIOB)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	else if(GPIOx == GPIOC)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	else if(GPIOx == GPIOD)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	else if(GPIOx == GPIOE)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	else if(GPIOx == GPIOF)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
	else if(GPIOx == GPIOG)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOG, ENABLE);
	else if(GPIOx == GPIOH)RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOH, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

ITStatus gpio_drv_read_pin_state(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)>0) return SET;
	else return RESET;
}
