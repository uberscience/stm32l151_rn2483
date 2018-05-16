#include "rn2483_drv.h"

uint8_t rn2483_drv_pwr_on (void){

	rn2483_drv_comm_int_init;
	rn2483_drv_pwr_port_init;
	rn2483_drv_pwr_enable;
	rn2483_drv_delay_ms(250);
	rn2483_drv_clear_buf;
	rn2483_drv_send_cmd(rn2483_SYS_GET_VER);

	rn2483_conn_cfg =(rn2483_typedef_struct_cfg_eeprom*) rn2483_eeprom_addr_cfg;

	if(rn2483_drv_wait_answer("RN2483",1000) == rn2483_answ_FOUND)return rn2483_pwr_ok;
	else return rn2483_pwr_error;

}

uint8_t rn2483_drv_wait_answer(char* answer_str, uint32_t delayms){
	uint8_t return_val = rn2483_answ_NOT_FOUND;

	rn2483_drv_delay_ms_start_wait(delayms);
	do{
		rn2483_drv_delay_ms(20);
		if(rn2483_drv_parse_rx_buff(answer_str)){
			return_val = rn2483_answ_FOUND;
			rn2483_drv_clear_buf;
			rn2483_drv_delay_ms_stop_and_off;
		}
	}while(rn2483_drv_delay_ms_stop_flag);
	rn2483_drv_delay_ms_stop_and_off;
	return return_val;
}

uint8_t rn2483_drv_join_gatevay (void){
	rn2483_drv_send_cmd(rn2483_MAC_JOIN_OTAA);

	rn2483_drv_delay_ms_start_wait(rn2483_TIME_FOR_JOIN);
		do{
			rn2483_drv_delay_ms(20);
				 if(rn2483_drv_parse_rx_buff(rn2483_MAC_JOIN_ACCEPTED)){
				rn2483_drv_clear_buf;
				rn2483_drv_delay_ms_stop_and_off;
				return rn2483_ACCEPTED;
			}
			else if(rn2483_drv_parse_rx_buff(rn2483_MAC_JOIN_DENIED)){
				rn2483_drv_clear_buf;
				rn2483_drv_delay_ms_stop_and_off;
				return rn2483_DENIED;
			}
			else if(rn2483_drv_parse_rx_buff(rn2483_MAC_JOIN_NO_FREE_CH)){
				rn2483_drv_clear_buf;
				rn2483_drv_delay_ms_stop_and_off;
				return rn2483_NO_FREE_CH;
			}
			else if(rn2483_drv_parse_rx_buff(rn2483_MAC_JOIN_KEYS_NOT_INIT)){
				rn2483_drv_clear_buf;
				rn2483_drv_delay_ms_stop_and_off;
				return rn2483_KEYS_NOT_INIT;
			}
		}while(rn2483_drv_delay_ms_stop_flag);
		rn2483_drv_delay_ms_stop_and_off;
		return rn2483_TIME_OUT;
}

