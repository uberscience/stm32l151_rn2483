#include "terminal_app.h"

void terminal_app_start(void){
	uint8_t join_status = 0, send_status = 0;
	uint32_t wait_delay_counter = terminal_app_SESSION_TIME;
	char port[3], data[15];

	rn2483_drv_cfg_comm_send_cmd("terminal app start\r\n");
	//terminal_app_delay_ms_start_wait(terminal_app_SESSION_TIME);

	do {
	    switch(join_status){
	    case rn2483_ACCEPTED:
	    	switch(send_status){
	    	case rn2483_MAC_TX_OK:
	    		rn2483_drv_cfg_comm_send_cmd("terminal app wait cmd\r\n");
	    		send_status = 0;
	    		break;
	    	case rn2483_MAC_RX_OK:
	    		rn2483_drv_cfg_comm_send_cmd("received message: ");
	    		rn2483_drv_cfg_comm_send_cmd(data);
	    		rn2483_drv_cfg_comm_send_cmd(rn2483_0D_0A);
	    		wait_delay_counter = terminal_app_SESSION_TIME;//terminal_app_delay_ms_stop_and_off;
	    		//terminal_app_delay_ms_start_wait(terminal_app_SESSION_TIME);
	    		if(USART_RX_HANDLER(data, terminal_app_START_UPLOAD)){
	    			rn2483_drv_cfg_comm_send_cmd("start upload process cmd\r\n");
	    			terminal_app_upload_data_start();
	    		}
	    		else if(USART_RX_HANDLER(data, terminal_app_STOP_SESSION)){
	    			rn2483_drv_cfg_comm_send_cmd("terminal app stop cmd\r\n");
	    			//terminal_app_upload_data_start();
	    			wait_delay_counter = 0;
	    		}
	    		send_status = 0;
	    		break;
	    	case rn2483_NO_FREE_CH:
	    		rn2483_drv_reboot();
	    		send_status = 0;
	    		join_status = 0;
	    		break;
	    	case rn2483_MAC_ERR:
	    		rn2483_drv_reboot();
	    		send_status = 0;
	    		join_status = 0;
	    		break;
	    	case rn2483_BUSY:
	    		send_status = rn2483_drv_busy_handler(port,data);
	    		break;
	    	case rn2483_NOT_JOINED:
	    		join_status = 0;
	    		break;
	    	case rn2483_INVALID_DATA_LEN:
	    		rn2483_drv_reboot();
	    		join_status = 0;
	    		send_status = 0;
	    		break;
	    	case rn2483_TIME_OUT:
	    		rn2483_drv_reboot();
	    		send_status = 0;
	    		join_status = 0;
	    		break;
	    	default:
	    		send_status = rn2483_drv_send_to_gateway(terminal_app_WAIT_CMD,CNF,_8_PORT,port,data);
	    		break;
	    	}
	    	break;
	    case rn2483_DENIED:
	    	join_status = 0;
	    	break;
	    case rn2483_NO_FREE_CH:
	    	rn2483_drv_reboot();
	    	join_status = 0;
	    	break;
	    case rn2483_KEYS_NOT_INIT:
	    	rn2483_drv_cfg_config_eeprom();
	    	rn2483_drv_cfg_config_RN2483();
	    	join_status = 0;
	    	break;
	    case rn2483_TIME_OUT:
	    	rn2483_drv_reboot();
	    	join_status = 0;
	        break;
	    default:
	    	rn2483_drv_clear_buf;
	    	join_status = rn2483_drv_join_gatevay();
	    	break;
	    }
	}while(wait_delay_counter--);//terminal_app_delay_ms_stop_flag);
	//terminal_app_delay_ms_stop_and_off;
	rn2483_drv_cfg_comm_send_cmd("terminal app stop\r\n");
}

void terminal_app_upload_data_start(void){

	char port[3], data[15], readydata[17] = "0000000000000000\0";
	uint8_t intdata[8];
	uint8_t join_status = 0, send_status = 0;
	uint32_t next_data_addr = FIRST_DATA_ADDR;
	logger_eeprom_data_struct wdata;
	uint32_t wait_delay_counter = terminal_app_SESSION_TIME;

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
				join_status = terminal_app_UPLOAD_COMPLETE;
			}
		    switch(join_status){
		    case rn2483_ACCEPTED:
		    	switch(send_status){
		    	case rn2483_MAC_TX_OK:
		    		next_data_addr += ONE_DATA_SIZE;
		    		//terminal_app_delay_ms_stop_and_off;
		    		//terminal_app_delay_ms_start_wait(terminal_app_SESSION_TIME);
		    		rn2483_drv_cfg_comm_send_cmd("quant of data uploaded\r\n");
		    		wait_delay_counter = terminal_app_SESSION_TIME;
		    		send_status = 0;
		    		break;
		    	case rn2483_MAC_RX_OK:
		    		next_data_addr += ONE_DATA_SIZE;
		    		rn2483_drv_cfg_comm_send_cmd("received message: ");
		    		rn2483_drv_cfg_comm_send_cmd(data);
		    		rn2483_drv_cfg_comm_send_cmd(rn2483_0D_0A);
		    		//terminal_app_delay_ms_stop_and_off;
		    		//terminal_app_delay_ms_start_wait(terminal_app_SESSION_TIME);
		    		wait_delay_counter = terminal_app_SESSION_TIME;
		    		if(USART_RX_HANDLER(data, terminal_app_STOP_UPLOAD)){
		    			wait_delay_counter = 0;//terminal_app_delay_ms_stop_and_off;
		    			rn2483_drv_cfg_comm_send_cmd("stop upload process cmd\r\n");
		    		}
		    		send_status = 0;
		    		break;
		    	case rn2483_BUSY:
		    		send_status = rn2483_drv_busy_handler(port,data);
		    		break;
		    	default:
		    		send_status = rn2483_drv_send_to_gateway(readydata,CNF,_8_PORT,port,data);
		    		break;
		    	}
		    	break;
		    case rn2483_TIME_OUT:
		    	rn2483_drv_reboot();
		    	join_status = 0;
		        break;
		    case terminal_app_UPLOAD_COMPLETE:
		    	rn2483_drv_cfg_comm_send_cmd("upload process complete\r\n");
		    	wait_delay_counter = 0;//terminal_app_delay_ms_stop_and_off;
		    	break;
		    default:
		    	rn2483_drv_clear_buf;
		    	join_status = rn2483_drv_join_gatevay();
		    	break;
		    }
		}while(wait_delay_counter--);
		//terminal_app_delay_ms_stop_and_off;
		rn2483_drv_cfg_comm_send_cmd("upload process stop\r\n");
}
