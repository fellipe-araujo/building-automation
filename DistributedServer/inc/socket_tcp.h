#ifndef SOCKETTCP_H
#define SOCKETTCP_H

void* server_handler(int floor);
void send_command(int command);
void close_server_socket();

#endif
