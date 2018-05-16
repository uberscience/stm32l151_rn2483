#include "uart_drv.h"

void USART1_IRQHandler(void){

   //Receive Data register not empty interrupt
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
   {

       if((usart1_data_counter == 255) | (usart1RXData[0] == '\0'))
       {
           CLEAR_STR(usart1RXData);
           usart1_data_counter = 0;
       }
       USART_ClearITPendingBit(USART1, USART_IT_RXNE);
       usart1RXData[usart1_data_counter]=USART_ReceiveData (USART1);
       //uart_drv_transmit_char(usart1RXData[usart1_data_counter],USART1);
       usart1_data_counter++;
       newdata = 1;
   }
    if(USART_GetITStatus(USART1, USART_IT_ORE_RX) != RESET)
   {
    	//err+=1;
       if((usart1_data_counter == 255) | (usart1RXData[0] == '\0'))
       {
           CLEAR_STR(usart1RXData);
           usart1_data_counter = 0;
       }
    	       //USART_ClearITPendingBit(USART1, USART_IT_RXNE);
       usart1RXData[usart1_data_counter]=USART_ReceiveData (USART1);
       //Usart_Transmit(usart1RXData[usart1_data_counter],USART1);
       usart1_data_counter++;
       newdata = 1;
   }
    	//USART_ClearITPendingBit(USART1, USART_IT_ORE_RX);
}

void USART2_IRQHandler(void){

   //Receive Data register not empty interrupt
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
   {

       if((usart2_data_counter == 255) | (usart2RXData[0] == '\0'))
       {
           CLEAR_STR(usart2RXData);
           usart2_data_counter = 0;
       }
       USART_ClearITPendingBit(USART2, USART_IT_RXNE);
       usart2RXData[usart2_data_counter]=USART_ReceiveData (USART2);
       //Usart_Transmit(usart2RXData[usart2_data_counter],USART2);
       usart2_data_counter++;

   }
    if(USART_GetITStatus(USART2, USART_IT_ORE_RX) != RESET)
   {
    	//err+=1;
       if((usart2_data_counter == 255) | (usart2RXData[0] == '\0'))
       {
          CLEAR_STR(usart2RXData);
    	  usart2_data_counter = 0;
       }
       USART_ClearITPendingBit(USART2, USART_IT_RXNE);
       usart2RXData[usart2_data_counter]=USART_ReceiveData (USART2);
       //Usart_Transmit(usart2RXData[usart2_data_counter],USART2);
       usart2_data_counter++;
   }
    	//USART_ClearITPendingBit(USART1, USART_IT_ORE_RX);
}

void uart_drv_init(USART_TypeDef* USARTx)
{

  GPIO_InitTypeDef    GPIO_InitStruct;
  USART_InitTypeDef    USART_InitStruct;
  NVIC_InitTypeDef  NVIC_InitStructure;
    //������������� �������: PA9 - USART1_TX, PA10 - USART1_RX
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF; //����� �������������� �������
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; //����� Push-Pull
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL; //����� ��� ������������� ����������
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz; //�������� ����� ������������

  USART_InitStruct.USART_WordLength          = USART_WordLength_8b; //����� ����� 8 ���
  USART_InitStruct.USART_StopBits            = USART_StopBits_1; //1 ����-���
  USART_InitStruct.USART_Parity              = USART_Parity_No ; //��� �������� ��������
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��� ����������� ��������
  USART_InitStruct.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx; //������� ���������� � �������� USART1

  	  if(USARTx == USART1){
	    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); //�������� ������������ GPIO�
	    //��� ������� PA9, PA10 �������� �������������� ������� ������ � USART1
	    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	    //������������� ������ PA9 - USART1_Tx
	    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9; //��������� ������ PA9
	    GPIO_Init(GPIOA, &GPIO_InitStruct); //�������� ��������� ��������� � ��������� GPIO�
	    //������������� ������ PA10 - USART1_Rx �� ��������� �� Input floating
	    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_10; //��������� ������ PA10
	    GPIO_Init(GPIOA, &GPIO_InitStruct); //�������� ��������� ��������� � ��������� GPIO�
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //�������� ������������ USART1
	    USART_InitStruct.USART_BaudRate    = BAUDRATE_USART1; //�������� ������ 9600 ���
	    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  }
  else if(USARTx == USART2) {
	    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); //�������� ������������ GPIO�
	    //��� ������� PA9, PA10 �������� �������������� ������� ������ � USART1
	    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	    //������������� ������ PA9 - USART1_Tx
	    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_2; //��������� ������ PA9
	    GPIO_Init(GPIOA, &GPIO_InitStruct); //�������� ��������� ��������� � ��������� GPIO�
	    //������������� ������ PA10 - USART1_Rx �� ��������� �� Input floating
	    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_3; //��������� ������ PA10
	    GPIO_Init(GPIOA, &GPIO_InitStruct); //�������� ��������� ��������� � ��������� GPIO�
	    //������������� USART2
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //�������� ������������ USART1
	    USART_InitStruct.USART_BaudRate    = BAUDRATE_USART2; //�������� ������ 9600 ���
	    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  }

  USART_Init(USARTx, &USART_InitStruct); //�������� ��������� ��������� � ��������� USART1

  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  USART_Cmd(USARTx, ENABLE); //�������� USART1
  USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);  /* Enable Receive interrupts */

}

//������ �������� ������� ����� USART
void uart_drv_transmit_char(uint8_t data, USART_TypeDef* USARTx)
{
  while(!(USARTx->SR & USART_SR_TC));//���� ��������� ����� TC - ���������� ��������
  USARTx->DR = data;
}

void uart_drv_transmit_str(char* str, USART_TypeDef* USARTx)
{
  //uint16_t j = 0;
  while(*str)//!(str[j] == '\0'))
  {
	uart_drv_transmit_char(*str,USARTx);
	*str++;
  }
}


uint8_t USART_RX_HANDLER(char *rxdata, char *finddata)
{
    uint8_t found = 0;

    if(strstr(rxdata, finddata) > 0)found = 1;
    else found = 0;
    return found;
}

void CLEAR_STR(volatile char *str){
  uint16_t   i = 0;
           while(!(str[i] == '\0'))
           {
               str[i] = '\0';
               i++;
           }
}
