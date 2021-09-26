#ifndef DATA_H_
#define DATA_H_

typedef struct {
  int LS_T01;
  int LS_T02;
  int LC_T;
  int AC_T;
  int SP_T;
  int SF_T;
  int SJ_T01;
  int SJ_T02;
  int SPo_T;
  int SC_IN;
  int SC_OUT;
  int ASP;
  int LS_101;
  int LS_102;
  int LC_1;
  int AC_1;
  int SP_1;
  int SF_1;
  int SJ_101;
  int SJ_102;
} Data;

void init_data();
Data set_data();
void get_data();

#endif
