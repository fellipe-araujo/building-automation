#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "menu.h"
#include "data.h"
#include "csv.h"
#include "socket_quit.h"

#define WIDTH 94
#define HEIGHT 28

WINDOW *window;

char *choices[] = {
	"Terreo - Lampada da Sala 01:",
	"Terreo - Lampada da Sala 02:",
	"Terreo - Lampadas do Corredor:",
	"Terreo - Ar-Condicionado:",
	"Terreo - Aspersores de Agua:",
  "Primeiro Andar - Lampada da Sala 101:",
  "Primeiro Andar - Lampada da Sala 102:",
  "Primeiro Andar - Lampadas do Corredor:",
  "Primeiro Andar - Ar-Condicionado:",
  "Ativar o Alarme:",
  "Sair",
};

int startx = 0;
int starty = 0;
int n_choices = sizeof(choices) / sizeof(char *);

void print_menu(WINDOW *window, int highlight) {
	int x = 2, y = 4, i;
	box(window, 0, 0);

	for(i = 0; i < n_choices; i++) {
		if (i == n_choices - 1) {
			wattron(window, COLOR_PAIR(2));
		}

		if (highlight == i + 1) {
			wattron(window, A_REVERSE);
			mvwprintw(window, y, x, "%s", choices[i]);
			wattroff(window, A_REVERSE);
		} else {
			mvwprintw(window, y, x, "%s", choices[i]);
		}

		if (i == n_choices - 1) {
			wattroff(window, COLOR_PAIR(2));
		}

		++y;
	}

	wrefresh(window);
}

void clear_menu(WINDOW *window_param) {
	wclear(window_param);
	wborder(window_param, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');  
	wrefresh(window_param);
	delwin(window_param); 
}

void print_data(Data data) {
  wattron(window, COLOR_PAIR(data.dev_out.ls_t01 == 1 ? 3 : 2));
	mvwprintw(window, 4, 41, data.dev_out.ls_t01 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.dev_out.ls_t01 == 1 ? 3 : 2));

  wattron(window, COLOR_PAIR(data.dev_out.ls_t02 == 1 ? 3 : 2));
	mvwprintw(window, 5, 41, data.dev_out.ls_t02 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.dev_out.ls_t02 == 1 ? 3 : 2));

  wattron(window, COLOR_PAIR(data.dev_out.lc_t == 1 ? 3 : 2));
	mvwprintw(window, 6, 41, data.dev_out.lc_t == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.dev_out.lc_t == 1 ? 3 : 2));

  wattron(window, COLOR_PAIR(data.dev_out.ac_t == 1 ? 3 : 2));
	mvwprintw(window, 7, 41, data.dev_out.ac_t == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.dev_out.ac_t == 1 ? 3 : 2));

  wattron(window, COLOR_PAIR(data.dev_out.asp == 1 ? 3 : 2));
	mvwprintw(window, 8, 41, data.dev_out.asp == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.dev_out.asp == 1 ? 3 : 2));

  wattron(window, COLOR_PAIR(data.dev_out.ls_101 == 1 ? 3 : 2));
	mvwprintw(window, 9, 41, data.dev_out.ls_101 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.dev_out.ls_101 == 1 ? 3 : 2));

  wattron(window, COLOR_PAIR(data.dev_out.ls_102 == 1 ? 3 : 2));
	mvwprintw(window, 10, 41, data.dev_out.ls_102 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.dev_out.ls_102 == 1 ? 3 : 2));

  wattron(window, COLOR_PAIR(data.dev_out.lc_1 == 1 ? 3 : 2));
	mvwprintw(window, 11, 41, data.dev_out.lc_1 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.dev_out.lc_1 == 1 ? 3 : 2));

  wattron(window, COLOR_PAIR(data.dev_out.ac_1 == 1 ? 3 : 2));
	mvwprintw(window, 12, 41, data.dev_out.ac_1 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.dev_out.ac_1 == 1 ? 3 : 2));

  wattron(window, COLOR_PAIR(data.dev_out.alarm == 1 ? 3 : 2));
	mvwprintw(window, 13, 41, data.dev_out.alarm == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.dev_out.alarm == 1 ? 3 : 2));

  mvwprintw(window, 19, 2, "Temperatura - Terreo: ");
  wattron(window, COLOR_PAIR(1));
  mvwprintw(window, 19, 25, "%4.2f", data.dht22_ground_floor.temperature);
	wattroff(window, COLOR_PAIR(1));
  mvwprintw(window, 20, 2, "Umidade     - Terreo: ");
	wattron(window, COLOR_PAIR(1));
  mvwprintw(window, 20, 25, "%4.2f", data.dht22_ground_floor.humidity);
	wattroff(window, COLOR_PAIR(1));

  mvwprintw(window, 19, 40, "Temperatura - Primeiro Andar: ");
  wattron(window, COLOR_PAIR(1));
  mvwprintw(window, 19, 70, "%4.2f", data.dht22_first_floor.temperature);
	wattroff(window, COLOR_PAIR(1));
  mvwprintw(window, 20, 40, "Umidade     - Primeiro Andar: ");
	wattron(window, COLOR_PAIR(1));
  mvwprintw(window, 20, 70, "%4.2f", data.dht22_first_floor.humidity);
	wattroff(window, COLOR_PAIR(1));

	mvwprintw(window, 25, 2, "Alarme Tocando: ");
  wattron(window, COLOR_PAIR(data.dev_out.alarm_playing == 1 ? 3 : 2));
	mvwprintw(window, 25, 18, data.dev_out.alarm_playing == 1 ? "SIM" : "NAO");
	wattroff(window, COLOR_PAIR(data.dev_out.alarm_playing == 1 ? 3 : 2));

  wrefresh(window);
}

