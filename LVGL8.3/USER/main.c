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
	HAL_Init();						// ��ʼ��HAL��
	Stm32_Clock_Init(RCC_PLL_MUL9); // ����ʱ��,72M
	delay_init(72);					// ��ʼ����ʱ����
	uart_init(115200);				// ��ʼ������
	LED_Init();						// ��ʼ��LED
	KEY_Init();						// ��ʼ������
	LCD_Init();						// ��ʼ��LCD
	tp_dev.init();					// ��������ʼ��
	Adjust_LCD();	   // ��ĻУ׼(KEY0У׼,KEY2�˳�У׼)

	// lvgl��ʼ��
	TIM3_Init(1000 - 1, 72 - 1); // ��ʱ��3,1ms
	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();

	// ����һ����ʽ
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
		if (key == KEY0_PRES) // KEY0����,��ִ��У׼����
		{
			LCD_Clear(WHITE); // ����
			TP_Adjust();	  // ��ĻУ׼
			TP_Save_Adjdata();
		}
		else if (key == KEY2_PRES) // KEY2���£����˳�whileѭ��
		{
			break;
		}
	}
}
