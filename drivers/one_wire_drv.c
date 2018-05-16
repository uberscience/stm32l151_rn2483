#include "one_wire_drv.h"

void delay(uint32_t delay){
	while(delay--);
}

void one_wire_drv_init(void){
	one_wire_drv_vdd_init;
	one_wire_drv_dq_tx_init;
	one_wire_drv_dq_rx_init;
	one_wire_drv_vdd_enable;
	one_wire_drv_dq_tx_LO;
	delay_ms(10);
}


void one_wire_drv_send_presence(void){

    one_wire_drv_dq_tx_HI;
    delay(128);//delay_20us(1);//for (i = 0;i<128;i++);//~5us
	one_wire_drv_dq_tx_LO;//ONE_WIRE_DQ_TX_LO;
	delay(1500);//delay_20us(25);//for (i = 0;i<1500;i++);//~500 us
	one_wire_drv_dq_tx_HI;
	//delay_20us(1);
}

uint8_t one_wire_drv_reset(void){

	one_wire_drv_send_presence();
	one_wire_drv_delay_ms_start_wait(500);
	do{

		if(!(one_wire_drv_dq_rx_read_bit)){
			while(!(one_wire_drv_dq_rx_read_bit));
			one_wire_drv_drv_delay_ms_stop_and_off;
			return ONE_WIRE_DEV_FOUND;
		}
	}while(one_wire_drv_drv_delay_ms_stop_flag);
	one_wire_drv_drv_delay_ms_off;
	return ONE_WIRE_DEV_NOT_FOUND;
}

void one_wire_drv_send_bit(uint8_t bit){
	one_wire_drv_dq_tx_LO;
	if(bit>0){
		delay(20);//delay_20us(1);
		one_wire_drv_dq_tx_HI;
		delay(200);//delay_20us(5);
	}
	else{
		delay(200);//delay_20us(5);
		one_wire_drv_dq_tx_HI;
		delay(20);//delay_20us(1);
	}
}

void one_wire_drv_send_byte(uint8_t data) {
 uint8_t i;
  for (i = 8; i; i--) {
	  one_wire_drv_send_bit(data & 1);
    data >>= 1;
  }
}
uint8_t one_wire_drv_read_bit(void){
	uint8_t bit;
	one_wire_drv_dq_tx_LO;
	delay(5);//delay_20us(0);
	one_wire_drv_dq_tx_HI;
	delay(5);//delay_20us(1);
	bit = one_wire_drv_read_bit();
	delay(50);//delay_20us(4);
	return bit;
}

uint8_t one_wire_drv_read_byte(void){
	uint8_t byte = 0, i;
	  for (i = 8; i; i--) {
	    byte >>= 1;
	    if (one_wire_drv_read_bit() > 0)
	      byte |= 0x80;
	  }
	  //for(i = 0; i<200; i++);//~65us
	  return byte;
}

