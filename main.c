#ifndef ENABLE_TOUCH
    #define ENABLE_TOUCH 1
#endif

#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"

#if ENABLE_TOUCH
    #include "lv_drivers/indev/evdev.h"
#endif

#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

#define DISP_BUF_SIZE (128 * 1024)

void lv_button_demo(void);
char txt[100];

int main(void)
{
    /*LittlevGL init*/
    lv_init();

    /*Linux frame buffer device init*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = 480;
    disp_drv.ver_res    = 640;
    lv_disp_drv_register(&disp_drv);

    /*Initialize and register a input driver*/
#if ENABLE_TOUCH    
    evdev_init();
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);          
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = evdev_read;         
    //indev_drv.read_cb = libinput_read;
    lv_indev_drv_register(&indev_drv);
#endif

        sprintf(txt, "WT32-SC01 with LVGL v%d.%d.%d", lv_version_major(), lv_version_minor(), lv_version_patch());
        lv_obj_t *label = lv_label_create(lv_scr_act()); // full screen as the parent
        lv_label_set_text(label, txt);                   // set label text
        lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);    // Center but 20 from the top

        lv_button_demo(); // lvl buttons

    /*Handle LitlevGL tasks (tickless mode)*/
    while(1) {
        lv_task_handler();
        usleep(5000);
    }

    return 0;
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}


/* Counter button event handler */
static void counter_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED)
    {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t *label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "Button: %d", cnt);
        LV_LOG_USER("Clicked");

    }
}

/* Toggle button event handler */
static void toggle_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        LV_LOG_USER("Toggled");

    }
}

/* Button with counter & Toggle Button */
void lv_button_demo(void)
{
    lv_obj_t *label;

    // Button with counter
    lv_obj_t *btn1 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn1, counter_event_handler, LV_EVENT_ALL, NULL);

    lv_obj_set_pos(btn1, 100, 100); /*Set its position*/
    lv_obj_set_size(btn1, 120, 50); /*Set its size*/

    label = lv_label_create(btn1);
    lv_label_set_text(label, "Button");
    lv_obj_center(label);

    // Toggle button
    lv_obj_t *btn2 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn2, toggle_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_pos(btn2, 250, 100); /*Set its position*/
    lv_obj_set_size(btn2, 120, 50); /*Set its size*/

    label = lv_label_create(btn2);
    lv_label_set_text(label, "Toggle Button");
    lv_obj_center(label);
}
