#include "myGUI.h"
#include "lvgl.h"
#include "stdio.h"

#define scr_act_width()     lv_obj_get_width(lv_scr_act())
#define scr_act_height()    lv_obj_get_height(lv_scr_act())
//#define lv_obj_add_event	lv_obj_add_event_cb
//#define lv_button_create	lv_btn_create
static const lv_font_t* font = &lv_font_montserrat_14;

static lv_obj_t* label_speed;
static lv_obj_t* speed_down;
static lv_obj_t* speed_up;
static lv_obj_t* speed_stop;
static int speed_val;

static lv_obj_t* switch_;
static lv_obj_t* switch_cool;
static lv_obj_t* switch_heat;

static lv_obj_t* checkbox;
static lv_obj_t* checkbox_1;
static lv_obj_t* checkbox_2;
static lv_obj_t* checkbox_3;
static lv_obj_t* checkbox_4;

static lv_obj_t* label_load;
static lv_obj_t* label_per;
static lv_obj_t* bar;
static int bar_value = 0;

static lv_obj_t* spinner;

static lv_obj_t* led_1;
static lv_obj_t* led_2;
/****************************************************************************/
/*                        FUNCTION  REALIZATION                             */
/****************************************************************************/
static void event_callback_1(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        printf("LV_EVENT_VALUE_CHANGED\n");
    }
}
static void event_callback_2(lv_event_t* e)
{
    lv_obj_t* target = (lv_obj_t*)lv_event_get_target(e);
    if (target == speed_up)
        speed_val += 30;
    else if (target == speed_down)
        speed_val -= 30;
    else if (target == speed_stop)
        speed_val = 0;
    lv_label_set_text_fmt(label_speed, "Speed : %d RPM", speed_val);
}
static void event_callback_3(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        if (lv_obj_has_state(switch_, LV_STATE_CHECKED)) // if the state is CHECKED, return true
            printf("LED ON\n");
        else
            printf("LED OFF\n");
    }
}
static void event_callback_4(lv_event_t* e)
{
    lv_obj_t* target = (lv_obj_t*)lv_event_get_target(e);
    if (target == switch_cool)
    {
        if (lv_obj_has_state(switch_cool, LV_STATE_CHECKED))
            lv_obj_clear_state(switch_heat, LV_STATE_CHECKED);
    }
    else if (target == switch_heat)
    {
        if (lv_obj_has_state(switch_heat, LV_STATE_CHECKED))
            lv_obj_clear_state(switch_cool, LV_STATE_CHECKED);
    }
}
static void event_callback_5(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        if (lv_obj_has_state(checkbox, LV_STATE_CHECKED))
            printf("CHOICE ON\n");
        else
            printf("CHOICE_OFF\n");
    }
}
static void event_callback_6(lv_event_t* e)
{
    lv_obj_t* target = (lv_obj_t*)lv_event_get_target(e);
    if (target == checkbox_1)
    {
        if (lv_obj_has_state(checkbox_1, LV_STATE_CHECKED))
            printf("buy chicken\n");
        else
            printf("cancel chicken\n");
    }
    else if (target == checkbox_2)
    {
        if (lv_obj_has_state(checkbox_2, LV_STATE_CHECKED))
            printf("buy duck\n");
        else
            printf("cancel duck\n");
    }
}
static void event_callback_7(lv_event_t* e)
{
    lv_obj_t* target = (lv_obj_t*)lv_event_get_target(e);
    if (target == led_1)
    {
        lv_led_toggle(led_1);
        if (lv_led_get_brightness(led_1) == LV_LED_BRIGHT_MAX)
        {
            printf("Red  LED:   ON\n");
        }
        else if(lv_led_get_brightness(led_1) == LV_LED_BRIGHT_MIN)
        {
            printf("Red  LED:   OFF\n");
        }
    }
    else if (target == led_2)
    {
        lv_led_toggle(led_2);
        if (lv_led_get_brightness(led_2) == LV_LED_BRIGHT_MAX)
        {
            printf("Blue LED:   ON\n");
        }
        else if (lv_led_get_brightness(led_2) == LV_LED_BRIGHT_MIN)
        {
            printf("Blue LED:   OFF\n");
        }
    }

}

