#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include "stm32l1xx.h"
#include "string.h"

#define ONE_WIRE_DQ_PORT GPIOA
#define ONE_WIRE_RCC RCC_AHBPeriph_GPIOA
#define ONE_WIRE_DQ_PIN_TX GPIO_Pin_12
#define ONE_WIRE_DQ_PIN_RX GPIO_Pin_12

#define ONE_WIRE_VDD_PORT GPIOA
#define ONE_WIRE_VDD_RCC RCC_AHBPeriph_GPIOA
#define ONE_WIRE_VDD_PIN GPIO_Pin_11

#define ONE_WIRE_DEV_FOUND  1
#define ONE_WIRE_DEV_NFOUND 0

#define ONE_WIRE_ENABLE_VDD  GPIO_SetBits(ONE_WIRE_VDD_PORT,ONE_WIRE_VDD_PIN)
#define ONE_WIRE_DISABLE_VDD GPIO_ResetBits(ONE_WIRE_VDD_PORT,ONE_WIRE_VDD_PIN)

#define ONE_WIRE_DQ_TX_HI  GPIO_SetBits  (ONE_WIRE_DQ_PORT,ONE_WIRE_DQ_PIN_TX)
#define ONE_WIRE_DQ_TX_LO  GPIO_ResetBits(ONE_WIRE_DQ_PORT,ONE_WIRE_DQ_PIN_TX)

#define SEARCH_SUCCESSFUL     0x00
#define SEARCH_CRC_ERROR      0x01
#define SEARCH_ERROR          0xff
#define AT_FIRST              0xff

#define     OWI_CRC_OK      0x00    //!< CRC check succeded
#define     OWI_CRC_ERROR   0x01    //!< CRC check failed

#define     OWI_ROM_READ    0x33    //!< READ ROM command code.
#define     OWI_ROM_SKIP    0xcc    //!< SKIP ROM command code.
#define     OWI_ROM_MATCH   0x55    //!< MATCH ROM command code.
#define     OWI_ROM_SEARCH  0xf0    //!< SEARCH ROM command code.


/****************************************************************************
 Return codes
****************************************************************************/
#define     OWI_ROM_SEARCH_FINISHED     0x00    //!< Search finished return code.
#define     OWI_ROM_SEARCH_FAILED       0xff    //!< Search failed return code.

#define SEARCH_SENSORS 0x00
#define SENSORS_FOUND 0xff

#define MAX_DEVICES    0x01

//коды ошибок для функции чтения температуры
#define READ_SUCCESSFUL   0x00
#define READ_CRC_ERROR    0x01

//код семейства и коды команд датчика DS18B20
#define DS18B20_FAMILY_ID                0x28 
#define DS18B20_CONVERT_T                0x44
#define DS18B20_READ_SCRATCHPAD          0xbe
#define DS18B20_WRITE_SCRATCHPAD         0x4e
#define DS18B20_COPY_SCRATCHPAD          0x48
#define DS18B20_RECALL_E                 0xb8
#define DS18B20_READ_POWER_SUPPLY        0xb4

typedef struct
{
    unsigned char id[8];    //!< The 64 bit identifier.
} OWI_device;

void one_wire_init(void);
void send_presence(void);
uint8_t one_wire_reset(void);
void one_wire_write_bit(uint8_t bit);
void one_wire_write_byte(uint8_t data);
uint8_t one_wire_read_bit(void);
uint8_t one_wire_read_byte(void);
void 	delay(uint32_t delay);

unsigned char DS18B20_ReadTemperature(unsigned char * id, unsigned int* temperature);
unsigned char OWI_CheckScratchPadCRC(unsigned char * scratchpad);
void 		  OWI_MatchRom(unsigned char * romValue);
unsigned char OWI_CheckRomCRC(unsigned char * romValue);
unsigned char OWI_SearchDevices(OWI_device *devices,    unsigned char numDevices, unsigned char *num);
unsigned char OWI_SearchRom(unsigned char  *bitPattern, unsigned char lastDeviation);
unsigned char OWI_ComputeCRC8(unsigned char inData, unsigned char seed);

#endif /* ONEWIRE_H_ */
