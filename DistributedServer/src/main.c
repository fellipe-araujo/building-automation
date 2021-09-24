#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dht22.h"

int main () {
  float temperature = -1;
  float humidity  = -1;

  setup_dht22();

  while (1) {
    read_dht22_data(&temperature, &humidity);
    sleep(1);
  }

  return 0;
}
