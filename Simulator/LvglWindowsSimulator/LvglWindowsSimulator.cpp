/*
 * PROJECT:   LVGL Windows Simulator
 * FILE:      LvglWindowsSimulator.cpp
 * PURPOSE:   Implementation for LVGL Windows Simulator
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

 /****************************************************************************/
 /*                        INCLUDE & DEFINE                                  */
 /****************************************************************************/
#include <Windows.h>
#include <LvglWindowsIconResource.h>

#if _MSC_VER >= 1200
 // Disable compilation warnings.
#pragma warning(push)
// nonstandard extension used : bit field types other than int
#pragma warning(disable:4214)
// 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable:4244)
#endif

#include "myGUI.h"
#include "lvgl/lvgl.h"
#include "win32drv.h"

#if _MSC_VER >= 1200
// Restore compilation warnings.
#pragma warning(pop)
#endif

/****************************************************************************/
/*                        FUNCTION  DECLARITY                               */
/****************************************************************************/
bool single_display_mode_initialization();
uint32_t tick_count_callback();

/****************************************************************************/
/*                        FUNCTION  REALIZATION                             */
/****************************************************************************/
int main() {
    /***************************************/
    /*              INITIALIZE		       */
    /***************************************/
    lv_init();
    lv_tick_set_cb(tick_count_callback);
    if (!single_display_mode_initialization()) {
        return -1;
    }

    /***************************************/
    /*              MYGUI   DEMO           */
    /***************************************/
    //myGUI();

    //label_show_1();
    //label_show_2();
    //label_show_3();
    //label_show_4();
    //
    //label_show_speed();
    //button_speed_down();
    //button_speed_up();
    //button_speed_stop();
    //
    //label_show_aircondition();
    //switch_show_1();
    //switch_show_2();
    //switch_show_3();
    //
    //checkbox_show_food();
    //
    //bar_show_loading();
    //
    //spinner_show();
    //
    led_show_room();

    /***************************************/
    /*              WHILE                  */
    /***************************************/
    while (!lv_win32_quit_signal) {
        uint32_t time_till_next = lv_timer_handler();
        Sleep(time_till_next);
    }

    return 0;
}

/****************************************************************************/
/*                        FUNCTION  REALIZATION                             */
/****************************************************************************/
bool single_display_mode_initialization() {
    if (!lv_win32_init(
        GetModuleHandleW(NULL),
        SW_SHOW,
        800,
        480,
        LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDI_LVGL_WINDOWS)))) {
        return false;
    }
    lv_win32_add_all_input_devices_to_group(NULL);
    return true;
}

uint32_t tick_count_callback() {
    return GetTickCount64();
}
