#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"
#include "socket_tcp.h"
#include "data.h"

#define TIME_SLEEP 1000000

Data _data;

void app_init() {
  DHT22 dht22;
  dht22.temperature = 0.0;
  dht22.humidity = 0.0;
  _data.dht22_ground_floor = dht22;
  _data.dht22_first_floor = dht22;
}

Data current_data() {
  return _data;
}

void* app_handler() {
  while (1) {
    DHT22 dht22_ground_floor = request_data(0);
    DHT22 dht22_first_floor = request_data(1);

    if (dht22_ground_floor.temperature != 0 && dht22_ground_floor.humidity != 0) {
      _data.dht22_ground_floor = dht22_ground_floor;
    }

    if (dht22_first_floor.temperature != 0 && dht22_first_floor.humidity != 0) {
      _data.dht22_first_floor = dht22_first_floor;
    }

    DevicesOut dev_out;
    dev_out = recover_devices_out_data();
    _data.dev_out = dev_out;

    print_data(_data);
    usleep(TIME_SLEEP);
  }

  return NULL;
}
