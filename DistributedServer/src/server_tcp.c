#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "gpio.h"
#include "dht22.h"
#include "socket_quit.h"

#define SERVER_DISTRIBUTED_1_PORT 10111
#define SERVER_DISTRIBUTED_2_PORT 10211

void process_client_tcp(int client_id) {
  char buffer[16];
  int size;

  if ((size = recv(client_id, buffer, 16, 0)) < 0) {
    printf("ERRO NO RECV: Messagem recebida com o tamanho menor do que o esperado!\n");
    quit_handler();
  }

  buffer[15] = '\0';

  int command;
  sscanf(buffer, "%d", &command);

  printf("Comando recebido: %d\n", command);

  // On/Off Device
  if (command == 1) {
    printf("Device state change requested. . .\n");

    int device;
    int state;

    sscanf(buffer, "%d %d %d", &command, &device, &state);

    change_device_state(device, state);

    char buf[2];
    snprintf(buf, 2, "%d", 1);

    int buf_size = strlen(buf);
    printf("Sending request result. . .\n");

    if (send(client_id, buf, buf_size, 0) != buf_size) {
      printf("Error: Send failed\n");
    }
  }

  // DHT22 Sensor
  if (command == 2) {
    printf("DHT22 Sensor data requested. . .\n");

    float temperature = 0.0;
    float humidity  = 0.0;

    dht22_read_data(&temperature, &humidity);

    char buf[16];
    snprintf(buf, 16, "%d %4.2f %4.2f", 2, temperature, humidity);

    int buf_size = strlen(buf);
    printf("Sending DHT22 Sensor data request. . .\n");

    if (send(client_id, buf, buf_size, 0) != buf_size) {
      printf("Error: Send failed\n");
    }
  }
}

void* server_handler(int floor) {
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;

  int server_id = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (server_id < 0) {
    printf("ERRO NO SOCKET DO SERVIDOR!\n");
    quit_handler();
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(floor == 0 ? SERVER_DISTRIBUTED_1_PORT: SERVER_DISTRIBUTED_2_PORT);

  if (bind(server_id, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    printf("ERRO NO BIND!\n");
    quit_handler();
  }

  if (listen(server_id, 10) < 0) {
    printf("ERRO NO LISTEN!\n");
		quit_handler();
  }

  while (1) {
    unsigned int client_length = sizeof(client_addr);

    int client_id = accept(server_id, (struct sockaddr *)&client_addr, &client_length);
    
    if (client_id < 0) {
      printf("ERRO NO ACCEPT!\n");
		  quit_handler();
    }

    process_client_tcp(client_id);

    close(client_id);
  }
  close(server_id);
}
