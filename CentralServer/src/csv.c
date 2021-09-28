#include "csv.h"

#define BUF_LEN 256

char buffer[BUF_LEN];

void time_generate() {
  time_t current_time;
  struct tm* time_info;

  time(&current_time);
  time_info = localtime(&current_time);

  strftime(buffer, BUF_LEN, "%c", time_info);
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
  FILE *file = fopen("data.csv", "a");
  char *state = command.state == 1 ? "ON" : "OFF";

  fprintf(
    file,
    "%s,%s,%s\r\n",
    buffer,
    command.device,
    state
  );

  fclose(file);
}
