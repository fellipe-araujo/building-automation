#include "menu.h"

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
