#ifndef __RTC_DRV_H
#define __RTC_DRV_H

#include "stm32l1xx.h"

//#define RTC_GetTime(RTC_Format_BIN, time) rtc_drv_get_time(time)
//#define RTC_GetDate(RTC_Format_BIN, date) rtc_drv_get_date(date)
//#define RTC_TimeTypeDef rtc_drv_TimeStructure
//#define RTC_DateTypeDef rtc_drv_DateStructure

void rtc_drv_init(void);
void rtc_drv_enter_STDBY_MODE(uint32_t sleep_time);

#endif
