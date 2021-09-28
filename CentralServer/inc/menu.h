#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "data.h"

void print_menu(WINDOW *window, int highlight);
void clear_menu(WINDOW *window_param);
void print_data(Data data);

#endif
