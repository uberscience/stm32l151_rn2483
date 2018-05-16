#ifndef __CONFIG_APP_H
#define __CONFIG_APP_H

#include "uart_drv.h"
#include "rn2483_drv.h"
#include "eeprom_drv.h"

#define config_app_comm_interface_init uart_drv_init(USART2)
#define config_app_clear_buff CLEAR_STR(usart2RXData)

void config_app_write_cfgRN2483_eeprom (void);


#endif
