#ifndef DATA_H_
#define DATA_H_

#include "app.h"
#include "alarm.h"
#include "socket_tcp.h"

typedef struct {
  int ls_t01;
  int ls_t02;
  int lc_t;
  int ac_t;
  int asp;
  int ls_101;
  int ls_102;
  int lc_1;
  int ac_1;
  int alarm;
  int alarm_playing;
} DevicesOut;

typedef struct {
  int sp_t;
  int sf_t;
  int sj_t01;
  int sj_t02;
  int spo_T;
  int sc_in;
  int sc_out;
  int sp_1;
  int sf_1;
  int sj_101;
  int sj_102;
} DevicesIn;

typedef struct {
  float temperature;
  float humidity;
} DHT22;

typedef struct {
  DHT22 dht22;
  DevicesOut dev_out;
} Data;

void data_init();
void devices_out_handler(int command);
DevicesOut recover_devices_in_data();

#endif
