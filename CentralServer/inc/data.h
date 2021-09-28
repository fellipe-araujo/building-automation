#ifndef DATA_H_
#define DATA_H_

#include "app.h"

typedef struct {
  int SP_T;
  int SF_T;
  int SJ_T01;
  int SJ_T02;
  int SPo_T;
  int SC_IN;
  int SC_OUT;
  int SP_1;
  int SF_1;
  int SJ_101;
  int SJ_102;
} DevicesIn;

typedef struct {
  int LS_T01;
  int LS_T02;
  int LC_T;
  int AC_T;
  int ASP;
  int LS_101;
  int LS_102;
  int LC_1;
  int AC_1;
} DevicesOut;

typedef struct {
  float temperature;
  float humidity;
} DHT22;

typedef struct {
  DHT22 dht22;
  DevicesOut dev_out;
} Data;

#endif
