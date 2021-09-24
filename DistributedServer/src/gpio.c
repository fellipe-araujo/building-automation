#include "gpio.h"

int device_exist(int device) {
  if (
    device == LS_T01 ||
    device == LS_T02 ||
    device == LC_T ||
    device == AC_T ||
    device == ASP ||
    device == LS_101 ||
    device == LS_102 ||
    device == LC_1 ||
    device == AC_1
  ) {
    return 1;
  }
  return 0;
}

void gpio_setup() {
  wiringPiSetup();

  pinMode(SP_T, OUTPUT);
  pinMode(SF_T, OUTPUT);
  pinMode(SJ_T01, OUTPUT);
  pinMode(SJ_T02, OUTPUT);
  pinMode(SPo_T, OUTPUT);
  pinMode(SC_IN, OUTPUT);
  pinMode(SC_OUT, OUTPUT);
  pinMode(SP_1, OUTPUT);
  pinMode(SF_1, OUTPUT);
  pinMode(SJ_101, OUTPUT);
  pinMode(SJ_102, OUTPUT);
}

void change_device_state(int device, int state) {
  if (device_exist(device)) {
    pinMode(device, OUTPUT);
    digitalWrite(device, state);
  }
}

void disable_output_devoces() {
  change_device_state(LS_T01, LOW);
  change_device_state(LS_T02, LOW);
  change_device_state(LC_T, LOW);
  change_device_state(AC_T, LOW);
  change_device_state(ASP, LOW);
  change_device_state(LS_101, LOW);
  change_device_state(LS_102, LOW);
  change_device_state(LC_1, LOW);
  change_device_state(AC_1, LOW);
}
