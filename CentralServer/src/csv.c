#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "csv.h"

#define BUF_LEN 256

char buffer[BUF_LEN];

void time_generate() {
  time_t current_time;
  struct tm* time_info;

  time(&current_time);
  time_info = localtime(&current_time);

  strftime(buffer, BUF_LEN, "%Y-%m-%d %H:%M:%S", time_info);
}

void csv_setup() {
  FILE *file = fopen("logs/data.csv", "w");
  fprintf(file, "DATETIME, DEVICE, STATE\n");
  fclose(file);
}

void write_data(Command command) {
  // Update Datetime
  time_generate();

  // Write file
  FILE *file = fopen("logs/data.csv", "a");
  char *state = command.state == 1 ? "ON" : "OFF";

  fprintf(
    file,
    "%s,%s,%s\n",
    buffer,
    command.device,
    state
  );

  fclose(file);
}