void rn2483_drv_cfg_config_RN2483 (void){

	rn2483_drv_clear_buf;
	rn2483_drv_send_cmd(rn2483_RADIO_MOD_LORA);
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd(rn2483_MAC_SET_APPEUI);
	rn2483_drv_send_cmd(rn2483_conn_cfg->APPEUI);
	rn2483_drv_send_cmd(rn2483_0D_0A);
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd(rn2483_MAC_SET_APPKEY);
	rn2483_drv_send_cmd(rn2483_conn_cfg->APPKEY);
	rn2483_drv_send_cmd(rn2483_0D_0A);
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);

	/*rn2483_drv_send_cmd("mac set deveui 0004a30b001c3317\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set devaddr 17d5f234\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set nwkskey 2b7e151628aed2a6abf7158809cf4f3c\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set appskey 2b7e151628aed2a6abf7158809cf4f3c\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);*/


	/*rn2483_drv_send_cmd("mac set ch dcycle 0 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 1 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 2 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);*/

	/*rn2483_drv_send_cmd("mac set ch freq 3 863000000\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch freq 4 863500000\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch freq 5 864000000\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch freq 6 864500000\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch freq 7 865000000\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch freq 8 865500000\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch freq 9 866000000\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch freq 10 866500000\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch freq 11 867000000\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch freq 12 867500000\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch freq 13 868000000\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch freq 14 868800000\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch freq 15 869000000\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);

	rn2483_drv_send_cmd("mac set ch drrange 1 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 1 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch drrange 2 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 2 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch drrange 3 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 3 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch drrange 4 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 4 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch drrange 5 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 5 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch drrange 6 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 6 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch drrange 7 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 7 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch drrange 8 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 8 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch drrange 9 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 9 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch drrange 10 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 10 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch drrange 11 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 11 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch drrange 12 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 12 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch drrange 13 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 13 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch drrange 14 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 14 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch drrange 15 0 5\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch dcycle 15 0\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);

	rn2483_drv_send_cmd("mac set ch status 3 on\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch status 4 on\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch status 5 on\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch status 6 on\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch status 7 on\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch status 8 on\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch status 9 on\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch status 10 on\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch status 11 on\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch status 12 on\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch status 13 on\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch status 14 on\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);
	rn2483_drv_send_cmd("mac set ch status 15 on\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);*/

	rn2483_drv_send_cmd("mac set adr on\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);

	rn2483_drv_send_cmd("mac set pwridx 1\r\n");
	rn2483_drv_wait_answer(rn2483_CMD_OK,rn2483_TIME_FOR_CONF);

}

void rn2483_drv_cfg_config_eeprom (void){

	uint8_t i;

	rn2483_conn_cfg =(rn2483_typedef_struct_cfg_eeprom*) rn2483_eeprom_addr_cfg;
	rn2483_drv_cfg_comm_int_init;
	rn2483_drv_cfg_comm_send_cmd("set the connection settings(APPEUI, APPKEY)");
	write_eeprom_byte((uint32_t)(&rn2483_conn_cfg->space1), 0x00);
	write_eeprom_byte((uint32_t)(&rn2483_conn_cfg->space2), 0x00);
	write_eeprom_byte((uint32_t)(&rn2483_conn_cfg->space3), 0x00);
	rn2483_drv_cfg_clear_buf;
	while(!(rn2483_drv_cfg_parse_rx_buff(rn2483_SAVE))){

		     if(rn2483_drv_cfg_parse_rx_buff("appeui ")){
		    if(rn2483_drv_cfg_parse_rx_buff(rn2483_0D_0A)){
		    	if(check_hex_format(usart2RXData,"appeui ","\r\n") == VALID_DATA){
		    		for( i = 7; i<23; i++){
                        write_eeprom_byte((uint32_t)(&rn2483_conn_cfg->APPEUI[i-7]), usart2RXData[i]);
		    		    if(i == 22)rn2483_drv_cfg_clear_buf;
	                }
		    		rn2483_drv_cfg_comm_send_cmd("appeui ok ");
		    		rn2483_drv_cfg_comm_send_cmd(rn2483_conn_cfg->APPEUI);
		    		rn2483_drv_cfg_comm_send_cmd(rn2483_0D_0A);
		    	}
		    	else {
		    		rn2483_drv_cfg_comm_send_cmd("invalid data");
		    		rn2483_drv_cfg_clear_buf;
		    	}
		    }
		}
		else if(rn2483_drv_cfg_parse_rx_buff("appkey ")){
			if(rn2483_drv_cfg_parse_rx_buff(rn2483_0D_0A)){
				if(check_hex_format(usart2RXData,"appkey ","\r\n") == VALID_DATA){
					for( i = 7; i<39; i++){
						write_eeprom_byte((uint32_t)(&rn2483_conn_cfg->APPKEY[i-7]), usart2RXData[i]);
					    if(i == 38)rn2483_drv_cfg_clear_buf;
				    }
					rn2483_drv_cfg_comm_send_cmd("appkey ok ");
					rn2483_drv_cfg_comm_send_cmd(rn2483_conn_cfg->APPKEY);
					rn2483_drv_cfg_comm_send_cmd(rn2483_0D_0A);
				}
				else{
					rn2483_drv_cfg_comm_send_cmd("invalid data");
					rn2483_drv_cfg_clear_buf;
				}
			}
		}
	}
}

