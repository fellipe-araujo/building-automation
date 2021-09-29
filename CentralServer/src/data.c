#include "data.h"

DevicesOut _dev_out;
DevicesIn _dev_in;

void data_init() {
  _dev_out.ls_t01 = 0;
  _dev_out.ls_t02 = 0;
  _dev_out.lc_t = 0;
  _dev_out.ac_t = 0;
  _dev_out.asp = 0;
  _dev_out.ls_101 = 0;
  _dev_out.ls_102 = 0;
  _dev_out.lc_1 = 0;
  _dev_out.ac_1 = 0;
  _dev_out.alarm = 0;
  _dev_out.alarm_playing = 0;

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

  Data data = current_data();
  data.dev_out = _dev_out;
  print_data(data);
  print_devices_in(_dev_in);
}

void devices_in_handler(int command) {
  if (command == SP_T) {
    _dev_in.sp_t = _dev_in.sp_t == 1 ? 0 : 1;
  }

  if (command == SF_T) {
    _dev_in.sf_t = _dev_in.sf_t == 1 ? 0 : 1;
  }

  if (command == SJ_T01) {
    _dev_in.sj_t01 = _dev_in.sj_t01 == 1 ? 0 : 1;
  }

  if (command == SJ_T02) {
    _dev_in.sj_t02 = _dev_in.sj_t02 == 1 ? 0 : 1;
  }

  if (command == SPo_T) {
    _dev_in.spo_T = _dev_in.spo_T == 1 ? 0 : 1;
  }

  if (command == SC_IN) {
    _dev_in.sc_in = _dev_in.sc_in == 1 ? 0 : 1;
  }

  if (command == SC_OUT) {
    _dev_in.sc_out = _dev_in.sc_out == 1 ? 0 : 1;
  }

  if (command == SP_1) {
    _dev_in.sp_1 = _dev_in.sp_1 == 1 ? 0 : 1;
  }

  if (command == SF_1) {
    _dev_in.sf_1 = _dev_in.sf_1 == 1 ? 0 : 1;
  }

  if (command == SJ_101) {
    _dev_in.sj_101 = _dev_in.sj_101 == 1 ? 0 : 1;
  }

  if (command == SJ_102) {
    _dev_in.sj_102 = _dev_in.sj_102 == 1 ? 0 : 1;
  }

  if (
    _dev_in.sp_t == 1 ||
    _dev_in.sf_t == 1 ||
    _dev_in.sj_t01 == 1 ||
    _dev_in.sj_t02 == 1 ||
    _dev_in.spo_T == 1 ||
    _dev_in.sc_in == 1 ||
    _dev_in.sc_out == 1 ||
    _dev_in.sp_1 == 1 ||
    _dev_in.sf_1 == 1 ||
    _dev_in.sj_101 == 1 ||
    _dev_in.sj_102 == 1
  ) {
    alarm_handler();
  } else {
    Data data = current_data();
    _dev_out.alarm_playing = 0;
    alarm_off();
    data.dev_out = _dev_out;
    print_data(data);
  }
  
  print_devices_in(_dev_in);
}

void store_devices_out_update(DevicesOut dev_out) {
  if (dev_out.alarm == 0) {
    dev_out.alarm_playing = 0;
    alarm_off();
  }

  if (dev_out.alarm == 1 && (
    _dev_in.sp_t == 1 ||
    _dev_in.sf_t == 1 ||
    _dev_in.sj_t01 == 1 ||
    _dev_in.sj_t02 == 1 ||
    _dev_in.spo_T == 1 ||
    _dev_in.sc_in == 1 ||
    _dev_in.sc_out == 1 ||
    _dev_in.sp_1 == 1 ||
    _dev_in.sf_1 == 1 ||
    _dev_in.sj_101 == 1 ||
    _dev_in.sj_102 == 1
  )) {
    dev_out.alarm_playing = 1;
  }

  Data data = current_data();
  data.dev_out = dev_out;
  print_data(data);

  int res = 1;
  if (dev_out.ls_t01 != _dev_out.ls_t01) {
    res = send_command(LS_T01, dev_out.ls_t01, 0);
  }

  if (dev_out.ls_t02 != _dev_out.ls_t02) {
    res = send_command(LS_T02, dev_out.ls_t02, 0);
  }

  if (dev_out.lc_t != _dev_out.lc_t) {
    res = send_command(LC_T, dev_out.lc_t, 0);
  }

  if (dev_out.ac_t != _dev_out.ac_t) {
    res = send_command(AC_T, dev_out.ac_t, 0);
  }

  if (dev_out.asp != _dev_out.asp) {
    res = send_command(ASP, dev_out.asp, 0);
  }

  if (dev_out.ls_101 != _dev_out.ls_101) {
    res = send_command(LS_101, dev_out.ls_101, 1);
  }

  if (dev_out.ls_102 != _dev_out.ls_102) {
    res = send_command(LS_102, dev_out.ls_102, 1);
  }

  if (dev_out.lc_1 != _dev_out.lc_1) {
    res = send_command(LC_1, dev_out.lc_1, 1);
  }

  if (dev_out.ac_1 != _dev_out.ac_1) {
    res = send_command(AC_1, dev_out.ac_1, 1);
  }

  if (res == 1) {
    _dev_out = dev_out;
  }
}

DevicesOut recover_devices_out_data() {
  return _dev_out;
}
