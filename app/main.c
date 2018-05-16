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
//! @{
//! \addtogroup main
//! @{
//*****************************************************************************
//#include "main_app_mac.h"
#include "main_app_terminal.h"

int main(void)
{
	SystemInit();

	main_app_terminal_start();

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