uint8_t rn2483_drv_cfg_check_eeprom_config (void){
	uint8_t i;
	uint8_t checksumeui = 0, checksumkey = 0, returnval = 0;
	rn2483_conn_cfg =(rn2483_typedef_struct_cfg_eeprom*) rn2483_eeprom_addr_cfg;
	for(i = 0; i <16; i++){
		checksumeui|=rn2483_conn_cfg->APPEUI[i];
	}
	for(i = 0; i <32; i++){
		checksumkey|=rn2483_conn_cfg->APPKEY[i];
	}
	if(checksumeui>0)returnval|=1;

    if(checksumkey>0)returnval|=2;

    return returnval;
}

void rn2483_drv_cfg_erase_eeprom (void){
	uint8_t i;
	rn2483_conn_cfg =(rn2483_typedef_struct_cfg_eeprom*) rn2483_eeprom_addr_cfg;
	for(i = 0; i <16; i++){
		write_eeprom_byte((uint32_t)(&rn2483_conn_cfg->APPEUI[i]), 0x00);
	}
	for(i = 0; i <32; i++){
		write_eeprom_byte((uint32_t)(&rn2483_conn_cfg->APPKEY[i]), 0x00);
	}
}

uint8_t rn2483_drv_send_to_gateway(char *data, char *cnf_uncnf, char *port, char *rxport,char *rxdata){

	rn2483_drv_clear_buf;
	rn2483_drv_send_cmd(rn2483_MAC_TX);
	rn2483_drv_send_cmd(cnf_uncnf);
	rn2483_drv_send_cmd(port);
	rn2483_drv_send_cmd(data);
	rn2483_drv_send_cmd(rn2483_0D_0A);
	rn2483_drv_delay_ms_start_wait(rn2483_TIME_FOR_SEND_DATA);
	do{
		rn2483_drv_delay_ms(20);
			 if(rn2483_drv_parse_rx_buff(rn2483_cMAC_TX_OK)){
			rn2483_drv_clear_buf;
			rn2483_drv_delay_ms_stop_and_off;
			return rn2483_MAC_TX_OK;
		}
		else if(rn2483_drv_parse_rx_buff(rn2483_cMAC_RX)){
			//rn2483_drv_clear_buf;
			rn2483_drv_rx_packet_parser(rxport,rxdata);
			rn2483_drv_clear_buf;
			rn2483_drv_delay_ms_stop_and_off;
			return rn2483_MAC_RX_OK;
		}
		else if(rn2483_drv_parse_rx_buff(rn2483_cNO_FREE_CH)){
			rn2483_drv_clear_buf;
			rn2483_drv_delay_ms_stop_and_off;
			return rn2483_NO_FREE_CH;
		}
		else if(rn2483_drv_parse_rx_buff(rn2483_cMAC_ERR)){
			rn2483_drv_clear_buf;
			rn2483_drv_delay_ms_stop_and_off;
			return rn2483_MAC_ERR;
		}
		else if(rn2483_drv_parse_rx_buff(rn2483_cBUSY)){
			rn2483_drv_clear_buf;
			rn2483_drv_delay_ms_stop_and_off;
			return rn2483_BUSY;
			}
		else if(rn2483_drv_parse_rx_buff(rn2483_cNOT_JOINED)){
			rn2483_drv_clear_buf;
			rn2483_drv_delay_ms_stop_and_off;
			return rn2483_NOT_JOINED;
			}
		else if(rn2483_drv_parse_rx_buff(rn2483_cINVALID_DATA_LEN)){
			rn2483_drv_clear_buf;
			rn2483_drv_delay_ms_stop_and_off;
			return rn2483_INVALID_DATA_LEN;
		}
	}while(rn2483_drv_delay_ms_stop_flag);
	rn2483_drv_delay_ms_stop_and_off;
	return rn2483_TIME_OUT;
}

