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
#define SERVER_DISTRIBUTED_1_PORT 10111
#define SERVER_DISTRIBUTED_2_PORT 10211

void* server_handler(int floor) {
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;

  int socket_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (socket_id < 0) {
    printf("Falha no socket do Servidor\n");
    finishWithError(0);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(floor == 0 ? SERVER_DISTRIBUTED_1_PORT : SERVER_DISTRIBUTED_2_PORT);

  if (bind(socket_id, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    printf("Falha no Bind\n");
    finishWithError(0);
  }

  if (listen(socket_id, 10) < 0) {
    printf("Falha no Listen\n");
    finishWithError(0);
  }

  while (1) {
    unsigned int client_length = sizeof(client_addr);

    int socket_id = accept(socket_id, (struct sockaddr *)&client_addr, &client_length);
    
    if (socket_id < 0) {
      printf("Falha no Accept\n");
      finishWithError(0);
    }

    printf("Client Connected %s\n", inet_ntoa(client_addr.sin_addr));

    char buffer[16];
    int size = recv(socket_id, buffer, 16, 0);

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

      if (send(socket_id, buf, buf_size, 0) != buf_size) {
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

      if (send(socket_id, buf, buf_size, 0) != buf_size) {
        printf("Error: Send failed\n");
      }
    }

    close(socket_id);
  }
  close(socket_id);
}

void send_command(int command) {
  struct sockaddr_in client_addr;
  int socket_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  char message[16];

  sprintf(message, "%d", command);

  if (socket_id < 0) {
    printf("Erro no socket()");
    finishWithError(0);
  }

  client_addr.sin_family = AF_INET;
  client_addr.sin_addr.s_addr = inet_addr(SERVER_CENTRAL_IP);
  client_addr.sin_port = htons(SERVER_CENTRAL_PORT);

  if (connect(socket_id, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
    printf("Erro no connect()\n");
    finishWithError(0);
  }

  int size = strlen(message);

  if (send(socket_id, message, size, 0) != size) {
    printf("Erro no envio: numero de bytes enviados diferente do esperado\n");
    finishWithError(0);
  }

  close(socket_id);
}
