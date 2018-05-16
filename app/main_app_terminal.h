#ifndef __MAIN_APP_MAC_H
#define __MAIN_APP_MAC_H

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
//#include "terminal_app.h"

#define SESSION_TIME			30
#define OPEN_SESSION  	  		"070701"
#define CLOSE_SESSION 	  		"070702"
#define UPLOAD_DATA_START 		"070703"
#define UPLOAD_DATA_COMPLETE	"070709"
#define SESSION_STARTED   		"070704"
#define SESSION_ACTIVE    		"070705"
#define SESSION_CLOSED    		"070706"
#define QUANT_OF_DATA_RESEIVED 	"070707"
#define UNSTABLE_CONNECTION		"070708"

#define iOPEN_SESSION  	  			101
#define iCLOSE_SESSION 	  			102
#define iUPLOAD_DATA_START 			103
#define iUPLOAD_DATA_COMPLETE		109
#define iSESSION_STARTED   			104
#define iSESSION_ACTIVE    			105
#define iSESSION_CLOSED    			106
#define iQUANT_OF_DATA_RESEIVED 	107
#define iUNSTABLE_CONNECTION		108

#define WAIT_DATA_TIME 30000

void main_app_terminal_start(void);
//uint8_t wait_data(uint32_t delayms);
uint8_t wait_cmd(uint32_t delayms, char* rxdata);
uint8_t data_finder(char *rxdata, char *finddata);
void terminal_start(void);
void upload_data_start (void);

#endif
