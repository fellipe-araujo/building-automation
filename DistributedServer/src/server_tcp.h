#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "gpio.h"
#include "data.h"

void handle_output_devices(int device) {
  Data data = get_data();

  switch (device) {
  case LS_T01:
    if (data.LS_T01) {
      change_device_state(device, 1);
      data.LS_T01 = 1;
    } else {
      change_device_state(device, 0);
      data.LS_T01 = 0;
    }
    break;
  
  case LS_T02:
    if (data.LS_T02) {
      change_device_state(device, 1);
      data.LS_T02 = 1;
    } else {
      change_device_state(device, 0);
      data.LS_T02 = 0;
    }
    break;
  
  case LC_T:
    if (data.LC_T) {
      change_device_state(device, 1);
      data.LC_T = 1;
    } else {
      change_device_state(device, 0);
      data.LC_T = 0;
    }
    break;
  
  case AC_T:
    if (data.AC_T) {
      change_device_state(device, 1);
      data.AC_T = 1;
    } else {
      change_device_state(device, 0);
      data.AC_T = 0;
    }
    break;
  
  case ASP:
    if (data.ASP) {
      change_device_state(device, 1);
      data.ASP = 1;
    } else {
      change_device_state(device, 0);
      data.ASP = 0;
    }
    break;
  
  case LS_101:
    if (data.LS_101) {
      change_device_state(device, 1);
      data.LS_101 = 1;
    } else {
      change_device_state(device, 0);
      data.LS_101 = 0;
    }
    break;
  
  case LS_102:
    if (data.LS_102) {
      change_device_state(device, 1);
      data.LS_102 = 1;
    } else {
      change_device_state(device, 0);
      data.LS_102 = 0;
    }
    break;
  
  case LC_1:
    if (data.LC_1) {
      change_device_state(device, 1);
      data.LC_1 = 1;
    } else {
      change_device_state(device, 0);
      data.LC_1 = 0;
    }
    break;
  
  case AC_1:
    if (data.AC_1) {
      change_device_state(device, 1);
      data.AC_1 = 1;
    } else {
      change_device_state(device, 0);
      data.AC_1 = 0;
    }
    break;
  
  default:
    break;
  }

  set_data(data);
}
