#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "24cxx.h"
#include "w25qxx.h"
#include "touch.h"
#include "timer.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "MyGUI.h"

void Adjust_LCD(void);

int main(void)
{
	HAL_Init();						// 初始化HAL库
	Stm32_Clock_Init(RCC_PLL_MUL9); // 设置时钟,72M
	delay_init(72);					// 初始化延时函数
	uart_init(115200);				// 初始化串口
	LED_Init();						// 初始化LED
	KEY_Init();						// 初始化按键
	LCD_Init();						// 初始化LCD
	tp_dev.init();					// 触摸屏初始化
	Adjust_LCD();	   // 屏幕校准(KEY0校准,KEY2退出校准)

	// lvgl初始化
	TIM3_Init(1000 - 1, 72 - 1); // 定时器3,1ms
	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();

	// 创建一个样式
	lv_obj_t *switch_obj = lv_switch_create(lv_scr_act());
	lv_obj_set_size(switch_obj, 100, 50);
	lv_obj_align(switch_obj, LV_ALIGN_CENTER, 0, 0);

	while (1)
	{
		lv_task_handler();
		delay_ms(5);
	}
}

void Adjust_LCD(void)
{
	LCD_Clear(WHITE);
	u8 key;
	while (1)
	{
		key = KEY_Scan(0);
		if (key == KEY0_PRES) // KEY0按下,则执行校准程序
		{
			LCD_Clear(WHITE); // 清屏
			TP_Adjust();	  // 屏幕校准
			TP_Save_Adjdata();
		}
		else if (key == KEY2_PRES) // KEY2按下，则退出while循环
		{
			break;
		}
	}
}
