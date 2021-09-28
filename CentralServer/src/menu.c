#include "menu.h"
#include "data.h"

#define WIDTH 94
#define HEIGHT 28

WINDOW *window;

char *choices[] = {
	"Térreo - Lâmpada da Sala 01:",
	"Térreo - Lâmpada da Sala 02:",
	"Térreo - Lâmpadas do Corredor:",
	"Térreo - Ar-Condicionado:",
	"Térreo - Aspersores de Agua:",
  "Primeiro Andar - Lâmpada da Sala 101:",
  "Primeiro Andar - Lâmpada da Sala 102:",
  "Primeiro Andar - Lâmpadas do Corredor:",
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

  mvwprintw(window, 19, 2, "Temperatura - Térreo: ");
  wattron(window, COLOR_PAIR(1));
  mvwprintw(window, 19, 25, "%4.2f", data.dht22.ground_floor_temperature);
	wattroff(window, COLOR_PAIR(1));
  mvwprintw(window, 20, 2, "Umidade     - Térreo: ");
	wattron(window, COLOR_PAIR(1));
  mvwprintw(window, 20, 25, "%4.2f", data.dht22.ground_floor_humidity);
	wattroff(window, COLOR_PAIR(1));

  mvwprintw(window, 19, 40, "Temperatura - Primeiro Andar: ");
  wattron(window, COLOR_PAIR(1));
  mvwprintw(window, 19, 70, "%4.2f", data.dht22.first_floor_temperature);
	wattroff(window, COLOR_PAIR(1));
  mvwprintw(window, 20, 40, "Umidade     - Primeiro Andar: ");
	wattron(window, COLOR_PAIR(1));
  mvwprintw(window, 20, 70, "%4.2f", data.dht22.first_floor_humidity);
	wattroff(window, COLOR_PAIR(1));

	mvwprintw(window, 25, 2, "Alarme Tocando: ");
  wattron(window, COLOR_PAIR(data.dev_out.alarm_playing == 1 ? 3 : 2));
	mvwprintw(window, 25, 18, "%s", data.dev_out.alarm_playing == 1 ? "SIM" : "NAO");
	wattroff(window, COLOR_PAIR(data.dev_out.alarm_playing == 1 ? 3 : 2));

	mvwprintw(window, 25, 50, "Pessoas: ");
  wattron(window, COLOR_PAIR(1));
	mvwprintw(window, 25, 59, "%s", "0");
	wattroff(window, COLOR_PAIR(1));

  wrefresh(window);
}
