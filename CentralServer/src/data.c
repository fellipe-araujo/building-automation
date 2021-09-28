#include "data.h"

#define LS_T01 4
#define LS_T02 17
#define LC_T 27
#define AC_T 7
#define ASP 16
#define LS_101 22
#define LS_102 25
#define LC_1 8
#define AC_1 12

DevicesIn _dev_in;
DevicesOut _dev_out;

void data_init() {
  _dev_in.sp_t = 0;
  _dev_in.sf_t = 0;
  _dev_in.sj_t01 = 0;
  _dev_in.sj_t02 = 0;
  _dev_in.spo_T = 0;
  _dev_in.sc_in = 0;
  _dev_in.sc_out = 0;
  _dev_in.sp_1 = 0;
  _dev_in.sf_1 = 0;
  _dev_in.sj_101 = 0;
  _dev_in.sj_102 = 0;
  _dev_in.alarm = 0;
  _dev_in.alarm_playing = 0;
  
  _dev_out.ls_t01 = 0;
  _dev_out.ls_t02 = 0;
  _dev_out.lc_t = 0;
  _dev_out.ac_t = 0;
  _dev_out.asp = 0;
  _dev_out.ls_101 = 0;
  _dev_out.ls_102 = 0;
  _dev_out.lc_1 = 0;
  _dev_out.ac_1 = 0;

  Data data = current_data();
  data.dev_out = _dev_out;
}

void devices_out_handler(int command) {
  if (command == LS_T01) {
    _dev_out.ls_t01 = _dev_out.ls_t01 == 1 ? 0 : 1;
  }

  if (command == LS_T02) {
    _dev_out.ls_t02 = _dev_out.ls_t02 == 1 ? 0 : 1;
  }

  if (command == LC_T) {
    _dev_out.lc_t = _dev_out.lc_t == 1 ? 0 : 1;
  }

  if (command == AC_T) {
    _dev_out.ac_t = _dev_out.ac_t == 1 ? 0 : 1;
  }

  if (command == ASP) {
    _dev_out.asp = _dev_out.asp == 1 ? 0 : 1;
  }

  if (command == LS_101) {
    _dev_out.ls_101 = _dev_out.ls_101 == 1 ? 0 : 1;
  }

  if (command == LS_102) {
    _dev_out.ls_102 = _dev_out.ls_102 == 1 ? 0 : 1;
  }

  if (command == LC_1) {
    _dev_out.lc_1 = _dev_out.lc_1 == 1 ? 0 : 1;
  }

  if (command == AC_1) {
    _dev_out.ac_1 = _dev_out.ac_1 == 1 ? 0 : 1;
  }
}

DevicesIn recover_devices_in_data() {
  return _dev_in;
}
