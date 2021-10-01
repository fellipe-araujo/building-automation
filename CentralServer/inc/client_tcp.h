#include "data.h"

#ifndef CLIENTTCP_H_
#define CLIENTTCP_H_

int send_command(int device, int state, int floor);
DHT22 request_data(int floor);

#endif