/****************************************************************************/
/*                        FUNCTION  REALIZATION                             */
/****************************************************************************/
static void timer_callback_1(lv_timer_t* timer)
{
    if (bar_value < 100)
    {
        bar_value++;
        lv_bar_set_value(bar, bar_value, LV_ANIM_ON);
        lv_label_set_text_fmt(label_per, "%d %%", lv_bar_get_value(bar));
        switch ((bar_value / 4) % 4)
        {
        case 0: lv_label_set_text(label_load, "LOADING"); break;
        case 1: lv_label_set_text(label_load, "LOADING ."); break;
        case 2: lv_label_set_text(label_load, "LOADING . ."); break;
        case 3: lv_label_set_text(label_load, "LOADING . . ."); break;
        }
    }
    else
    {
        lv_label_set_recolor(label_load, true);
        lv_obj_set_style_text_font(label_load, &lv_font_montserrat_20, LV_STATE_DEFAULT);
        lv_label_set_text(label_load, "#00ff00 Finished! #");
        lv_label_set_text_fmt(label_per, "%d %%", lv_bar_get_value(bar));
    }
}

/****************************************************************************/
/*                        FUNCTION  REALIZATION                             */
/****************************************************************************/
void myGUI()
{

}

/****************************************************************************/
/*                        FUNCTION  REALIZATION                             */
/****************************************************************************/
void label_show_demo()
{
    //create an label_obj
    lv_obj_t* label = lv_label_create(lv_scr_act());
    // set label text
    lv_label_set_text_fmt(label, "hello, %s", "world!");
    // set background color
    lv_obj_set_style_bg_color(label, lv_color_hex(0xff0000), LV_STATE_DEFAULT);
    // set background transparency
    lv_obj_set_style_bg_opa(label, 100, LV_STATE_DEFAULT);

    //// set font style & size
    //lv_obj_set_style_text_font(label, &lv_font_montserrat_30, LV_STATE_DEFAULT);
    //// set text color
    //lv_obj_set_style_text_color(label, lv_color_hex(0x0000ff), LV_STATE_DEFAULT);
}
void label_show_1()
{
    if (scr_act_width() <= 320)
        font = &lv_font_montserrat_10;
    else if (scr_act_width() <= 480)
        font = &lv_font_montserrat_14;
    else
        font = &lv_font_montserrat_20;

    //create an label_obj
    lv_obj_t* label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "#0000ff Re-color# #ff00ff words# #ff0000 of a# "
        "label, align the lines to the center"
        "and wrap long text automatically");
    lv_label_set_recolor(label, true);
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
    lv_obj_set_width(label, scr_act_width() / 3);
    lv_obj_align(label, LV_ALIGN_CENTER, -scr_act_width() / 3, 0);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
}
void label_show_2()
{
    if (scr_act_width() <= 320)
        font = &lv_font_montserrat_10;
    else if (scr_act_width() <= 480)
        font = &lv_font_montserrat_14;
    else
        font = &lv_font_montserrat_20;

    lv_obj_t* label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "It is a circularly scrolling text. ");
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
    lv_obj_set_width(label, scr_act_width() / 3);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}
