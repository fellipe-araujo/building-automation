#ifndef SOCKETTCP_H_
#define SOCKETTCP_H_

#include "data.h"

void* recv_message();
int send_command(int device, int state, int floor);
DHT22 request_data(int floor);

#endif
