#ifndef GPIO_H
#define GPIO_H

#include <wiringPi.h>

// Ground Floor
#define LS_T01 4
#define LS_T02 17
#define LC_T 27
#define AC_T 7
#define SP_T 26
#define SF_T 23
#define SJ_T01 9
#define SJ_T02 11
#define SPo_T 10
#define SC_IN 13
#define SC_OUT 19
#define ASP 16

// First Floor
#define LS_101 22
#define LS_102 25
#define LC_1 8
#define AC_1 12
#define SP_1 18
#define SF_1 24
#define SJ_101 5
#define SJ_102 4

void gpio_setup();
int device_exist(int device);
void gpio_handler(int floor);
void change_device_state(int device, int state);
void disable_output_devices();

#endif
