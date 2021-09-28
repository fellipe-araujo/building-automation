#ifndef SOCKETTCP_H_
#define SOCKETTCP_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include "data.h"
#include "alarm.h"
#include "socket_quit.h"

void* recv_message();
int send_command(int item, int status);
DHT22 request_data();

#endif