uint8_t rn2483_drv_busy_handler(char *rxport,char *rxdata){
	rn2483_drv_delay_ms_start_wait(rn2483_TIME_FOR_SEND_DATA);
		do{
			rn2483_drv_delay_ms(20);
				 if(rn2483_drv_parse_rx_buff(rn2483_cMAC_TX_OK)){
				rn2483_drv_clear_buf;
				rn2483_drv_delay_ms_stop_and_off;
				return rn2483_MAC_TX_OK;
			}
			else if(rn2483_drv_parse_rx_buff(rn2483_cMAC_RX)){
				//rn2483_drv_clear_buf;
				rn2483_drv_rx_packet_parser(rxport,rxdata);
				rn2483_drv_clear_buf;
				rn2483_drv_delay_ms_stop_and_off;
				return rn2483_MAC_RX_OK;
			}
			else if(rn2483_drv_parse_rx_buff(rn2483_cNO_FREE_CH)){
				rn2483_drv_clear_buf;
				rn2483_drv_delay_ms_stop_and_off;
				return rn2483_NO_FREE_CH;
			}
			else if(rn2483_drv_parse_rx_buff(rn2483_cMAC_ERR)){
				rn2483_drv_clear_buf;
				rn2483_drv_delay_ms_stop_and_off;
				return rn2483_MAC_ERR;
			}
			else if(rn2483_drv_parse_rx_buff(rn2483_cBUSY)){
				rn2483_drv_clear_buf;
				rn2483_drv_delay_ms_stop_and_off;
				return rn2483_BUSY;
				}
			else if(rn2483_drv_parse_rx_buff(rn2483_cNOT_JOINED)){
				rn2483_drv_clear_buf;
				rn2483_drv_delay_ms_stop_and_off;
				return rn2483_NOT_JOINED;
				}
			else if(rn2483_drv_parse_rx_buff(rn2483_cINVALID_DATA_LEN)){
				rn2483_drv_clear_buf;
				rn2483_drv_delay_ms_stop_and_off;
				return rn2483_INVALID_DATA_LEN;
			}
		}while(rn2483_drv_delay_ms_stop_flag);
		rn2483_drv_delay_ms_stop_and_off;
		return rn2483_TIME_OUT;
}

void rn2483_drv_rx_packet_parser(char* port, char* data){

	char mrxdata[6] = "mac_rx", i = 0, j = 0;

	delay_ms(100);
	do{
		if(mrxdata[j] == rn2483_drv_rx_buf[i]){
			j++;
		}
		i++;
	}while(j<6);
	i++;
	j=0;
	do{
		port[j] = rn2483_drv_rx_buf[i];
		j++;
		i++;
	}while(!(rn2483_drv_rx_buf[i] == ' '));
	i++;
	j=0;
	do{
		data[j] = rn2483_drv_rx_buf[i];
		j++;
		i++;
	}while(!(rn2483_drv_rx_buf[i] == '\r'));

}

uint8_t rn2483_drv_send_cmd_w_arg(char *cmd,char* arg){
	rn2483_drv_send_cmd(cmd);
	rn2483_drv_send_cmd(" ");
	rn2483_drv_send_cmd(arg);
	rn2483_drv_send_cmd(rn2483_0D_0A);
	return rn2483_drv_wait_answer(rn2483_CMD_OK,1000);
}

uint8_t 	rn2483_drv_radio_tx(char* data){
	rn2483_drv_clear_buf;
	rn2483_drv_send_cmd(rn2483_RADIO_TX);
	rn2483_drv_send_cmd(" ");
	rn2483_drv_send_cmd(data);
	rn2483_drv_send_cmd(rn2483_0D_0A);
	rn2483_drv_delay_ms_start_wait(rn2483_TIME_FOR_SEND_DATA);
	do {
		if(rn2483_drv_parse_rx_buff(rn2483_cRADIO_TX_OK)){
			rn2483_drv_clear_buf;
			rn2483_drv_delay_ms_stop_and_off;
			return rn2483_RADIO_TX_OK;
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

void	rn2483_drv_reboot(void){
	rn2483_drv_pwr_disable;
	delay_ms(100);
	rn2483_drv_pwr_on();
	rn2483_drv_cfg_config_RN2483();
	rn2483_drv_clear_buf;
}
