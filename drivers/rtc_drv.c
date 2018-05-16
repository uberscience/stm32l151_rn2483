#include "rtc_drv.h"

void rtc_drv_init(void){

    RTC_InitTypeDef RTC_InitStructure;
    RTC_TimeTypeDef RTC_TimeStructure;
    RTC_DateTypeDef RTC_DateStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Allow access to RTC Domain */
    PWR_RTCAccessCmd(ENABLE);

    /* Check if the StandBy flag is set */
    if (PWR_GetFlagStatus(PWR_FLAG_SB) != RESET)
    {
        /* Clear StandBy flag */
        PWR_ClearFlag(PWR_FLAG_SB);
        /* Wait for RTC APB registers synchronisation */
        RTC_WaitForSynchro();
        /* No need to configure the RTC as the RTC config(clock source, enable,
           prescaler,...) are kept after wake-up from STANDBY */
    }
    else
    {
        /* RTC Configuration ******************************************************/
        /* Reset RTC Domain */
        RCC_RTCResetCmd(ENABLE);
        RCC_RTCResetCmd(DISABLE);

        /* Enable the LSE OSC */
        RCC_LSEConfig(RCC_LSE_ON);

        /* Wait till LSE is ready */
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

        /* Select the RTC Clock Source */
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

        /* Enable the RTC Clock */
        RCC_RTCCLKCmd(ENABLE);

        /* Wait for RTC APB registers synchronisation */
        RTC_WaitForSynchro();

        /* Set the RTC time base to 1s */
        RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
        RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
        RTC_InitStructure.RTC_SynchPrediv = 0xFF;
        RTC_Init(&RTC_InitStructure);

        /* Set the time to 01h 00mn 00s AM */
        RTC_TimeStructure.RTC_H12     = RTC_H12_PM;
        RTC_TimeStructure.RTC_Hours   = 23;
        RTC_TimeStructure.RTC_Minutes = 59;
        RTC_TimeStructure.RTC_Seconds = 45;
        RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);

        RTC_DateStructure.RTC_Date = 1;
        RTC_DateStructure.RTC_Month = RTC_Month_January;
        RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Saturday;
        RTC_DateStructure.RTC_Year = 0;
        RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure);

    }
    /* Clear RTC Alarm A flag */
    RTC_ClearFlag(RTC_FLAG_ALRAF);
}

void rtc_drv_enter_STDBY_MODE(uint32_t sleep_time){
        uint32_t secgen;
        RTC_TimeTypeDef TIME;
        RTC_AlarmTypeDef RTC_AlarmStructure;

        RTC_AlarmCmd(RTC_Alarm_A, DISABLE);
        RTC_GetTime(RTC_Format_BIN, &TIME);

        /* Set the alarm X+5s */
        secgen = TIME.RTC_Hours * 3600 + TIME.RTC_Minutes * 60 + TIME.RTC_Seconds + sleep_time;
        RTC_AlarmStructure.RTC_AlarmTime.RTC_H12  =  TIME.RTC_H12;
        RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = (secgen / 3600)%24;
        RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = ((secgen - RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours * 3600)/60)%60;
        RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = (secgen - RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours * 3600 - RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes * 60)%60;
        RTC_AlarmStructure.RTC_AlarmDateWeekDay = 31;
        RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
        RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
        RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStructure);

        /* Clear PWR WakeUp flag */
        PWR_ClearFlag(PWR_FLAG_WU);

        /* Clear RTC Alarm A flag */
        RTC_ClearFlag(RTC_FLAG_ALRAF);

        /* Enable RTC Alarm A Interrupt: this Interrupt will wake-up the system from
           STANDBY mode (RTC Alarm IT not enabled in NVIC) */
        RTC_ITConfig(RTC_IT_ALRA, ENABLE);

        /* Enable the Alarm A */
        RTC_AlarmCmd(RTC_Alarm_A, ENABLE);

        /* Request to enter STANDBY mode */
        PWR_EnterSTANDBYMode();
}
