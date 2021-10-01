#ifndef DATA_H_
#define DATA_H_

#define LS_T01 7
#define LS_T02 0
#define LC_T 2
#define AC_T 11

#define LS_T01 4
#define LS_T02 17
#define LC_T 27
#define AC_T 7
#define ASP 16
#define LS_101 22
#define LS_102 25
#define LC_1 8
#define AC_1 12

#define SP_T 26
#define SF_T 23
#define SJ_T01 9
#define SJ_T02 11
#define SPo_T 10
#define SC_IN 13
#define SC_OUT 19
#define SP_1 18
#define SF_1 24
#define SJ_101 5
#define SJ_102 4

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
void store_devices_out_update(DevicesOut dev_out);
DevicesOut recover_devices_out_data();

#endif
