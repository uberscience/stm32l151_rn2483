#include "main_app_terminal.h"


void main_app_terminal_start(void){

	char rxdata[15];
	uint8_t wait_session_stat = 0;
	//uint8_t terminal_result = 0;
	rtc_drv_init();
	green_led_init;
	red_led_init;
	left_btn_init;
	rn2483_drv_cfg_comm_int_init;
	if(read_left_btn>0){
		green_led_enable;
		red_led_enable;
		while(read_left_btn);
		rn2483_drv_cfg_config_eeprom();
		green_led_disable;
		red_led_disable;
	}
	green_led_disable;
	red_led_disable;
	if(rn2483_drv_pwr_on() == rn2483_pwr_ok)green_led_enable;
	else red_led_enable;

	rn2483_drv_send_cmd(rn2483_MAC_PAUSE);
	rn2483_drv_wait_answer(rn2483_CMD_OK,1000);
	rn2483_drv_RADIO_SET_FREQ("868000000");
	rn2483_drv_RADIO_SET_PWR("-3");
	rn2483_drv_RADIO_SET_MOD("lora");
	rn2483_drv_RADIO_SET_SF("sf7");
	rn2483_drv_RADIO_SET_BW("125");
	rn2483_drv_cfg_comm_send_cmd("main program start\r\n");
	while(1){
		switch(wait_session_stat){
		case rn2483_RADIO_RX_OK:
			rn2483_drv_cfg_comm_send_cmd(rxdata);
			rn2483_drv_cfg_comm_send_cmd(rn2483_0D_0A);
			if(data_finder(rxdata,OPEN_SESSION)>0){
				terminal_start();
			}
			wait_session_stat = 0;
			break;
		case rn2483_INVALID_PARAM:
			rn2483_drv_cfg_comm_send_cmd(rn2483_cINVALID_PARAM);
			wait_session_stat = 0;
			break;
		case rn2483_RADIO_ERR:
			rn2483_drv_cfg_comm_send_cmd(rn2483_cRADIO_ERR);
			wait_session_stat = 0;
			break;
		case rn2483_BUSY:
			rn2483_drv_cfg_comm_send_cmd(rn2483_cBUSY);
			wait_session_stat = 0;
			break;
		case rn2483_TIME_OUT:
			rn2483_drv_cfg_comm_send_cmd("time out\r\n");
			wait_session_stat = 0;
			break;
		default:
			wait_session_stat = wait_cmd(WAIT_DATA_TIME,rxdata);
			break;
		}
	}


}

uint8_t wait_cmd(uint32_t delayms, char* rxdata){

	rn2483_drv_clear_buf;
	rn2483_drv_send_cmd("radio rx 0\r\n");
	rn2483_drv_delay_ms_start_wait(delayms);

	do {
		if(rn2483_drv_parse_rx_buff(rn2483_cRADIO_RX)){
			radio_rx_packet_parser(rxdata);
			rn2483_drv_clear_buf;
			rn2483_drv_delay_ms_stop_and_off;
			return rn2483_RADIO_RX_OK;
		}
		else if(rn2483_drv_parse_rx_buff(rn2483_cINVALID_PARAM)){
			rn2483_drv_clear_buf;
			rn2483_drv_delay_ms_stop_and_off;
			return rn2483_INVALID_PARAM;
		}
		else if(rn2483_drv_parse_rx_buff(rn2483_cRADIO_ERR)){
			rn2483_drv_clear_buf;
			rn2483_drv_delay_ms_stop_and_off;
			return rn2483_RADIO_ERR;
		}
		else if(rn2483_drv_parse_rx_buff(rn2483_cBUSY)){
			rn2483_drv_clear_buf;
			rn2483_drv_delay_ms_stop_and_off;
			return rn2483_BUSY;
		}
	} while (rn2483_drv_delay_ms_stop_flag);

	rn2483_drv_delay_ms_stop_and_off;
	return rn2483_TIME_OUT;
}

void radio_rx_packet_parser(char* data){

	CLEAR_STR(data);
	char mrxdata[8] = "radio_rx", i = 0, j = 0;

	delay_ms(100);
	do{
		if(mrxdata[j] == rn2483_drv_rx_buf[i]){
			j++;
		}
		i++;
	}while(j<8);
	i++;
	i++;
	j=0;
	do{
		data[j] = rn2483_drv_rx_buf[i];
		j++;
		i++;
	}while(!(rn2483_drv_rx_buf[i] == '\r'));

}

