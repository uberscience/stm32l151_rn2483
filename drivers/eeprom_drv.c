#include "eeprom_drv.h"

void write_eeprom_word(uint32_t address, uint32_t data){
    FLASH_Status status;

    if(IS_FLASH_DATA_ADDRESS(address)){
        DATA_EEPROM_Unlock();
        status = DATA_EEPROM_ProgramWord(address, data);
        if(status == FLASH_COMPLETE) {
        } else {
        }
        DATA_EEPROM_Lock();
    }
}

void write_eeprom_halfw(uint32_t address, uint16_t data){
    FLASH_Status status;

    if(IS_FLASH_DATA_ADDRESS(address)){
        DATA_EEPROM_Unlock();
        status = DATA_EEPROM_ProgramHalfWord(address, data);
        if(status == FLASH_COMPLETE) {
        } else {
        }
        DATA_EEPROM_Lock();
    }
}

void write_eeprom_byte(uint32_t address, uint8_t data){
    FLASH_Status status;

    if(IS_FLASH_DATA_ADDRESS(address)){
        DATA_EEPROM_Unlock();
        status = DATA_EEPROM_ProgramByte(address, data);
        if(status == FLASH_COMPLETE) {
        } else {
        }
        DATA_EEPROM_Lock();
    }
}

