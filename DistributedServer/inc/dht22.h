#ifndef DHT22_H_
#define DHT22_H_

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// CONSTANTS 
#define MAX_TIMINGS	85
#define DEBUG 1
#define WAIT_TIME 2000

int setup_dht22();
int read_dht22_data(float *temperature, float *humidity);

#endif
