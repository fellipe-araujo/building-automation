#include "data.h"

DevicesIn _dev_in;
DevicesOut _dev_out;

void data_init() {
  _dev_in.SP_T;
  _dev_in.SF_T;
  _dev_in.SJ_T01;
  _dev_in.SJ_T02;
  _dev_in.SPo_T;
  _dev_in.SC_IN;
  _dev_in.SC_OUT;
  _dev_in.SP_1;
  _dev_in.SF_1;
  _dev_in.SJ_101;
  _dev_in.SJ_102;
  
  _dev_out.LS_T01;
  _dev_out.LS_T02;
  _dev_out.LC_T;
  _dev_out.AC_T;
  _dev_out.ASP;
  _dev_out.LS_101;
  _dev_out.LS_102;
  _dev_out.LC_1;
  _dev_out.AC_1;

  Data data = current_data();
  data.dev_out = _dev_out;
}
