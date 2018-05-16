#ifndef __BOARD_DEFINES_H
#define __BOARD_DEFINES_H

#define green_led_init gpio_drv_out_stdmode_init(GPIOB,GPIO_Pin_3)
#define red_led_init   gpio_drv_out_stdmode_init(GPIOA,GPIO_Pin_15)
#define left_btn_init  gpio_drv_in_stdmode_init(GPIOB, GPIO_Pin_15)
#define right_btn_init gpio_drv_in_stdmode_init(GPIOA, GPIO_Pin_5)

#define green_led_enable  gpio_drv_set_state(GPIOB,GPIO_Pin_3,ENABLE)
#define green_led_disable gpio_drv_set_state(GPIOB,GPIO_Pin_3,DISABLE)
#define red_led_enable	  gpio_drv_set_state(GPIOA,GPIO_Pin_15,ENABLE)
#define red_led_disable	  gpio_drv_set_state(GPIOA,GPIO_Pin_15,DISABLE)
#define read_left_btn	  gpio_drv_read_pin_state(GPIOB, GPIO_Pin_15)
#define read_right_btn	  gpio_drv_read_pin_state(GPIOA, GPIO_Pin_5)

#endif
