#include "data.h"

Data data;

void init_data() {
  data.LS_T01 = 0;
  data.LS_T02 = 0;
  data.LC_T = 0;
  data.AC_T = 0;
  data.SP_T = 0;
  data.SF_T = 0;
  data.SJ_T01 = 0;
  data.SJ_T02 = 0;
  data.SPo_T = 0;
  data.SC_IN = 0;
  data.SC_OUT = 0;
  data.ASP = 0;
  data.LS_101 = 0;
  data.LS_102 = 0;
  data.LC_1 = 0;
  data.AC_1 = 0;
  data.SP_1 = 0;
  data.SF_1 = 0;
  data.SJ_101 = 0;
  data.SJ_102 = 0;
}

Data get_data() {
  return data;
}

void set_data(Data _data) {
  data = _data;
}
