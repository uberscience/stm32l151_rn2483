#ifndef __TERMINAL_APP_H
#define __TERMINAL_APP_H

#include "rn2483_drv.h"
#include "logger_app.h"
#include "conversions_app.h"
#include "delay_drv.h"

#define terminal_app_delay_ms_start_wait(delay)  delay_ms_tim5_start(delay)
#define terminal_app_delay_ms_stop_flag		 	 delay_tim5_end_flag
#define terminal_app_delay_ms_off				 delay_tim5_rcc_off
#define terminal_app_delay_ms_stop_and_off	  	 delay_ms_tim5_stop_and_off()

#define terminal_app_SESSION_TIME 500000
#define terminal_app_UPLOAD_COMPLETE 254

#define TERMINAL_APP_START 		  "0701"
#define terminal_app_STOP_UPLOAD  "0702"
#define terminal_app_START_UPLOAD "0703"
#define terminal_app_STOP_SESSION "0704"
#define terminal_app_WAIT_CMD	  "0705"

void terminal_app_start(void);
void terminal_app_upload_data_start(void);

#endif
