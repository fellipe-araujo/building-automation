#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void finish(int signal) {
  printf("Finzalização completa . . .\n");
  exit(0);
}

void finishWithError(int signal) {
  printf("Erro no socket. . .\n");
  finish(0);
}

void quit_setup() {
  signal(SIGINT, finish);
  signal(SIGPIPE, finishWithError);
}

void quit_handler(char *message) {
  refresh();
  endwin();

  int len = strlen(message);

  if (len > 0) {
    printf("%s\n", message);
  }

  exit(0);
}