void print_devices_in(DevicesIn dev_in) {
  mvwprintw(window, 4, 50, "Terreo - Sensor de Presenca:");
	wattron(window, COLOR_PAIR(dev_in.sp_t == 1 ? 3 : 2));
	mvwprintw(window, 4, 89, dev_in.sp_t == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(dev_in.sp_t == 1 ? 3 : 2));

  mvwprintw(window, 5, 50, "Terreo - Sensor de Fumaca:");
	wattron(window, COLOR_PAIR(dev_in.sf_t == 1 ? 3 : 2));
	mvwprintw(window, 5, 89, dev_in.sf_t == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(dev_in.sf_t == 1 ? 3 : 2));

  mvwprintw(window, 6, 50, "Terreo - Sensor de Janela 01:");
	wattron(window, COLOR_PAIR(dev_in.sj_t01 == 1 ? 3 : 2));
	mvwprintw(window, 6, 89, dev_in.sj_t01 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(dev_in.sj_t01 == 1 ? 3 : 2));

  mvwprintw(window, 7, 50, "Terreo - Sensor de Janela 02:");
	wattron(window, COLOR_PAIR(dev_in.sj_t02 == 1 ? 3 : 2));
	mvwprintw(window, 7, 89, dev_in.sj_t02 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(dev_in.sj_t02 == 1 ? 3 : 2));

  mvwprintw(window, 8, 50, "Terreo - Sensor de Porta:");
	wattron(window, COLOR_PAIR(dev_in.spo_T == 1 ? 3 : 2));
	mvwprintw(window, 8, 89, dev_in.spo_T == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(dev_in.spo_T == 1 ? 3 : 2));

  mvwprintw(window, 9, 50, "Primeiro Andar - Sensor de Presenca:");
	wattron(window, COLOR_PAIR(dev_in.sp_1 == 1 ? 3 : 2));
	mvwprintw(window, 9, 89, dev_in.sp_1 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(dev_in.sp_1 == 1 ? 3 : 2));

  mvwprintw(window, 10, 50, "Primeiro Andar - Sensor de Fumaca:");
	wattron(window, COLOR_PAIR(dev_in.sf_1 == 1 ? 3 : 2));
	mvwprintw(window, 10, 89, dev_in.sf_1 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(dev_in.sf_1 == 1 ? 3 : 2));

  mvwprintw(window, 11, 50, "Primeiro Andar - Sensor de Janela 101:");
	wattron(window, COLOR_PAIR(dev_in.sj_101 == 1 ? 3 : 2));
	mvwprintw(window, 11, 89, dev_in.sj_101 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(dev_in.sj_101 == 1 ? 3 : 2));

  mvwprintw(window, 12, 50, "Primeiro Andar - Sensor de Janela 102:");
	wattron(window, COLOR_PAIR(dev_in.sj_102 == 1 ? 3 : 2));
	mvwprintw(window, 12, 89, dev_in.sj_102 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(dev_in.sj_102 == 1 ? 3 : 2));

	mvwprintw(window, 25, 50, "Pessoas: ");
  wattron(window, COLOR_PAIR(1));
	mvwprintw(window, 25, 59, dev_in.people_counter >= 10 ? "%d" : "0%d", dev_in.people_counter);
	wattroff(window, COLOR_PAIR(1));

  wrefresh(window);
}

