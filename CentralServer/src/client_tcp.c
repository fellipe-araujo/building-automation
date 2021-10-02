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

#define SERVER_DISTRIBUTED_IP "192.168.0.52"
#define SERVER_DISTRIBUTED_1_PORT 10132
#define SERVER_DISTRIBUTED_2_PORT 10232

int send_command(int device, int state, int floor) {
  struct sockaddr_in server_addr;
  int client_id = socket(AF_INET, SOCK_STREAM, 0);

  if (client_id < 0) {
    char *message = "ERRO NO SOCKET!";
    quit_handler(message);
  }

  memset(&server_addr, '0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(SERVER_DISTRIBUTED_IP);
  server_addr.sin_port = htons(floor == 0 ? SERVER_DISTRIBUTED_1_PORT : SERVER_DISTRIBUTED_2_PORT);

  if (connect(client_id, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
    char *message = "ERROR NO CONNECT!";
    quit_handler(message);
  }

  char buf[16];

  // command = 1 | device | state
  snprintf(buf, 16, "%d %d %d", 1, device, state);
  int size = strlen(buf);

  if (send(client_id, buf, size, 0) != size) {
		char *message = "ERROR NO SEND: Número de bytes enviados diferente do esperado!";
    quit_handler(message);
  }

  char buffer[2];
  int size_rec = recv(client_id, buffer, 1, 0);
  
  if (size_rec < 0) {
    char *message = "ERROR NO RECV!";
    quit_handler(message);
  }

  int res;
  sscanf(buffer, "%d", &res);

  close(client_id);

  return res;
}

DHT22 request_data(int floor) {
  struct sockaddr_in server_addr;

  DHT22 dht22;
  dht22.temperature = 0.0;
  dht22.humidity = 0.0;

  int client_id = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  
  if (client_id < 0) {
    printf("client_id < 0\n");
    return dht22;
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(SERVER_DISTRIBUTED_IP);
  server_addr.sin_port = htons(floor == 0 ? SERVER_DISTRIBUTED_1_PORT : SERVER_DISTRIBUTED_2_PORT);

  if (connect(client_id, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
    // printf("connect() < 0\n");
    return dht22;
  }

  char buf[6];

  // command = 2
  snprintf(buf, 6, "%d %d", 2, floor);
  int size = strlen(buf);

  if (send(client_id, buf, size, 0) != size) {
    printf("send() != size\n");
    close(client_id);
    return dht22;
  }

  char buffer[16];
  int total_bytes_rec = 0;
  int size_rec;

  // printf("VAI ENTRAR NO WHILE()\n");
  while (total_bytes_rec < size) {
    if ((size_rec = recv(client_id, buffer, 16 - 1, 0)) <= 0) {
      printf("Não recebeu o total de bytes enviados\n");
      close(client_id);
      return dht22;
    }

    total_bytes_rec += size_rec;
    buffer[size_rec] = '\0';
    // printf("%s\n", buffer);
  }
	
  int command;
  float temperature = 0.0;
  float humidity = 0.0;

  sscanf(buffer, "%d", &command);

  if (command == 2) {
    sscanf(buffer, "%d %f %f", &command, &temperature, &humidity);
    dht22.temperature = temperature;
    dht22.humidity = humidity;
  }

  close(client_id);

  return dht22;
}
