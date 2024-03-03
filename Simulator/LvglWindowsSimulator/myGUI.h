#ifndef _MYGUI_H_
#define _MYGUI_H_

typedef enum
{
    /* red LED state */
    RED_LED_ON,
    RED_LED_OFF,
    /* blue LED state */
    BLUE_LED_ON,
    BLUE_LED_OFF,
    /* flags */


} GUI_flag_t;

void myGUI();
void label_show_demo();
void label_show_1();
void label_show_2();
void label_show_3();
void label_show_4();

void button_show_demo();
void label_show_speed();
void button_speed_up();
void button_speed_down();
void button_speed_stop();

void switch_show_demo();
void label_show_aircondition();
void switch_show_1();
void switch_show_2();
void switch_show_3();

void checkbox_show_demo();
void checkbox_show_food();

void bar_show_demo();
void bar_show_loading();

void spinner_show();

void led_show_demo();
void led_show_room();
#endif // !_MYGUI_H_
