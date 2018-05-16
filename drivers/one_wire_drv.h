#ifndef __ONE_WIRE_H
#define __ONE_WIRE_H

#include "gpio_drv.h"
#include "delay_drv.h"

#define ONE_WIRE_DEV_FOUND 		1
#define ONE_WIRE_DEV_NOT_FOUND  0

#define one_wire_drv_vdd_init gpio_drv_out_stdmode_init(GPIOA, GPIO_Pin_11)
#define one_wire_drv_dq_tx_init  gpio_drv_out_stdmode_init(GPIOA, GPIO_Pin_12)
#define one_wire_drv_dq_rx_init  gpio_drv_in_stdmode_init (GPIOA, GPIO_Pin_13)

#define one_wire_drv_vdd_enable	  	gpio_drv_set_state(GPIOA,GPIO_Pin_11,ENABLE)
#define one_wire_drv_vdd_disable  	gpio_drv_set_state(GPIOA,GPIO_Pin_11,DISABLE)
#define one_wire_drv_dq_tx_HI	  	gpio_drv_set_state(GPIOA,GPIO_Pin_12,ENABLE)
#define one_wire_drv_dq_tx_LO	  	gpio_drv_set_state(GPIOA,GPIO_Pin_12,DISABLE)
#define one_wire_drv_dq_rx_read_bit gpio_drv_read_pin_state(GPIOA,GPIO_Pin_13)

#define one_wire_drv_delay_ms_start_wait(delay)   delay_ms_tim6_start(delay)
#define one_wire_drv_drv_delay_ms_stop_flag		  delay_tim6_end_flag
#define one_wire_drv_drv_delay_ms_off			  delay_tim6_rcc_off
#define one_wire_drv_drv_delay_ms_stop_and_off	  delay_ms_tim6_stop_and_off()

void 	delay(uint32_t delay);
void 	one_wire_drv_init (void);
void 	one_wire_drv_send_presence(void);
uint8_t one_wire_drv_reset(void);
void 	one_wire_drv_send_bit(uint8_t bit);
void 	one_wire_drv_send_byte(uint8_t data);
uint8_t one_wire_drv_read_bit(void);
uint8_t one_wire_drv_read_byte(void);

#endif
