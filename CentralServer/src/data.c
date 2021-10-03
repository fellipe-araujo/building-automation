#include <stdio.h>
#include <unistd.h>

#include "data.h"
#include "menu.h"
#include "alarm.h"
#include "client_tcp.h"
#include "app.h"

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
  _dev_in.person_counter = 0;

  Data data = current_data();
  data.dev_out = _dev_out;
  print_data(data);
  print_devices_in(_dev_in);
}

void devices_in_handler(int command) {
  // printf("Command: %d   |   State: %d\n", command, state);
  if (command == SP_T) {
    if (_dev_in.sp_t == 1) {
      _dev_in.sp_t = 0;
    } else {
      _dev_in.sp_t = 1;
    }
  }

  else if (command == LC_T) {
    Data dev_out_10s = current_data();
    _dev_out.lc_t = _dev_out.lc_t == 1 ? 0 : 1;
    dev_out_10s.dev_out = _dev_out;
    print_data(dev_out_10s);
  }

  else if (command == SF_T) {
    _dev_in.sf_t = _dev_in.sf_t == 1 ? 0 : 1;
  }

  else if (command == SJ_T01) {
    _dev_in.sj_t01 = _dev_in.sj_t01 == 1 ? 0 : 1;
  }

  else if (command == SJ_T02) {
    _dev_in.sj_t02 = _dev_in.sj_t02 == 1 ? 0 : 1;
  }

  else if (command == SPo_T) {
    _dev_in.spo_T = _dev_in.spo_T == 1 ? 0 : 1;
  }

  // else if (command == SC_IN) {
  //   if (_dev_in.person_counter < 100)
  //     _dev_in.person_counter++;
  // }

  // else if (command == SC_OUT) {
  //   if (_dev_in.person_counter > 0)
  //     _dev_in.person_counter--;
  // }

  else if (command == SP_1) {
    if (_dev_in.sp_1 == 1) {
      _dev_in.sp_1 = 0;
      send_command(LC_1, 1, 0);
    } else {
      _dev_in.sp_1 = 1;
    }
  }

  else if (command == LC_1) {
    Data dev_out_10s = current_data();
    _dev_out.lc_1 = _dev_out.lc_1 == 1 ? 0 : 1;
    dev_out_10s.dev_out = _dev_out;
    print_data(dev_out_10s);
  }

  else if (command == SF_1) {
    _dev_in.sf_1 = _dev_in.sf_1 == 1 ? 0 : 1;
  }

  else if (command == SJ_101) {
    _dev_in.sj_101 = _dev_in.sj_101 == 1 ? 0 : 1;
  }

  else if (command == SJ_102) {
    _dev_in.sj_102 = _dev_in.sj_102 == 1 ? 0 : 1;
  }

  if (
    _dev_in.sp_t == 1 ||
    _dev_in.sf_t == 1 ||
    _dev_in.sj_t01 == 1 ||
    _dev_in.sj_t02 == 1 ||
    _dev_in.spo_T == 1 ||
    _dev_in.sp_1 == 1 ||
    _dev_in.sf_1 == 1 ||
    _dev_in.sj_101 == 1 ||
    _dev_in.sj_102 == 1
  ) {
    // if (_dev_out.alarm == 0 && _dev_in.sp_t == 1) {
    //   // _dev_out.lc_t = 1;
    //   send_command(LC_T, 1, 0);
    // }

    // if (_dev_out.alarm == 0 && _dev_in.sp_1 == 1) {
    //   // _dev_out.lc_1 = 1;
    //   send_command(LC_1, 1, 0);
    // }

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

void store_devices_out_update(DevicesOut dev_out_updated) {
  if (dev_out_updated.alarm == 0) {
    dev_out_updated.alarm_playing = 0;
    alarm_off();
  }

  if (dev_out_updated.alarm == 1 && (
    _dev_in.sp_t == 1 ||
    _dev_in.sj_t01 == 1 ||
    _dev_in.sj_t02 == 1 ||
    _dev_in.spo_T == 1 ||
    _dev_in.sp_1 == 1 ||
    _dev_in.sj_101 == 1 ||
    _dev_in.sj_102 == 1
  )) {
    dev_out_updated.alarm_playing = 1;
  }

  Data data = current_data();
  data.dev_out = dev_out_updated;
  print_data(data);

  int res = 1;
  if (data.dev_out.ls_t01 != _dev_out.ls_t01) {
    res = send_command(LS_T01, data.dev_out.ls_t01, 0);
  }

  else if (data.dev_out.ls_t02 != _dev_out.ls_t02) {
    res = send_command(LS_T02, data.dev_out.ls_t02, 0);
  }

  else if (data.dev_out.lc_t != _dev_out.lc_t) {
    res = send_command(LC_T, data.dev_out.lc_t, 0);
  }

  else if (data.dev_out.ac_t != _dev_out.ac_t) {
    res = send_command(AC_T, data.dev_out.ac_t, 0);
  }

  else if (data.dev_out.asp != _dev_out.asp) {
    res = send_command(ASP, data.dev_out.asp, 0);
  }

  else if (data.dev_out.ls_101 != _dev_out.ls_101) {
    res = send_command(LS_101, data.dev_out.ls_101, 1);
  }

  else if (data.dev_out.ls_102 != _dev_out.ls_102) {
    res = send_command(LS_102, data.dev_out.ls_102, 1);
  }

  else if (data.dev_out.lc_1 != _dev_out.lc_1) {
    res = send_command(LC_1, data.dev_out.lc_1, 1);
  }

  else if (data.dev_out.ac_1 != _dev_out.ac_1) {
    res = send_command(AC_1, data.dev_out.ac_1, 1);
  }

  if (res == 1) {
    _dev_out = dev_out_updated;
  }
}

DevicesOut recover_devices_out_data() {
  return _dev_out;
}
