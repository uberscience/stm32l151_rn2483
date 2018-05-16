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
//#include "logger_app.h"
//#include "terminal_app.h"

#define SLEEP_TIME 10

void main_app_mac_start(void);


#endif