void label_show_3()
{
    if (scr_act_width() <= 320)
        font = &lv_font_montserrat_10;
    else if (scr_act_width() <= 480)
        font = &lv_font_montserrat_14;
    else
        font = &lv_font_montserrat_20;

    lv_obj_t* label = lv_label_create(lv_scr_act());
    lv_label_set_text_fmt(label, "Label can set text like %s", "printf");
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
    lv_obj_set_width(label, scr_act_width() / 3);
    lv_obj_align(label, LV_ALIGN_CENTER, scr_act_width() / 3, 0);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    lv_obj_t* label_shadow = lv_label_create(lv_scr_act());
    lv_label_set_text(label_shadow, lv_label_get_text(label));
    lv_obj_set_style_text_font(label_shadow, font, LV_PART_MAIN);
    lv_obj_set_width(label_shadow, scr_act_width() / 3);
    lv_obj_set_style_text_opa(label_shadow, LV_OPA_30, LV_PART_MAIN);
    lv_obj_set_style_text_color(label_shadow, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_text_align(label_shadow, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_align_to(label_shadow, label, LV_ALIGN_TOP_LEFT, 3, 3);
}
void label_show_4()
{
    lv_obj_t* label1 = lv_label_create(lv_scr_act());               //创建label对象    
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);             //设置label longmode
    lv_label_set_recolor(label1, true);                             //设置label 重着色
    lv_label_set_text(label1, "#0000ff Re-color# #ff00ff words# #ff0000 of a# "
        "label,align the lines to center "
        "and wrap long text automatically"); //设置label字体
    lv_obj_set_width(label1, 150);                                  //设置对象宽度
    lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);   //设置对象字体样式居中
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, -40);                  //设置对象居中

    lv_obj_t* label2 = lv_label_create(lv_scr_act());               //创建label对象 
    lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR);  //设置label longmode
    lv_obj_set_width(label2, 150);                                  //设置对象宽度
    lv_label_set_text(label2, "It is a circularly scrolling text"); //设置label字体
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 40);                   //设置对象居中
}

