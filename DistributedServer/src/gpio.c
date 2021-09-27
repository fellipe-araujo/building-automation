#include "gpio.h"
#include "socket_tcp.h"

void gpio_setup() {
  wiringPiSetup();
  disable_output_devices();
}

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
  printf("Presence sensor on the ground floor was detected!");
  send_command(SP_T);
}

void handle_smoke_ground() {
  printf("Smoke sensor on the ground floor was detected!");
  send_command(SF_T);
}

void handle_window_1_ground() {
  printf("Window 1 sensor on the ground floor was detected!");
  send_command(SJ_T01);
}

void handle_window_2_ground() {
  printf("Window 2 sensor on the ground floor was detected!");
  send_command(SJ_T02);
}

void handle_door_ground() {
  printf("Door sensor on the ground floor was detected!");
  send_command(SPo_T);
}

void handle_counter_in_ground() {
  printf("Counter in sensor on the ground floor was detected!");
  send_command(SC_IN);
}

void handle_counter_out_ground() {
  printf("Counter out sensor on the ground floor was detected!");
  send_command(SC_OUT);
}

void handle_presence_first() {
  printf("Presence sensor on the first floor was detected!");
  send_command(SP_1);
}

void handle_smoke_first() {
  printf("Smoke sensor on the first floor was detected!");
  send_command(SF_1);
}

void handle_window_1_first() {
  printf("Window 1 sensor on the first floor was detected!");
  send_command(SJ_101);
}

void handle_window_2_first() {
  printf("Window 2 sensor on the first floor was detected!");
  send_command(SJ_102);
}

void gpio_handler(int floor) {
  // floor = 0 -> ground
  // floor = 1 -> first
  if (floor == 0) {
    pinMode(SP_T, OUTPUT);
    wiringPiISR(SP_T, INT_EDGE_BOTH, &handle_presence_ground);

    pinMode(SF_T, OUTPUT);
    wiringPiISR(SF_T, INT_EDGE_BOTH, &handle_smoke_ground);

    pinMode(SJ_T01, OUTPUT);
    wiringPiISR(SJ_T01, INT_EDGE_BOTH, &handle_window_1_ground);
    
    pinMode(SJ_T02, OUTPUT);
    wiringPiISR(SJ_T02, INT_EDGE_BOTH, &handle_window_2_ground);

    pinMode(SPo_T, OUTPUT);
    wiringPiISR(SPo_T, INT_EDGE_BOTH, &handle_door_ground);

    pinMode(SC_IN, OUTPUT);
    wiringPiISR(SC_IN, INT_EDGE_BOTH, &handle_counter_in_ground);

    pinMode(SC_OUT, OUTPUT);
    wiringPiISR(SC_OUT, INT_EDGE_BOTH, &handle_counter_out_ground);

  } else if (floor == 1) {
    pinMode(SP_1, OUTPUT);
    wiringPiISR(SP_1, INT_EDGE_BOTH, &handle_presence_first);

    pinMode(SF_1, OUTPUT);
    wiringPiISR(SF_1, INT_EDGE_BOTH, &handle_smoke_first);

    pinMode(SJ_101, OUTPUT);
    wiringPiISR(SJ_101, INT_EDGE_BOTH, &handle_window_1_first);

    pinMode(SJ_102, OUTPUT);
    wiringPiISR(SJ_102, INT_EDGE_BOTH, &handle_window_2_first);
  }

  for (;;) {
    sleep(1);
  }
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
