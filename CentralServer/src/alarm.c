#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "alarm.h"
#include "data.h"

int playing = 0;

void* play() {
  while (playing == 1) {
    system("cd ..; omxplayer central_beep.mp3 > /dev/null");
  }

  return NULL;
}

void alarm_handler() {
  DevicesIn dev_in = recover_devices_in_data();

  // Alarm active
  if (dev_in.alarm == 1) {
    dev_in.alarm_playing = 1;
    playing = 1;
    pthread_t alarm;
    pthread_create(&alarm, NULL, (void *)play, (void *)NULL);
  }
}

void alarm_off() {
  playing = 0;
}
