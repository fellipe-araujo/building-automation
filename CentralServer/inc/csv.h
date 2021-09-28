#ifndef CSV_H_
#define CSV_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  char* device;
  int state;
} Command;

void csv_setup();
void write_data(Command command);

#endif