void terminal_start(void){

	uint8_t rxdatacmd = 0, txdataresult = 0, rxdataresult = 0;
	uint32_t wait_delay_counter = SESSION_TIME;
	char rxdata[15];
	rn2483_drv_cfg_comm_send_cmd("terminal start\r\n");
	do {
	    switch(txdataresult){
	    case rn2483_RADIO_TX_OK:
	    	switch(rxdataresult){
    			case rn2483_RADIO_RX_OK:
    				if(data_finder(rxdata,SESSION_ACTIVE)>0){
    					wait_delay_counter = SESSION_TIME;
    					txdataresult = 0;
    					rxdataresult = 0;
    				}
    				else if(data_finder(rxdata,UPLOAD_DATA_START)>0){
    					upload_data_start();
    					wait_delay_counter = SESSION_TIME;
    					rxdataresult = 0;
    				}
    				else if(data_finder(rxdata,CLOSE_SESSION)>0){
    					wait_delay_counter = 0;
    					txdataresult = iCLOSE_SESSION;
    				}
    				rxdataresult = 0;
    				//txdataresult = 0;
    				break;
    			case rn2483_INVALID_PARAM:
    				rxdataresult = 0;
    				break;
    			case rn2483_RADIO_ERR:
    				rxdataresult = 0;
    				break;
    			case rn2483_BUSY:
    				rxdataresult = 0;
    				break;
    			case rn2483_TIME_OUT:
    				rxdataresult = 0;
    				break;
    			default:
    				rxdataresult = wait_cmd(WAIT_DATA_TIME,rxdata);
    				break;
    			}
	    	break;
	    case rn2483_RADIO_ERR:
	    	txdataresult = 0;
	    	break;
	    case rn2483_BUSY:
	    	delay_ms(15000);
	    	txdataresult = 0;
	    	break;
	    case rn2483_INVALID_PARAM:
	    	txdataresult = 0;
	    	break;
	    case iCLOSE_SESSION:
	    	wait_delay_counter = 0;
	    	break;
	    default:
	    	txdataresult = rn2483_drv_radio_tx(SESSION_ACTIVE);
	    	break;
	    }
	}while(wait_delay_counter--);
	rn2483_drv_cfg_comm_send_cmd("terminal stop\r\n");
	//rn2483_drv_cfg_comm_send_cmd("terminal app stop\r\n");
}



void upload_data_start (void){

	uint8_t rxdatacmd = 0, txdataresult = 0, rxdataresult = 0;
	uint32_t next_data_addr = FIRST_DATA_ADDR;
	logger_eeprom_data_struct wdata;
	uint8_t intdata[8];
	uint32_t wait_delay_counter = SESSION_TIME;
	char rxdata[15], readydata[17] = "0000000000000000\0";

	rn2483_drv_cfg_comm_send_cmd("upload process start\r\n");

	do {

		logger_read_data(next_data_addr, &wdata);
		if((wdata.flag) == NOT_NULL_FLAG){
			intdata[0] = wdata.day;
			intdata[1] = wdata.mounth;
			intdata[2] = wdata.year;
			intdata[3] = wdata.hour;
			intdata[4] = wdata.minute;
			intdata[5] = wdata.second;
			intdata[6] = (wdata.data>>8)&0x00FF;
			intdata[7] = wdata.data&0x00FF;
			CharToHex((char*)intdata,readydata,8);
		}
		else{
			txdataresult = iUPLOAD_DATA_COMPLETE;
		}

	    switch(txdataresult){
	    case rn2483_RADIO_TX_OK:
	    	switch(rxdataresult){
    			case rn2483_RADIO_RX_OK:
    				if(data_finder(rxdata,QUANT_OF_DATA_RESEIVED)>0){
    					wait_delay_counter = SESSION_TIME;
    					next_data_addr += ONE_DATA_SIZE;
    				}
    				rxdataresult = 0;
    				txdataresult = 0;
    				break;
    			case rn2483_INVALID_PARAM:
    				rxdataresult = 0;
    				break;
    			case rn2483_RADIO_ERR:
    				rxdataresult = 0;
    				break;
    			case rn2483_BUSY:
    				rxdataresult = 0;
    				break;
    			case rn2483_TIME_OUT:
    				rxdataresult = 0;
    				break;
    			default:
    				rxdataresult = wait_cmd(WAIT_DATA_TIME,rxdata);
    				break;
    			}
	    	break;
	    case rn2483_RADIO_ERR:
	    	txdataresult = 0;
	    	break;
	    case rn2483_BUSY:
	    	delay_ms(15000);
	    	txdataresult = 0;
	    	break;
	    case rn2483_INVALID_PARAM:
	    	txdataresult = 0;
	    	break;
	    case iUPLOAD_DATA_COMPLETE:
	    	txdataresult = rn2483_drv_radio_tx(UPLOAD_DATA_COMPLETE);
	    	rn2483_drv_cfg_comm_send_cmd("upload process complete\r\n");
	    	wait_delay_counter = 0;
	    	break;
	    default:
	    	txdataresult = rn2483_drv_radio_tx(readydata);
	    	break;
	    }
	}while(wait_delay_counter--);
	rn2483_drv_cfg_comm_send_cmd("upload stop\r\n");

}



uint8_t data_finder(char *rxdata, char *finddata)
{
    uint8_t found = 0;

    if(strstr(rxdata, finddata) > 0)found = 1;
    else found = 0;
    return found;
}
