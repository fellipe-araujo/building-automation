#ifndef DATA_H_
#define DATA_H_

#define LS_T01 7
#define LS_T02 0
#define LC_T 2
#define AC_T 11
#define ASP 27
#define LS_101 3
#define LS_102 6
#define LC_1 10
#define AC_1 26

#define SP_T 25
#define SF_T 4
#define SJ_T01 13
#define SJ_T02 14
#define SPo_T 12
#define SC_IN 23
#define SC_OUT 24
#define SP_1 1
#define SF_1 5
#define SJ_101 21
#define SJ_102 22

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
  DHT22 dht22_ground_floor;
  DHT22 dht22_first_floor;
  DevicesOut dev_out;
} Data;

void data_init();
void devices_in_handler(int command);
void store_devices_out_update(DevicesOut dev_out_updated);
DevicesOut recover_devices_out_data();

#endif
