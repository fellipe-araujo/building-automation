#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "app.h"
#include "socket_quit.h"
#include "menu.h"
#include "data.h"
#include "server_tcp.h"
#include "csv.h"

int main() {
  quit_setup();
  csv_setup();
  app_init();

  pthread_t tid[3];

  pthread_create(&tid[0], NULL, (void *)app_handler, (void *)NULL);
  pthread_create(&tid[1], NULL, (void *)menu_handler, (void *)NULL);
  pthread_create(&tid[2], NULL, (void *)recv_message, (void *)NULL);

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  pthread_join(tid[2], NULL);

  return 0;
}
