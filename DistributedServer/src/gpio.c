#include <stdio.h>
#include <unistd.h>
#include "gpio.h"
#include "client_tcp.h"

void gpio_setup() {
  wiringPiSetup();
}

void handle_presence_ground(void) {
  printf("SP_T - Sensor de presenca do andar terreo foi detectado!\n");
  send_command(SP_T);
}

void handle_smoke_ground(void) {
  printf("SF_T - Sensor de fumaça do andar terreo foi detectado!\n");
  send_command(SF_T);
}

void handle_window_1_ground(void) {
  printf("SJ_T01 - Sensor da janela 01 do andar terreo foi detectado!\n");
  send_command(SJ_T01);
}

void handle_window_2_ground(void) {
  printf("SJ_T02 - Sensor da janela 02 do andar terreo foi detectado!\n");
  send_command(SJ_T02);
}

void handle_door_ground(void) {
  printf("SPo_T - Sensor da porta do andar terreo foi detectado!\n");
  send_command(SPo_T);
}

// void handle_counter_in_ground(void) {
//   millis();
//   printf("Counter in sensor on the ground floor was detected!\n");
//   send_command(SC_IN);
//   delay(300);
// }

// void handle_counter_out_ground(void) {
//   printf("Counter out sensor on the ground floor was detected!\n");
//   send_command(SC_OUT);
//   delay(300);
// }

void handle_presence_first(void) {
  printf("SP_1 - Sensor de presenca do primeiro andar foi detectado!\n");
  send_command(SP_1);
}

void handle_smoke_first(void) {
  printf("SF_1 - Sensor de fumaca do primeiro andar foi detectado!\n");
  send_command(SF_1);
}

void handle_window_1_first(void) {
  printf("SJ_101 - Sensor da janela 101 do primeiro andar foi detectado!\n");
  send_command(SJ_101);
}

void handle_window_2_first(void) {
  printf("SJ_102 - Sensor da janela 102 do primeiro andar foi detectado!\n");
  send_command(SJ_102);
}

void* gpio_handler() {
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

  // pinMode(SC_IN, OUTPUT);
  // wiringPiISR(SC_IN, INT_EDGE_BOTH, &handle_counter_in_ground);

  // pinMode(SC_OUT, OUTPUT);
  // wiringPiISR(SC_OUT, INT_EDGE_BOTH, &handle_counter_out_ground);

  pinMode(SP_1, OUTPUT);
  wiringPiISR(SP_1, INT_EDGE_BOTH, &handle_presence_first);

  pinMode(SF_1, OUTPUT);
  wiringPiISR(SF_1, INT_EDGE_BOTH, &handle_smoke_first);

  pinMode(SJ_101, OUTPUT);
  wiringPiISR(SJ_101, INT_EDGE_BOTH, &handle_window_1_first);

  pinMode(SJ_102, OUTPUT);
  wiringPiISR(SJ_102, INT_EDGE_BOTH, &handle_window_2_first);

  for (;;) {
    sleep(1);
  }
}

void change_device_state(int device, int state) {
  pinMode(device, OUTPUT);
  digitalWrite(device, state);
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