void print_header() {
	wattron(window, COLOR_PAIR(4));
	mvwprintw(window, 2, 15, "DISPOSITIVOS DE SAIDA");
	wattroff(window, COLOR_PAIR(4));

	wattron(window, COLOR_PAIR(4));
	mvwprintw(window, 2, 61, "DISPOSITIVOS DE ENTRADA");
	wattroff(window, COLOR_PAIR(4));

	wattron(window, COLOR_PAIR(4));
	mvwprintw(window, 17, 37, "TEMPERATURA E UMIDADE");
	wattroff(window, COLOR_PAIR(4));

	wattron(window, COLOR_PAIR(4));
	mvwprintw(window, 23, 13, "ALARME");
	wattroff(window, COLOR_PAIR(4));

	wattron(window, COLOR_PAIR(4));
	mvwprintw(window, 23, 57, "QUANTIDADE DE PESSOAS");
	wattroff(window, COLOR_PAIR(4));
}

void* menu_handler() {
	int highlight = 1;
	int choice = 0;
	int c;

	initscr();
	start_color(); 
	clear();
	noecho();
	cbreak();
	curs_set(0);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
     
	window = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(window, TRUE);
	refresh();

	data_init();

	do {
		print_header();
		print_menu(window, highlight);
		c = wgetch(window);

		switch(c) {
			case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:    
				choice = highlight;

				DevicesOut dev_out = recover_devices_out_data();

				if (choice == 1) {
					dev_out.ls_t01 = dev_out.ls_t01 == 1 ? 0 : 1;
					char *device = "T??rreo - L??mpada da Sala 01";
					Command command;
					command.device = device;
					command.state = dev_out.ls_t01;
					write_data(command);
				}

				else if (choice == 2) {
					dev_out.ls_t02 = dev_out.ls_t02 == 1 ? 0 : 1;
					char *device = "T??rreo - L??mpada da Sala 02";
					Command command;
					command.device = device;
					command.state = dev_out.ls_t02;
					write_data(command);
				}

				else if (choice == 3) {
					dev_out.lc_t = dev_out.lc_t == 1 ? 0 : 1;
					char *device = "T??rreo - L??mpadas do Corredor";
					Command command;
					command.device = device;
					command.state = dev_out.lc_t;
					write_data(command);
				}

				else if (choice == 4) {
					dev_out.ac_t = dev_out.ac_t == 1 ? 0 : 1;
					char *device = "T??rreo - Ar-Condicionado";
					Command command;
					command.device = device;
					command.state = dev_out.ac_t;
					write_data(command);
				}

				else if (choice == 5) {
					dev_out.asp = dev_out.asp == 1 ? 0 : 1;
					char *device = "T??rreo - Aspersores de Agua";
					Command command;
					command.device = device;
					command.state = dev_out.asp;
					write_data(command);
				}

				else if (choice == 6) {
					dev_out.ls_101 = dev_out.ls_101 == 1 ? 0 : 1;
					char *device = "Primeiro Andar - L??mpada da Sala 101";
					Command command;
					command.device = device;
					command.state = dev_out.ls_101;
					write_data(command);
				}

				else if (choice == 7) {
					dev_out.ls_102 = dev_out.ls_102 == 1 ? 0 : 1;
					char *device = "Primeiro Andar - L??mpada da Sala 102";
					Command command;
					command.device = device;
					command.state = dev_out.ls_102;
					write_data(command);
				}

				else if (choice == 8) {
					dev_out.lc_1 = dev_out.lc_1 == 1 ? 0 : 1;
					char *device = "Primeiro Andar - L??mpadas do Corredor";
					Command command;
					command.device = device;
					command.state = dev_out.lc_1;
					write_data(command);
				}

				else if (choice == 9) {
					dev_out.ac_1 = dev_out.ac_1 == 1 ? 0 : 1;
					char *device = "Primeiro Andar - Ar-Condicionado";
					Command command;
					command.device = device;
					command.state = dev_out.ac_1;
					write_data(command);
				}

				else if (choice == 10) {
					dev_out.alarm = dev_out.alarm == 1 ? 0 : 1;
					char *device = "Ativar o Alarme";
					Command command;
					command.device = device;
					command.state = dev_out.alarm;
					write_data(command);
				}

				store_devices_out_update(dev_out);

				if (choice == 11) {
					char *message = "Finalizando. . .";
					quit_handler(message);
				}

				break;

			default:
				refresh();
				break;
		}
	} while(1);

	return NULL;
}
