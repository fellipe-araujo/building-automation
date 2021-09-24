#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dht22.h"

int main () {
  float temperature = -1;
  float humidity  = -1;

  dht22_setup();

  while (1) {
    dht22_read_data(&temperature, &humidity);
    sleep(1);
  }

  return 0;
}
