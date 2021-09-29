#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "data.h"
#include "socket_quit.h"

void print_menu(WINDOW *window, int highlight);
void clear_menu(WINDOW *window_param);
void print_data(Data data);
void print_devices_in(DevicesIn dev_in);
void* menu_handler();

#endif
