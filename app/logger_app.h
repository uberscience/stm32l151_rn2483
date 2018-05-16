#ifndef __LOGGER_APP_H
#define __LOGGER_APP_H

#include "eeprom_drv.h"
#include "rtc_drv.h"

#define FIRST_DATA_ADDR 0x08080070
#define LAST_DATA_ADDR 0x08080064
#define ONE_DATA_SIZE  10 //по факту 9 байт
#define EEPROM_DATA_LIMIT 250
#define NOT_NULL_FLAG 0xA7


typedef struct{
	uint8_t flag;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t year;
	uint8_t mounth;
	uint8_t day;
	uint16_t data;//занимает 3 байта, почему? незнаю, возможно баг
}logger_eeprom_data_struct;

logger_eeprom_data_struct *logger_data;
uint32_t *last_data_addr;
uint32_t *write_data_addr;

void 	logger_addr_eeprom_init(void);
void 	logger_write_data(logger_eeprom_data_struct* data);
uint8_t logger_quantity_of_data(void);
void 	logger_reset_last_addr(void);
void    logger_clear_all_data(void);
void 	logger_read_data(uint32_t addr, logger_eeprom_data_struct *data);

#endif
