#include "main_app_mac.h"

void main_app_mac_start(void){
	char port[3], data[15];
	uint8_t join_status = 0, send_status = 0;

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
	if(rn2483_drv_cfg_check_eeprom_config() < 3)rn2483_drv_cfg_config_eeprom();
	else rn2483_drv_cfg_config_RN2483();
	rn2483_drv_cfg_comm_send_cmd("main program start\r\n");

    while(1)
    {
    	switch(join_status){

    	case rn2483_ACCEPTED:
    		switch(send_status){
    		case rn2483_MAC_TX_OK:
    			rn2483_drv_cfg_comm_send_cmd("message send complete\r\n");
    			join_status = SLEEP_STDBY;
    			send_status = 0;
    			break;
    		case rn2483_MAC_RX_OK:
    			rn2483_drv_cfg_comm_send_cmd("received message: ");
    			rn2483_drv_cfg_comm_send_cmd(data);
    			rn2483_drv_cfg_comm_send_cmd(rn2483_0D_0A);
    			rn2483_drv_cfg_comm_send_cmd(" port: ");
    			rn2483_drv_cfg_comm_send_cmd(port);
    			rn2483_drv_cfg_comm_send_cmd(rn2483_0D_0A);
    			send_status = 0;
    			break;
    		case rn2483_NO_FREE_CH:
    			rn2483_drv_cfg_comm_send_cmd(rn2483_cNO_FREE_CH);
    			rn2483_drv_reboot();
    			send_status = 0;
    			join_status = 0;
    			break;
    		case rn2483_MAC_ERR:
    			rn2483_drv_cfg_comm_send_cmd(rn2483_cMAC_ERR);
    			rn2483_drv_reboot();
    			send_status = 0;
    			join_status = 0;
    			break;
    		case rn2483_BUSY:
    			rn2483_drv_cfg_comm_send_cmd(rn2483_cBUSY);
    			send_status = rn2483_drv_busy_handler(port,data);
    			break;
    		case rn2483_NOT_JOINED:
    			rn2483_drv_cfg_comm_send_cmd(rn2483_cNOT_JOINED);
    			join_status = 0;
    			break;
    		case rn2483_INVALID_DATA_LEN:
    			rn2483_drv_cfg_comm_send_cmd(rn2483_cINVALID_DATA_LEN);
    			rn2483_drv_reboot();
    			join_status = 0;
    			send_status = 0;
    			break;
    		case rn2483_TIME_OUT:
    			rn2483_drv_cfg_comm_send_cmd("time out\r\n");
    			rn2483_drv_reboot();
    			send_status = 0;
    			join_status = 0;
    			break;
    		default:
    			rn2483_drv_cfg_comm_send_cmd("send...\r\n");
    			send_status = rn2483_drv_send_to_gateway("0ABCD8",CNF,_8_PORT,port,data);
    			break;
    		}
    		break;
    	case rn2483_DENIED:
    		join_status = 0;
    		rn2483_drv_cfg_comm_send_cmd(rn2483_MAC_JOIN_DENIED);
    		break;
    	case rn2483_NO_FREE_CH:
    		rn2483_drv_cfg_comm_send_cmd(rn2483_MAC_JOIN_NO_FREE_CH);
    		rn2483_drv_reboot();
    		join_status = 0;
    		break;
    	case rn2483_KEYS_NOT_INIT:
    		rn2483_drv_cfg_comm_send_cmd(rn2483_MAC_JOIN_KEYS_NOT_INIT);
    		rn2483_drv_cfg_config_eeprom();
    		rn2483_drv_reboot();
    		rn2483_drv_cfg_config_RN2483();
    		join_status = 0;
    		break;
    	case rn2483_TIME_OUT:
    		rn2483_drv_cfg_comm_send_cmd("time out\r\n");
    		rn2483_drv_reboot();
    		join_status = 0;
    	    break;
    	case SLEEP_STDBY:
    		rtc_drv_enter_STDBY_MODE(SLEEP_TIME);
    		break;
    	default:
    		rn2483_drv_cfg_comm_send_cmd("join...\r\n");
    		rn2483_drv_clear_buf;
    		join_status = rn2483_drv_join_gatevay();
    		break;
    	}
    }
}
