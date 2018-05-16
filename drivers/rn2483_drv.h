#ifndef __RN2483_DRV_H
#define __RN2483_DRV_H
#include "gpio_drv.h"
#include "uart_drv.h"
#include "delay_drv.h"
#include "eeprom_drv.h"
#include "conversions_app.h"

#define rn2483_OK             	 255
#define SLEEP_STDBY 			 254
#define rn2483_ACCEPTED       	 1
#define rn2483_DENIED         	 2
#define rn2483_MAC_TX_OK      	 3
#define rn2483_NO_FREE_CH     	 4
#define rn2483_NOT_JOINED     	 5
#define rn2483_BUSY           	 6
#define rn2483_MAC_ERR        	 7
#define LORA_USART_ERR 	 		 8
#define rn2483_MAC_RX_OK      	 9
#define rn2483_INVALID_DATA_LEN  10
#define rn2483_KEYS_NOT_INIT	 14
#define rn2483_TIME_OUT			 15
#define rn2483_INVALID_PARAM	 16
#define rn2483_RADIO_TX_OK		 17
#define rn2483_RADIO_ERR		 18
#define rn2483_RADIO_RX_OK		 17

#define CNF            	 "cnf "
#define UNCNF          	 "uncnf "
#define _1_PORT			 "1 "
#define _2_PORT			 "2 "
#define _3_PORT			 "3 "
#define _4_PORT			 "4 "
#define _5_PORT			 "5 "
#define _6_PORT			 "7 "
#define _8_PORT			 "8 "
#define _9_PORT			 "9 "
#define _10_PORT		 "10 "

#define rn2483_TIME_FOR_JOIN	   15000
#define rn2483_TIME_FOR_SEND_DATA  30000
#define rn2483_TIME_FOR_CONF	   5000
#define rn2483_SYS_GET_VER    	      "sys get ver\r\n"
#define rn2483_MAC_JOIN_OTAA 	      "mac join otaa\r\n"
#define rn2483_MAC_JOIN_ABP 	      "mac join abp\r\n"
#define rn2483_MAC_JOIN_ACCEPTED	  "accepted\r\n"
#define rn2483_MAC_JOIN_DENIED     	  "denied\r\n"
#define rn2483_MAC_JOIN_NO_FREE_CH 	  "no_free_ch\r\n"
#define rn2483_MAC_JOIN_KEYS_NOT_INIT "keys_not_init\r\n"
#define rn2483_RADIO_MOD_LORA		  "radio set mod lora\r\n"
#define rn2483_CMD_OK				  "ok\r\n"
#define rn2483_MAC_SET_APPEUI		  "mac set appeui "
#define rn2483_MAC_SET_APPKEY		  "mac set appkey "
#define rn2483_MAC_TX				  "mac tx "
#define rn2483_0D_0A				  "\r\n"
#define rn2483_SAVE					  "save\r\n"
#define rn2483_cMAC_TX_OK			  "mac_tx_ok\r\n"
#define rn2483_cBUSY				  "busy\r\n"
#define rn2483_cNO_FREE_CH			  "no_free_ch\r\n"
#define rn2483_cNOT_JOINED			  "not_joined\r\n"
#define rn2483_cMAC_ERR				  "mac_err\r\n"
#define rn2483_cMAC_RX				  "mac_rx"
#define rn2483_cINVALID_DATA_LEN	  "invalid_data_len\r\n"
#define rn2483_MAC_PAUSE			  "mac pause\r\n"
#define rn2483_RADIO_TX				  "radio tx"
#define rn2483_cINVALID_PARAM		  "invalid_param\r\n"
#define rn2483_cRADIO_TX_OK			  "radio_tx_ok\r\n"
#define rn2483_cRADIO_ERR			  "radio_err\r\n"
#define rn2483_cRADIO_RX			  "radio_rx "

#define rn2483_pwr_error 11
#define rn2483_pwr_ok	 12

