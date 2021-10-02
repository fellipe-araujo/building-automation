#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "gpio.h"
#include "dht22.h"
#include "socket_quit.h"

#define SERVER_CENTRAL_IP "192.168.0.53"
#define SERVER_CENTRAL_PORT 10032

void send_command(int command) {
  struct sockaddr_in server_addr;
  int client_id = socket(AF_INET, SOCK_STREAM, 0);

  if (client_id < 0) {
    printf("ERROR NO SOCKET!\n");
    quit_handler();
  }

  memset(&server_addr, '0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(SERVER_CENTRAL_IP);
  server_addr.sin_port = htons(SERVER_CENTRAL_PORT);
  
  if (connect(client_id, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    printf("ERROR NO CONNECT!\n");
    quit_handler();
  }

  char buffer[6];

  snprintf(buffer, 6, "%d", command);
  int size = strlen(buffer);

  if (send(client_id, buffer, size, 0) != size) {
    printf("ERROR NO SEND: Número de bytes enviados diferente do esperado!\n");
    quit_handler();
  }

  close(client_id);
}
