#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "gpio.h"
#include "socket_tcp.h"

void finish(int signal) {
  disable_output_devices();
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
