#include "delay_drv.h"


void delay_ms(uint32_t delay)
{
	 RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
     TIM7->PSC = F_APB1/1000+1;				//������������� ������������
     TIM7->ARR = delay;						//������������� �������� ������������ �������, � ������ � �������� ��� ������� ������������ ������� ����������
     TIM7->EGR |= TIM_EGR_UG;				//���������� ������� ���������� ��� ������ ������ � �������� PSC � ARR
     TIM7->CR1 |= TIM_CR1_CEN|TIM_CR1_OPM;	//��������� ������ ������� ���� CEN � ������������� ����� ������ ������� ���������� ���� OPM
     while ((TIM7->CR1&TIM_CR1_CEN)!=0);
     RCC->APB1ENR &= ~RCC_APB1ENR_TIM7EN;
}

void delay_20us(uint32_t delay)
{
	 RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
     TIM7->PSC = F_APB1/50000+1;			//������������� ������������
     TIM7->ARR = delay;						//������������� �������� ������������ �������, � ������ � �������� ��� ������� ������������ ������� ����������
     TIM7->EGR |= TIM_EGR_UG;				//���������� ������� ���������� ��� ������ ������ � �������� PSC � ARR
     TIM7->CR1 |= TIM_CR1_CEN|TIM_CR1_OPM;	//��������� ������ ������� ���� CEN � ������������� ����� ������ ������� ���������� ���� OPM
     while ((TIM7->CR1&TIM_CR1_CEN)!=0);
     RCC->APB1ENR &= ~RCC_APB1ENR_TIM7EN;
}

void delay_ms_tim6_start(uint32_t delay){
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->PSC = F_APB1/1000+1;				//������������� ������������
    TIM6->ARR = delay;						//������������� �������� ������������ �������, � ������ � �������� ��� ������� ������������ ������� ����������
    TIM6->EGR |= TIM_EGR_UG;				//���������� ������� ���������� ��� ������ ������ � �������� PSC � ARR
    TIM6->CR1 |= TIM_CR1_CEN|TIM_CR1_OPM;	//��������� ������ ������� ���� CEN � ������������� ����� ������ ������� ���������� ���� OPM
}

void delay_ms_tim6_stop_and_off(void){
	TIM6->CR1 &= ~TIM_CR1_CEN;
	TIM6->CNT  = 0;
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM6EN;
}

void delay_ms_tim5_start(uint32_t delay){
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	TIM5->PSC = F_APB1/1000+1;				//������������� ������������
    TIM5->ARR = delay;						//������������� �������� ������������ �������, � ������ � �������� ��� ������� ������������ ������� ����������
    TIM5->EGR |= TIM_EGR_UG;				//���������� ������� ���������� ��� ������ ������ � �������� PSC � ARR
    TIM5->CR1 |= TIM_CR1_CEN|TIM_CR1_OPM;	//��������� ������ ������� ���� CEN � ������������� ����� ������ ������� ���������� ���� OPM
}

void delay_ms_tim5_stop_and_off(void){
	TIM5->CR1 &= ~TIM_CR1_CEN;
	TIM5->CNT  = 0;
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM6EN;
}
