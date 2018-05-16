#include "logger_app.h"


void logger_addr_eeprom_init(void){

	last_data_addr = (uint32_t*)LAST_DATA_ADDR;

	if((FIRST_DATA_ADDR+ONE_DATA_SIZE*EEPROM_DATA_LIMIT)>*last_data_addr){
		if(*last_data_addr == 0){
			logger_data = (logger_eeprom_data_struct*)FIRST_DATA_ADDR;
			write_eeprom_word(LAST_DATA_ADDR,FIRST_DATA_ADDR);
			}
		else{
			write_data_addr = *last_data_addr + ONE_DATA_SIZE;
			logger_data = (logger_eeprom_data_struct*)write_data_addr;
			write_eeprom_word(LAST_DATA_ADDR,write_data_addr);
		}
	}
	else {
		logger_data = (logger_eeprom_data_struct*)FIRST_DATA_ADDR;
		write_eeprom_word(LAST_DATA_ADDR,FIRST_DATA_ADDR);
	}
}

void logger_write_data(logger_eeprom_data_struct* data){
	logger_addr_eeprom_init();
	write_eeprom_byte((uint32_t) (&logger_data->flag), NOT_NULL_FLAG);
	write_eeprom_byte((uint32_t) (&logger_data->hour), data->hour);
	write_eeprom_byte((uint32_t) (&logger_data->minute), data->minute);
	write_eeprom_byte((uint32_t) (&logger_data->second), data->second);
	write_eeprom_byte((uint32_t) (&logger_data->year), data->year);
	write_eeprom_byte((uint32_t) (&logger_data->mounth), data->mounth);
	write_eeprom_byte((uint32_t) (&logger_data->day), data->day);
	write_eeprom_halfw((uint32_t)(&logger_data->data), data->data);
}

uint8_t logger_quantity_of_data(void){
	uint8_t data_counter, quantity = 0;
	logger_data = (logger_eeprom_data_struct*)FIRST_DATA_ADDR;
	for(data_counter = 0; data_counter < EEPROM_DATA_LIMIT; data_counter++){
		if(logger_data->flag == NOT_NULL_FLAG)quantity++;
		else return quantity;
		logger_data = (logger_eeprom_data_struct*)(&logger_data+ONE_DATA_SIZE);
	}

	return quantity;
}
void 	logger_reset_last_addr(void){
	last_data_addr = LAST_DATA_ADDR;
	write_eeprom_word(last_data_addr, 0x00000000);
}
void logger_clear_all_data(void){
	uint8_t data_counter = EEPROM_DATA_LIMIT;
	logger_data = (logger_eeprom_data_struct*)FIRST_DATA_ADDR;
	do{
		write_eeprom_byte((uint32_t) (&logger_data->flag),   0);
		write_eeprom_byte((uint32_t) (&logger_data->hour),   0);
		write_eeprom_byte((uint32_t) (&logger_data->minute), 0);
		write_eeprom_byte((uint32_t) (&logger_data->second), 0);
		write_eeprom_byte((uint32_t) (&logger_data->year),   0);
		write_eeprom_byte((uint32_t) (&logger_data->mounth), 0);
		write_eeprom_byte((uint32_t) (&logger_data->day),    0);
		write_eeprom_halfw((uint32_t)(&logger_data->data),   0);
		logger_data = (logger_eeprom_data_struct*)(&logger_data+ONE_DATA_SIZE);
	}while(data_counter--);
	write_eeprom_word(LAST_DATA_ADDR,FIRST_DATA_ADDR);
}

void logger_read_data(uint32_t addr, logger_eeprom_data_struct *data){

	logger_data = (logger_eeprom_data_struct*)addr;
	data->flag = logger_data->flag;
	data->hour = logger_data->hour;
	data->minute = logger_data->minute;
	data->second = logger_data->second;
	data->year = logger_data->year;
	data->mounth = logger_data->mounth;
	data->day = logger_data->day;
	data->data = logger_data->data;

}

