
#ifndef __CONVERSIONS_APP_H_
#define __CONVERSIONS_APP_H_

#include "stm32l1xx.h"

#define INVALID_DATA   8
#define VALID_DATA     9

int  	CharToHex(char *s,char* buf,char Count);
void 	convert_dectoascii(uint16_t DEC, char *ASCII);
void 	convert_ds18b20_to_char(uint16_t temp,char* temp_char);
uint8_t check_hex_format(char *text,char *uncheckdataH,char* uncheckdataL);


#endif /* CONVERSION_H_ */
