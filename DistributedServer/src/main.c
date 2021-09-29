#include "main.h"

void ground_floor() {
  gpio_handler(0);
  server_handler(0);
}

void first_floor() {
  gpio_handler(1);
  server_handler(1);
}

int main () {
  gpio_setup();
  quit_setup();
  dht22_setup();

  pthread_t tid[2];

  pthread_create(&tid[0], NULL, (void *)ground_floor, (void *)NULL);
  pthread_create(&tid[1], NULL, (void *)first_floor, (void *)NULL);

  pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

  return 0;
}