/****************************************************************************/
/*                        FUNCTION  REALIZATION                             */
/****************************************************************************/
void button_show_demo()
{
    lv_obj_t* button = lv_button_create(lv_scr_act());

    lv_obj_set_size(button, 100, 50);
    lv_obj_set_align(button, LV_ALIGN_CENTER);
    //lv_obj_set_style_bg_color(button, lv_color_hex(0x00ff00), LV_STATE_PRESSED);

    lv_obj_add_flag(button, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_event(button, event_callback_1, LV_EVENT_VALUE_CHANGED, NULL);
}
void label_show_speed()
{
    if (scr_act_width() <= 320)
        font = &lv_font_montserrat_10;
    else if (scr_act_width() <= 480)
        font = &lv_font_montserrat_14;
    else
        font = &lv_font_montserrat_20;

    label_speed = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(label_speed, font, LV_PART_MAIN);
    lv_label_set_text(label_speed, "Speed : 0 RPM");
    lv_obj_align(label_speed, LV_ALIGN_CENTER, 0, -scr_act_height() / 3);
}
void button_speed_up()
{
    speed_up = lv_button_create(lv_scr_act());
    lv_obj_set_size(speed_up, scr_act_width() / 4, scr_act_height() / 6);
    lv_obj_align(speed_up, LV_ALIGN_CENTER, -scr_act_width() / 3, 0);
    lv_obj_add_event(speed_up, event_callback_2, LV_EVENT_CLICKED, NULL);

    lv_obj_t* label = lv_label_create(speed_up);
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
    lv_label_set_text(label, "Speed +");
    lv_obj_set_align(label, LV_ALIGN_CENTER);
}
void button_speed_down()
{
    speed_down = lv_button_create(lv_scr_act());
    lv_obj_set_size(speed_down, scr_act_width() / 4, scr_act_height() / 6);
    lv_obj_align(speed_down, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event(speed_down, event_callback_2, LV_EVENT_CLICKED, NULL);

    lv_obj_t* label = lv_label_create(speed_down);
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
    lv_label_set_text(label, "Speed -");
    lv_obj_set_align(label, LV_ALIGN_CENTER);
}
void button_speed_stop()
{
    speed_stop = lv_button_create(lv_scr_act());
    lv_obj_set_size(speed_stop, scr_act_width() / 4, scr_act_height() / 6);
    lv_obj_align(speed_stop, LV_ALIGN_CENTER, scr_act_width() / 3, 0);
    lv_obj_set_style_bg_color(speed_stop, lv_color_hex(0xef5f60), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(speed_stop, lv_color_hex(0xff0000), LV_STATE_PRESSED);
    lv_obj_add_event(speed_stop, event_callback_2, LV_EVENT_CLICKED, NULL);

    lv_obj_t* label = lv_label_create(speed_stop);
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
    lv_label_set_text(label, "Stop");
    lv_obj_set_align(label, LV_ALIGN_CENTER);
}

/****************************************************************************/
/*                        FUNCTION  REALIZATION                             */
/****************************************************************************/
void switch_show_demo()
{
    switch_ = lv_switch_create(lv_scr_act());
    lv_obj_set_style_bg_color(switch_, lv_color_hex(0xdf5345), LV_STATE_CHECKED | LV_PART_INDICATOR);
    lv_obj_add_state(switch_, LV_STATE_CHECKED);
    //lv_obj_clear_state(switch_, LV_STATE_CHECKED | LV_STATE_DISABLED);
    lv_obj_add_event(switch_, event_callback_3, LV_EVENT_VALUE_CHANGED, NULL);
}
void label_show_aircondition()
{
    if (scr_act_width() <= 320)
        font = &lv_font_montserrat_10;
    else if (scr_act_width() <= 480)
        font = &lv_font_montserrat_14;
    else
        font = &lv_font_montserrat_20;

    lv_obj_t* label_aircondition = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(label_aircondition, font, LV_PART_MAIN);
    lv_label_set_text(label_aircondition, "Air Condition Control System");
    lv_obj_align(label_aircondition, LV_ALIGN_CENTER, 0, -scr_act_height() / 3);
}
void switch_show_1()
{
    lv_obj_t* obj_cool = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj_cool, scr_act_height() / 3, scr_act_height() / 3);
    lv_obj_align(obj_cool, LV_ALIGN_CENTER, -scr_act_width() / 4, 0);

    lv_obj_t* label_cool = lv_label_create(obj_cool);
    lv_label_set_text(label_cool, "Cool");
    lv_obj_set_style_text_font(label_cool, font, LV_STATE_DEFAULT);
    lv_obj_align(label_cool, LV_ALIGN_CENTER, 0, -scr_act_height() / 16);

    switch_cool = lv_switch_create(obj_cool);
    lv_obj_set_size(switch_cool, scr_act_height() / 6, scr_act_height() / 12);
    lv_obj_align(switch_cool, LV_ALIGN_CENTER, 0, scr_act_height() / 16);
    lv_obj_add_event(switch_cool, event_callback_4, LV_EVENT_VALUE_CHANGED, NULL);
}
void switch_show_2()
{
    lv_obj_t* obj_heat = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj_heat, scr_act_height() / 3, scr_act_height() / 3);
    lv_obj_align(obj_heat, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* label_heat = lv_label_create(obj_heat);
    lv_label_set_text(label_heat, "Heat");
    lv_obj_set_style_text_font(label_heat, font, LV_STATE_DEFAULT);
    lv_obj_align(label_heat, LV_ALIGN_CENTER, 0, -scr_act_height() / 16);

    switch_heat = lv_switch_create(obj_heat);
    lv_obj_set_size(switch_heat, scr_act_height() / 6, scr_act_height() / 12);
    lv_obj_align(switch_heat, LV_ALIGN_CENTER, 0, scr_act_height() / 16);
    lv_obj_add_event(switch_heat, event_callback_4, LV_EVENT_VALUE_CHANGED, NULL);
}
void switch_show_3()
{
    lv_obj_t* obj_dry = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj_dry, scr_act_height() / 3, scr_act_height() / 3);
    lv_obj_align(obj_dry, LV_ALIGN_CENTER, scr_act_width() / 4, 0);

    lv_obj_t* label_dry = lv_label_create(obj_dry);
    lv_label_set_text(label_dry, "Dry");
    lv_obj_set_style_text_font(label_dry, font, LV_STATE_DEFAULT);
    lv_obj_align(label_dry, LV_ALIGN_CENTER, 0, -scr_act_height() / 16);

    switch_heat = lv_switch_create(obj_dry);
    lv_obj_set_size(switch_heat, scr_act_height() / 6, scr_act_height() / 12);
    lv_obj_align(switch_heat, LV_ALIGN_CENTER, 0, scr_act_height() / 16);
    lv_obj_add_event(switch_heat, event_callback_4, LV_EVENT_VALUE_CHANGED, NULL);
}

/****************************************************************************/
/*                        FUNCTION  REALIZATION                             */
/****************************************************************************/
void checkbox_show_demo()
{
    checkbox = lv_checkbox_create(lv_scr_act());
    lv_obj_set_align(checkbox, LV_ALIGN_CENTER);
    lv_checkbox_set_text(checkbox, "remember the password");
    lv_obj_set_style_pad_column(checkbox, 50, LV_STATE_DEFAULT);
    lv_obj_add_event(checkbox, event_callback_5, LV_EVENT_VALUE_CHANGED, NULL);
}
void checkbox_show_food()
{
    lv_obj_t* obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj, scr_act_width() * 4 / 5, scr_act_height() * 3 / 5);
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);

    checkbox_1 = lv_checkbox_create(obj);
    lv_checkbox_set_text(checkbox_1, "Roast chicken $19");
    lv_obj_set_style_text_font(checkbox_1, font, LV_STATE_DEFAULT);
    lv_obj_add_event(checkbox_1, event_callback_6, LV_EVENT_VALUE_CHANGED, NULL);

    checkbox_2 = lv_checkbox_create(obj);
    lv_checkbox_set_text(checkbox_2, "Roast duck    $29");
    lv_obj_set_style_text_font(checkbox_2, font, LV_STATE_DEFAULT);
    lv_obj_align_to(checkbox_2, checkbox_1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, scr_act_height() / 16);
    lv_obj_add_event(checkbox_2, event_callback_6, LV_EVENT_VALUE_CHANGED, NULL);

    checkbox_3 = lv_checkbox_create(obj);
    lv_checkbox_set_text(checkbox_3, "Roast fish    $29");
    lv_obj_set_style_text_font(checkbox_3, font, LV_STATE_DEFAULT);
    lv_obj_align_to(checkbox_3, checkbox_2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, scr_act_height() / 16);
    lv_obj_add_state(checkbox_3, LV_STATE_DISABLED);

    checkbox_4 = lv_checkbox_create(obj);
    lv_checkbox_set_text(checkbox_4, "Roast lamb    $69");
    lv_obj_set_style_text_font(checkbox_1, font, LV_STATE_DEFAULT);
    lv_obj_align_to(checkbox_4, checkbox_3, LV_ALIGN_OUT_BOTTOM_LEFT, 0, scr_act_height() / 16);
    lv_obj_add_state(checkbox_4, LV_STATE_DISABLED);
}

