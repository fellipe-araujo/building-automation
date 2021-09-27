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
#define SERVER_CENTRAL_PORT 10011
#define SERVER_DISTRIBUTED_PORT 10111

int server_socket;
int socket_client;

void* server_handler() {
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;

  int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (server_socket < 0) {
    printf("Falha no socket do Servidor\n");
    finishWithError(0);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(SERVER_DISTRIBUTED_PORT);

  if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    printf("Falha no Bind\n");
    finishWithError(0);
  }

  if (listen(server_socket, 10) < 0) {
    printf("Falha no Listen\n");
    finishWithError(0);
  }

  while (1) {
    unsigned int client_length = sizeof(client_addr);

    int socket_client = accept(server_socket, (struct sockaddr *)&client_addr, &client_length);
    
    if (socket_client < 0) {
      printf("Falha no Accept\n");
      finishWithError(0);
    }

    printf("Client Connected %s\n", inet_ntoa(client_addr.sin_addr));

    char buffer[16];
    int size = recv(socket_client, buffer, 16, 0);

    if (size < 0) {
      printf("Error");
      exit(1);
    }

    buffer[15] = '\0';

    int command;
    sscanf(buffer, "%d", &command);

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

      if (send(socket_client, buf, buf_size, 0) != buf_size) {
        printf("Error: Send failed\n");
      }
    }

    // DHT22 Sensor
    if (command == 2) {
      printf("DHT22 Sensor data requested. . .\n");

      float temperature = -1;
      float humidity  = -1;

      dht22_read_data(&temperature, &humidity);

      char buf[16];
      snprintf(buf, 16, "%d %4.2f %4.2f", 2, temperature, humidity);

      int buf_size = strlen(buf);
      printf("Sending DHT22 Sensor data request. . .\n");

      if (send(socket_client, buf, buf_size, 0) != buf_size) {
        printf("Error: Send failed\n");
      }
    }

    close(socket_client);
  }
  close(server_socket);
}

void send_command(int command) {
  struct sockaddr_in client_addr;
  int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  char message[LEN];

  sprintf(message, "%d", command);

  if (client_socket < 0) {
    printf("Erro no socket()");
    finishWithError(0);
  }

  client_addr.sin_family = AF_INET;
  client_addr.sin_addr.s_addr = inet_addr(SERVER_CENTRAL_IP);
  client_addr.sin_port = htons(SERVER_CENTRAL_PORT);

  if (connect(client_socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
    printf("Erro no connect()\n");
    finishWithError(0);
  }

  int size = strlen(message);

  if (send(client_socket, message, size, 0) != size) {
    printf("Erro no envio: numero de bytes enviados diferente do esperado\n");
    finishWithError(0);
  }

  close(client_socket);
}

void close_server_socket() {
  close(socket_client);
  close(server_socket);
}
