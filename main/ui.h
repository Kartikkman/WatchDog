#ifndef __UI_H_
#define __UI_H_

#include <stdint.h>
#include <stdio.h>
#include"driver/gpio.h"
#include"string.h"
#include"SSD.h"
#include"touch.h"

enum Touch_State {SELECT , RIGHT_SLIDE , LEFT_SLIDE};
enum STATUS{TIME , MENU,LED_GUI,ALERT_GUI};

extern int status;


int alert_gui(int touch);
int led_gui(int touch);
int sub_menu(int touch);
int time_display(int touch);

extern int (*func_ptr[])(int touch) ;





#endif