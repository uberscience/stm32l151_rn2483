//*****************************************************************************
//
//! \file main.c
//! \brief main application
//! \version 1.0.0.0
//! \date $Creat_time$
//! \author $Creat_author$
//! \copy
//!
//! Copyright (c) 2014 CooCox.  All rights reserved.
//
//! \addtogroup project
//! @{//loramod
//! \addtogroup main
//! @{
//*****************************************************************************
#include "stm32l1xx.h"
#include "uart_drv.h"
#include "gpio_drv.h"
#include "rtc_drv.h"
#include "exti_drv.h"
#include "rn2483_drv.h"
#include "delay_drv.h"
#include "board_defines.h"
#include "conversions_app.h"
#include "logger_app.h"
#include "terminal_app.h"


int main(void)
{
	SystemInit();

	char port[3], data[15];
	logger_eeprom_data_struct wdata;
	RTC_TimeTypeDef Time;
	RTC_DateTypeDef Date;
	uint8_t join_status = 0, send_status = 0;
	uint16_t counter = 255;
	uint32_t next_data_addr = FIRST_DATA_ADDR;

	rtc_drv_init();
	//logger_reset_last_addr();
	green_led_init;
	red_led_init;
	green_led_disable;
	red_led_disable;
	uart_drv_init(USART2);
	uart_drv_transmit_str("pLora \r\n", USART2);
	if(rn2483_drv_pwr_on() == rn2483_pwr_ok)green_led_enable;
	else red_led_enable;
	if(rn2483_drv_cfg_check_eeprom_config() < 3)rn2483_drv_cfg_config_eeprom();
	else rn2483_drv_cfg_config_RN2483();
	//rn2483_drv_config_eeprom();
	/*if(send_status == rn2483_MAC_RX_OK){
		uart_drv_transmit_str(port, USART2);
		uart_drv_transmit_str("\r\n", USART2);
		uart_drv_transmit_str(data, USART2);
		uart_drv_transmit_str("\r\n", USART2);
	}*/
	rn2483_drv_cfg_comm_send_cmd("main program start\r\n");
    while(1)
    {
    	switch(join_status){
    	case rn2483_ACCEPTED:
    		switch(send_status){
    		case rn2483_MAC_TX_OK:
    			rn2483_drv_cfg_comm_send_cmd("message send complete\r\n");
    			send_status = 0;
    			break;
    		case rn2483_MAC_RX_OK:
    			rn2483_drv_cfg_comm_send_cmd("received message: ");
    			rn2483_drv_cfg_comm_send_cmd(data);
    			rn2483_drv_cfg_comm_send_cmd(rn2483_0D_0A);
    			if(USART_RX_HANDLER(data,TERMINAL_APP_START)>0){
    				rn2483_drv_cfg_comm_send_cmd("terminal app start cmd\r\n");
    				terminal_app_start();
    			}
    			send_status = 0;
    			/*uart_drv_transmit_str(port, USART2);
    			uart_drv_transmit_str("\r\n", USART2);
    			uart_drv_transmit_str(data, USART2);
    			uart_drv_transmit_str("\r\n", USART2);*/
    			break;
    		case rn2483_NO_FREE_CH:
    			rn2483_drv_reboot();
    			send_status = 0;
    			join_status = 0;
    			break;
    		case rn2483_MAC_ERR:
    			rn2483_drv_reboot();
    			send_status = 0;
    			join_status = 0;
    			break;
    		case rn2483_BUSY:
    			send_status = rn2483_drv_busy_handler(port,data);
    			break;
    		case rn2483_NOT_JOINED:
    			join_status = 0;
    			break;
    		case rn2483_INVALID_DATA_LEN:
    			rn2483_drv_reboot();
    			join_status = 0;
    			send_status = 0;
    			break;
    		case rn2483_TIME_OUT:
    			rn2483_drv_reboot();
    			send_status = 0;
    			join_status = 0;
    			break;
    		default:
    			send_status = rn2483_drv_send_to_gateway("0ABCD8",CNF,_8_PORT,port,data);
    			break;
    		}
    		break;
    	case rn2483_DENIED:
    		join_status = 0;
    		break;
    	case rn2483_NO_FREE_CH:
    		rn2483_drv_reboot();
    		/*rn2483_drv_send_cmd("mac get ch status 0\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 1\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 2\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 3\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 4\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 5\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 6\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 7\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 8\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 9\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 10\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 11\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 12\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 13\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 14\r\n");
    		delay_ms(100);
    		rn2483_drv_send_cmd("mac get ch status 15\r\n");
    		delay_ms(100);*/
    		join_status = 0;
    		break;
    	case rn2483_KEYS_NOT_INIT:
    		rn2483_drv_cfg_config_eeprom();
    		rn2483_drv_cfg_config_RN2483();
    		join_status = 0;
    		break;
    	case rn2483_TIME_OUT:
    		rn2483_drv_reboot();
    		join_status = 0;
    	    break;
    	default:
    		rn2483_drv_clear_buf;
    		join_status = rn2483_drv_join_gatevay();
    		break;
    	}
    	//delay_ms(60000);

    	/*logger_read_data(next_data_addr, &wdata);
    	if((wdata.flag) == NOT_NULL_FLAG){
    		next_data_addr += ONE_DATA_SIZE;
    		convert_dectoascii(wdata.day, data);
    		uart_drv_transmit_str(data, USART2);
    		uart_drv_transmit_char('/',USART2);
    		convert_dectoascii(wdata.mounth, data);
    		uart_drv_transmit_str(data, USART2);
       		uart_drv_transmit_char('/',USART2);
       		convert_dectoascii(wdata.year, data);
      		uart_drv_transmit_str(data, USART2);
      		uart_drv_transmit_char(' ',USART2);

      		convert_dectoascii(wdata.hour, data);
       		uart_drv_transmit_str(data, USART2);
       		uart_drv_transmit_char(':',USART2);
       		convert_dectoascii(wdata.minute, data);
       		uart_drv_transmit_str(data, USART2);
       		uart_drv_transmit_char(':',USART2);
       		convert_dectoascii(wdata.second, data);
      		uart_drv_transmit_str(data, USART2);
       		uart_drv_transmit_char(' ',USART2);

       		convert_dectoascii(wdata.data, data);
       		uart_drv_transmit_str("data: ", USART2);
       		uart_drv_transmit_str(data, USART2);
       		uart_drv_transmit_str("\r\n", USART2);
    	}
    	else uart_drv_transmit_str("upload complete\r\n",USART2);
    	wdata.day 	 = Date.RTC_Date;
    	wdata.mounth = Date.RTC_Month;
    	wdata.year	 = Date.RTC_Year;
    	wdata.hour 	 = Time.RTC_Hours;
    	wdata.minute = Time.RTC_Minutes;
    	wdata.second = Time.RTC_Seconds;
    	wdata.data	 = counter;
    	//logger_write_data(&wdata);
    	delay_ms(800);
    	counter++;*/
    }
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
	//red_led_enable;
	//debug_printf("Wrong parameters value: file %s on line %d\r\n", file, (int)line);
	while (1)
	{
	}
}/* assert_failed */
#endif/*USE_FULL_ASSERT*/
//! @}
//! @}


