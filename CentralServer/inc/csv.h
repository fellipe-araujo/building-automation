#ifndef CSV_H_
#define CSV_H_

typedef struct {
  char* device;
  int state;
} Command;

void csv_setup();
void write_data(Command command);

#endif
