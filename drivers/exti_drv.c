#include "exti_drv.h"

void exti_drv_gpio_interrupt_init( exti_drv_init_struct_typedef* exti_drv_init_struct){

	EXTI_InitTypeDef exti;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(exti_drv_init_struct->EXTI_PortSourceGPIOx, exti_drv_init_struct->EXTI_PinSourcex);   // Connect EXTI line  to Port

	exti.EXTI_Mode    = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = exti_drv_init_struct->EXTI_Trigger;
	exti.EXTI_LineCmd = ENABLE;

	if((exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource0)||
	   (exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource1)||
	   (exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource2)||
	   (exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource3)) {

		switch(exti_drv_init_struct->EXTI_PinSourcex){
		case EXTI_PinSource0:
				SYSCFG->EXTICR[0] |= exti_drv_init_struct->SYSCFG_EXTICR;
				exti.EXTI_Line    = EXTI_Line0;
				EXTI_Init(&exti);
				NVIC_SetPriority(EXTI0_IRQn, exti_drv_init_struct->priority);
				NVIC_EnableIRQ  (EXTI0_IRQn);
				break;
		case EXTI_PinSource1:
				SYSCFG->EXTICR[0] |= exti_drv_init_struct->SYSCFG_EXTICR;
				exti.EXTI_Line    = EXTI_Line1;
				EXTI_Init(&exti);
				NVIC_SetPriority(EXTI1_IRQn, exti_drv_init_struct->priority);
				NVIC_EnableIRQ  (EXTI1_IRQn);
				break;
		case EXTI_PinSource2:
				SYSCFG->EXTICR[0] |= exti_drv_init_struct->SYSCFG_EXTICR;
				exti.EXTI_Line    = EXTI_Line2;
				EXTI_Init(&exti);
				NVIC_SetPriority(EXTI2_IRQn, exti_drv_init_struct->priority);
				NVIC_EnableIRQ  (EXTI2_IRQn);
				break;
		case EXTI_PinSource3:
				SYSCFG->EXTICR[0] |= exti_drv_init_struct->SYSCFG_EXTICR;
				exti.EXTI_Line    = EXTI_Line3;
				EXTI_Init(&exti);
				NVIC_SetPriority(EXTI3_IRQn, exti_drv_init_struct->priority);
				NVIC_EnableIRQ  (EXTI3_IRQn);
				break;
		}
	}

	else if((exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource4)||
		    (exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource5)||
		    (exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource6)||
			(exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource7)){

		switch(exti_drv_init_struct->EXTI_PinSourcex){

			case EXTI_PinSource4:
					SYSCFG->EXTICR[1] |= exti_drv_init_struct->SYSCFG_EXTICR;
					exti.EXTI_Line    = EXTI_Line4;
					EXTI_Init(&exti);
					NVIC_SetPriority(EXTI4_IRQn, exti_drv_init_struct->priority);
					NVIC_EnableIRQ  (EXTI4_IRQn);
					break;
			case EXTI_PinSource5:
					SYSCFG->EXTICR[1] |= exti_drv_init_struct->SYSCFG_EXTICR;
					exti.EXTI_Line    = EXTI_Line5;
					EXTI_Init(&exti);
					NVIC_SetPriority(EXTI9_5_IRQn, exti_drv_init_struct->priority);
					NVIC_EnableIRQ  (EXTI9_5_IRQn);
					break;
			case EXTI_PinSource6:
					SYSCFG->EXTICR[1] |= exti_drv_init_struct->SYSCFG_EXTICR;
					exti.EXTI_Line    = EXTI_Line6;
					EXTI_Init(&exti);
					NVIC_SetPriority(EXTI9_5_IRQn, exti_drv_init_struct->priority);
					NVIC_EnableIRQ  (EXTI9_5_IRQn);
					break;
			case EXTI_PinSource7:
					SYSCFG->EXTICR[1] |= exti_drv_init_struct->SYSCFG_EXTICR;
					exti.EXTI_Line    = EXTI_Line7;
					EXTI_Init(&exti);
					NVIC_SetPriority(EXTI9_5_IRQn, exti_drv_init_struct->priority);
					NVIC_EnableIRQ  (EXTI9_5_IRQn);
					break;
		}
	}

	else if((exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource8)||
		    (exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource9)||
		    (exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource10)||
			(exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource11)){
		switch(exti_drv_init_struct->EXTI_PinSourcex){
			case EXTI_PinSource8:
					SYSCFG->EXTICR[2] |= exti_drv_init_struct->SYSCFG_EXTICR;
					exti.EXTI_Line    = EXTI_Line8;
					EXTI_Init(&exti);
					NVIC_SetPriority(EXTI9_5_IRQn, exti_drv_init_struct->priority);
					NVIC_EnableIRQ  (EXTI9_5_IRQn);
					break;
			case EXTI_PinSource9:
					SYSCFG->EXTICR[2] |= exti_drv_init_struct->SYSCFG_EXTICR;
					exti.EXTI_Line    = EXTI_Line9;
					EXTI_Init(&exti);
					NVIC_SetPriority(EXTI9_5_IRQn, exti_drv_init_struct->priority);
					NVIC_EnableIRQ  (EXTI9_5_IRQn);
					break;
			case EXTI_PinSource10:
					SYSCFG->EXTICR[2] |= exti_drv_init_struct->SYSCFG_EXTICR;
					exti.EXTI_Line    = EXTI_Line10;
					EXTI_Init(&exti);
					NVIC_SetPriority(EXTI15_10_IRQn, exti_drv_init_struct->priority);
					NVIC_EnableIRQ  (EXTI15_10_IRQn);
					break;
			case EXTI_PinSource11:
					SYSCFG->EXTICR[2] |= exti_drv_init_struct->SYSCFG_EXTICR;
					exti.EXTI_Line    = EXTI_Line11;
					EXTI_Init(&exti);
					NVIC_SetPriority(EXTI15_10_IRQn, exti_drv_init_struct->priority);
					NVIC_EnableIRQ  (EXTI15_10_IRQn);
					break;
		}
	}
	else if((exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource12)||
			(exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource13)||
			(exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource14)||
			(exti_drv_init_struct->EXTI_PinSourcex == EXTI_PinSource15)){
		switch(exti_drv_init_struct->EXTI_PinSourcex){
			case EXTI_PinSource12:
					SYSCFG->EXTICR[3] |= exti_drv_init_struct->SYSCFG_EXTICR;
					exti.EXTI_Line    = EXTI_Line12;
					EXTI_Init(&exti);
					NVIC_SetPriority(EXTI15_10_IRQn, exti_drv_init_struct->priority);
					NVIC_EnableIRQ  (EXTI15_10_IRQn);
					break;
			case EXTI_PinSource13:
					SYSCFG->EXTICR[3] |= exti_drv_init_struct->SYSCFG_EXTICR;
					exti.EXTI_Line    = EXTI_Line13;
					EXTI_Init(&exti);
					NVIC_SetPriority(EXTI15_10_IRQn, exti_drv_init_struct->priority);
					NVIC_EnableIRQ  (EXTI15_10_IRQn);
					break;
			case EXTI_PinSource14:
					SYSCFG->EXTICR[3] |= exti_drv_init_struct->SYSCFG_EXTICR;
					exti.EXTI_Line    = EXTI_Line14;
					EXTI_Init(&exti);
					NVIC_SetPriority(EXTI15_10_IRQn, exti_drv_init_struct->priority);
					NVIC_EnableIRQ  (EXTI15_10_IRQn);
					break;
			case EXTI_PinSource15:
					SYSCFG->EXTICR[3] |= exti_drv_init_struct->SYSCFG_EXTICR;
					exti.EXTI_Line    = EXTI_Line15;
					EXTI_Init(&exti);
					NVIC_SetPriority(EXTI15_10_IRQn, exti_drv_init_struct->priority);
					NVIC_EnableIRQ  (EXTI15_10_IRQn);
					break;
			}
	}

}

void EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0) != RESET){
		        EXTI_ClearITPendingBit(EXTI_Line0);

			}
}

void EXTI1_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line1) != RESET){
		        EXTI_ClearITPendingBit(EXTI_Line1);

		}
}

void EXTI2_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line2) != RESET){
		        EXTI_ClearITPendingBit(EXTI_Line2);

		}
}

void EXTI3_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line3) != RESET){
		        EXTI_ClearITPendingBit(EXTI_Line3);

		}
}

void EXTI4_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line4) != RESET){
		        EXTI_ClearITPendingBit(EXTI_Line4);

		}
}

void EXTI9_5_IRQHandler (void){
	if(EXTI_GetITStatus(EXTI_Line5) != RESET){
		        EXTI_ClearITPendingBit(EXTI_Line5);

		}
	if(EXTI_GetITStatus(EXTI_Line6) != RESET){
			    EXTI_ClearITPendingBit(EXTI_Line6);

		}
	if(EXTI_GetITStatus(EXTI_Line7) != RESET){
		        EXTI_ClearITPendingBit(EXTI_Line7);

		}
	if(EXTI_GetITStatus(EXTI_Line8) != RESET){
		        EXTI_ClearITPendingBit(EXTI_Line8);

		}
	if(EXTI_GetITStatus(EXTI_Line9) != RESET){
		        EXTI_ClearITPendingBit(EXTI_Line9);

		}
}

void EXTI15_10_IRQHandler(void){

	if(EXTI_GetITStatus(EXTI_Line10) != RESET){
				EXTI_ClearITPendingBit(EXTI_Line10);

	}
	if(EXTI_GetITStatus(EXTI_Line11) != RESET){
		        EXTI_ClearITPendingBit(EXTI_Line11);

		}
	if(EXTI_GetITStatus(EXTI_Line12) != RESET){
		        EXTI_ClearITPendingBit(EXTI_Line12);

		}
	if(EXTI_GetITStatus(EXTI_Line13) != RESET){
		        EXTI_ClearITPendingBit(EXTI_Line13);

		}
	if(EXTI_GetITStatus(EXTI_Line14) != RESET){
		        EXTI_ClearITPendingBit(EXTI_Line14);

		}
	if(EXTI_GetITStatus(EXTI_Line15) != RESET){
		        EXTI_ClearITPendingBit(EXTI_Line15);

		}

}