/****************************************************************************/
/*                        FUNCTION  REALIZATION                             */
/****************************************************************************/
void bar_show_demo()
{
    lv_obj_t* bar = lv_bar_create(lv_scr_act());
    lv_obj_set_align(bar, LV_ALIGN_CENTER);
    lv_obj_set_size(bar, 400, 20);
    lv_bar_set_range(bar, -100, 100);
    //lv_bar_set_value(bar, -100, LV_ANIM_ON);
    lv_obj_set_style_anim_time(bar, 1000, LV_STATE_DEFAULT);
    lv_bar_set_value(bar, 100, LV_ANIM_ON);

    lv_bar_set_mode(bar, LV_BAR_MODE_RANGE);
    lv_bar_set_start_value(bar, -50, LV_ANIM_OFF);
}
void bar_show_loading()
{
    label_load = lv_label_create(lv_scr_act());
    lv_label_set_text(label_load, "LOADING");
    lv_obj_set_style_text_font(label_load, font, LV_STATE_DEFAULT);
    lv_obj_align(label_load, LV_ALIGN_CENTER, 0, -scr_act_height() / 10);

    label_per = lv_label_create(lv_scr_act());
    lv_label_set_text(label_per, "0%");
    lv_obj_set_style_text_font(label_per, font, LV_STATE_DEFAULT);
    lv_obj_align(label_per, LV_ALIGN_CENTER, 0, scr_act_height() / 10);

    bar = lv_bar_create(lv_scr_act());
    lv_obj_set_align(bar, LV_ALIGN_CENTER);
    lv_obj_set_size(bar, scr_act_width() * 3 / 5, 20);
    lv_obj_set_style_anim_time(bar, 100, LV_STATE_DEFAULT);
    lv_timer_create(timer_callback_1, 50, NULL);
}


