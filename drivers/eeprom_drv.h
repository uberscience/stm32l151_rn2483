#ifndef __EEPROM_DRV_H
#define __EEPROM_DRV_H

#include "stm32l1xx.h"

void write_eeprom_word(uint32_t address, uint32_t data);
void write_eeprom_halfw(uint32_t address, uint16_t data);
void write_eeprom_byte(uint32_t address, uint8_t data);

  /* #define COUNTERVAL_EEPROM_ADDR  0x08080083
	 #define PARAMS_EEPROM_ADDR   	 0x08080000
	 #define ALARM_EEPROM_ADDR       0x08080009
     params  = (params_eeprom*) PARAMS_EEPROM_ADDR;
     counter = (counter_eeprom*)COUNTERVAL_EEPROM_ADDR;
     alarm   = (alarm_eeprom*)  ALARM_EEPROM_ADDR;*/

#endif
