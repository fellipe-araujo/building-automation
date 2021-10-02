#include "main.h"

int main () {
  gpio_setup();
  quit_setup();
  dht22_setup();

  disable_output_devices();

  pthread_t tid[3];

  pthread_create(&tid[0], NULL, (void *)gpio_handler, (void *)NULL);
  pthread_create(&tid[1], NULL, (void *)server_handler, (void*)0);
  pthread_create(&tid[2], NULL, (void *)server_handler, (void*)1);

  pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);

  return 0;
}
