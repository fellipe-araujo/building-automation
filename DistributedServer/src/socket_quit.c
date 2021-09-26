#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "gpio.h"
#include "server_tcp.h"
#include "data.h"

void finish(int signal) {
  close_server_socket();
  disable_output_devices();
  printf("Finzalização completa . . .\n");
  exit(0);
}

void finishWithError(int signal) {
  printf("Erro no socket. . .\n");
  finish(0);
}

void quit_handler() {
  signal(SIGINT, finish);
  signal(SIGPIPE, finishWithError);
}
