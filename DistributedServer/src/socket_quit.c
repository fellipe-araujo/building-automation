#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "gpio.h"

void quit_handler() {
  disable_output_devices();
  exit(1);
}

void quit_setup() {
  signal(SIGINT, quit_handler);
}
