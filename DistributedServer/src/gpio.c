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

void handle_presence_ground() {
  int state = digitalRead(SP_T);
  printf("Presence sensor on the ground floor was detected!");
}

void handle_smoke_ground() {
  int state = digitalRead(SF_T);
  printf("Smoke sensor on the ground floor was detected!");
}

void handle_window_1_ground() {
  int state = digitalRead(SJ_T01);
  printf("Window 1 sensor on the ground floor was detected!");
}

void handle_window_2_ground() {
  int state = digitalRead(SJ_T02);
  printf("Window 2 sensor on the ground floor was detected!");
}

void handle_door_ground() {
  int state = digitalRead(SPo_T);
  printf("Door sensor on the ground floor was detected!");
}

void handle_counter_in_ground() {
  int state = digitalRead(SC_IN);
  printf("Counter in sensor on the ground floor was detected!");
}

void handle_counter_out_ground() {
  int state = digitalRead(SC_OUT);
  printf("Counter out sensor on the ground floor was detected!");
}

void handle_presence_first() {
  int state = digitalRead(SP_1);
  printf("Presence sensor on the first floor was detected!");
}

void handle_smoke_first() {
  int state = digitalRead(SF_1);
  printf("Smoke sensor on the first floor was detected!");
}

void handle_window_1_first() {
  int state = digitalRead(SJ_101);
  printf("Window 1 sensor on the first floor was detected!");
}

void handle_window_2_first() {
  int state = digitalRead(SJ_102);
  printf("Window 2 sensor on the first floor was detected!");
}

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

void disable_output_devices() {
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
