#include "main.h"

void server_ground_floor() {
  server_handler(0);
}

void server_first_floor() {
  server_handler(1);
}

int main () {
  gpio_setup();
  quit_setup();
  dht22_setup();

  disable_output_devices();

  pthread_t tid[3];

  pthread_create(&tid[0], NULL, (void *)gpio_handler, (void *)NULL);
  pthread_create(&tid[1], NULL, (void *)server_ground_floor, (void *)NULL);
  pthread_create(&tid[2], NULL, (void *)server_first_floor, (void *)NULL);

  pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);

  return 0;
}