/****************************************************************************/
/*                        FUNCTION  REALIZATION                             */
/****************************************************************************/
void spinner_show()
{
    spinner = lv_spinner_create(lv_scr_act());
    lv_obj_align(spinner, LV_ALIGN_CENTER, 0, -scr_act_height() / 15);
    lv_obj_set_size(spinner, scr_act_height() / 5, scr_act_height() / 5);
    lv_spinner_set_anim_params(spinner, 2000, 180);
    lv_obj_set_style_arc_color(spinner, lv_color_hex(0xE6E7E8), LV_PART_MAIN);
    lv_obj_set_style_arc_color(spinner, lv_color_hex(0x006CBE), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(spinner, scr_act_height() / 35, LV_PART_MAIN);
    lv_obj_set_style_arc_width(spinner, scr_act_height() / 35, LV_PART_INDICATOR);
}

/****************************************************************************/
/*                        FUNCTION  REALIZATION                             */
/****************************************************************************/
void led_show_demo()
{
    lv_obj_t* led = lv_led_create(lv_scr_act());
    lv_obj_set_size(led, 100, 100);
    lv_obj_center(led);
    lv_led_set_color(led, lv_color_hex(0x00ff00));
    lv_led_set_brightness(led, 255);
    lv_led_off(led);
    //lv_led_on(led);
    lv_led_toggle(led);
}
void led_show_room()
{
    lv_obj_t* obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj, scr_act_width() * 5 / 6, scr_act_height() * 3 / 5);
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xefefef), LV_STATE_DEFAULT);

    led_1 = lv_led_create(obj);
    lv_obj_set_size(led_1, scr_act_height() / 10, scr_act_height() / 10);
    lv_obj_align(led_1, LV_ALIGN_CENTER, -scr_act_width() / 6, -scr_act_height() / 15);
    lv_led_set_color(led_1, lv_color_hex(0xff0000));
    lv_led_off(led_1);
    lv_obj_add_event(led_1, event_callback_7, LV_EVENT_CLICKED, NULL);

    lv_obj_t* label_1 = lv_label_create(lv_scr_act());
    lv_label_set_text(label_1, "ROOM 1");
    lv_obj_set_style_text_font(label_1, font, LV_STATE_DEFAULT);
    lv_obj_align_to(label_1, led_1, LV_ALIGN_OUT_BOTTOM_MID, 0, scr_act_height() / 15);

    led_2 = lv_led_create(obj);
    lv_obj_set_size(led_2, scr_act_height() / 10, scr_act_height() / 10);
    lv_obj_align(led_2, LV_ALIGN_CENTER, scr_act_width() / 6, -scr_act_height() / 15);
    lv_led_set_color(led_2, lv_color_hex(0x0000ff));
    lv_led_off(led_2);
    lv_obj_add_event(led_2, event_callback_7, LV_EVENT_CLICKED, NULL);

    lv_obj_t* label_2 = lv_label_create(lv_scr_act());
    lv_label_set_text(label_2, "ROOM 2");
    lv_obj_set_style_text_font(label_2, font, LV_STATE_DEFAULT);
    lv_obj_align_to(label_2, led_2, LV_ALIGN_OUT_BOTTOM_MID, 0, scr_act_height() / 15);
}

/****************************************************************************/
/*                        FUNCTION  REALIZATION                             */
/****************************************************************************/