#define rn2483_drv_comm_int_init 	  uart_drv_init(USART1)
#define rn2483_drv_send_cmd(str) 	  uart_drv_transmit_str (str,USART1)
#define rn2483_drv_parse_rx_buff(str) USART_RX_HANDLER(usart1RXData, str)>0
#define rn2483_drv_rx_buf			  usart1RXData
#define rn2483_drv_delay_ms(delayms)  	   	  delay_ms(delayms)
#define rn2483_drv_delay_ms_start_wait(delay) delay_ms_tim6_start(delay)
#define rn2483_drv_delay_ms_stop_flag		  delay_tim6_end_flag
#define rn2483_drv_delay_ms_off				  delay_tim6_rcc_off
#define rn2483_drv_delay_ms_stop_and_off	  delay_ms_tim6_stop_and_off()
#define rn2483_drv_pwr_port_init gpio_drv_out_stdmode_init(GPIOA,GPIO_Pin_8)
#define rn2483_drv_pwr_enable	 gpio_drv_set_state(GPIOA,GPIO_Pin_8,ENABLE)
#define rn2483_drv_pwr_disable	 gpio_drv_set_state(GPIOA,GPIO_Pin_8,DISABLE)
#define rn2483_drv_clear_buf	 CLEAR_STR(usart1RXData)
#define rn2483_drv_cfg_comm_int_init  	   uart_drv_init(USART2)
#define rn2483_drv_cfg_comm_send_cmd(str)  uart_drv_transmit_str (str,USART2)
#define rn2483_drv_cfg_parse_rx_buff(str)  USART_RX_HANDLER(usart2RXData, str)>0
#define rn2483_drv_cfg_clear_buf		   CLEAR_STR(usart2RXData)

#define rn2483_drv_RADIO_SET_FREQ(val)  		rn2483_drv_send_cmd_w_arg("radio set freq", val)
#define rn2483_drv_RADIO_SET_PWR(val)			rn2483_drv_send_cmd_w_arg("radio set pwr", val)
#define rn2483_drv_RADIO_SET_MOD(val)			rn2483_drv_send_cmd_w_arg("radio set mod", val)
#define rn2483_drv_RADIO_SET_SF(val)			rn2483_drv_send_cmd_w_arg("radio set sf", val)
#define rn2483_drv_RADIO_SET_BW(val)			rn2483_drv_send_cmd_w_arg("radio set bw", val)

#define rn2483_answ_FOUND 	  0
#define rn2483_answ_NOT_FOUND 1

#define rn2483_eeprom_addr_cfg  0x08080000

typedef struct{
    char     DEVEUI[16];
    uint8_t  space1;
    char     APPEUI[16];
    uint8_t  space2;
    char     APPKEY[32];
    uint8_t  space3;
} rn2483_typedef_struct_cfg_eeprom;

rn2483_typedef_struct_cfg_eeprom *rn2483_conn_cfg;

uint8_t rn2483_drv_wait_answer(char* answer_str, uint32_t delayms);
uint8_t rn2483_drv_pwr_on (void);
uint8_t rn2483_drv_join_gatevay (void);
void 	rn2483_drv_cfg_config_RN2483 (void);
void 	rn2483_drv_cfg_config_eeprom (void);
uint8_t rn2483_drv_cfg_check_eeprom_config (void);
void	rn2483_drv_cfg_erase_eeprom (void);
uint8_t rn2483_drv_send_to_gateway(char *data, char *cnf_uncnf, char *port, char *rxport,char *rxdata);
uint8_t rn2483_drv_mac_rx_handler (void);
void 	rn2483_drv_rx_packet_parser(char* port, char* data);
void	rn2483_drv_reboot(void);
uint8_t rn2483_drv_busy_handler(char *rxport,char *rxdata);
uint8_t rn2483_drv_send_cmd_w_arg(char *cmd,char* arg);
uint8_t	rn2483_drv_radio_tx(char* data);

#endif
