#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "gpio.h"
#include "data.h"
#include "dht22.h"

#define PORT 10111

int serverSocket;
int socketClient;

void handle_output_devices(int device) {
  Data data = get_data();

  switch (device) {
  case LS_T01:
    if (data.LS_T01) {
      change_device_state(device, 1);
      data.LS_T01 = 1;
    } else {
      change_device_state(device, 0);
      data.LS_T01 = 0;
    }
    break;
  
  case LS_T02:
    if (data.LS_T02) {
      change_device_state(device, 1);
      data.LS_T02 = 1;
    } else {
      change_device_state(device, 0);
      data.LS_T02 = 0;
    }
    break;
  
  case LC_T:
    if (data.LC_T) {
      change_device_state(device, 1);
      data.LC_T = 1;
    } else {
      change_device_state(device, 0);
      data.LC_T = 0;
    }
    break;
  
  case AC_T:
    if (data.AC_T) {
      change_device_state(device, 1);
      data.AC_T = 1;
    } else {
      change_device_state(device, 0);
      data.AC_T = 0;
    }
    break;
  
  case ASP:
    if (data.ASP) {
      change_device_state(device, 1);
      data.ASP = 1;
    } else {
      change_device_state(device, 0);
      data.ASP = 0;
    }
    break;
  
  case LS_101:
    if (data.LS_101) {
      change_device_state(device, 1);
      data.LS_101 = 1;
    } else {
      change_device_state(device, 0);
      data.LS_101 = 0;
    }
    break;
  
  case LS_102:
    if (data.LS_102) {
      change_device_state(device, 1);
      data.LS_102 = 1;
    } else {
      change_device_state(device, 0);
      data.LS_102 = 0;
    }
    break;
  
  case LC_1:
    if (data.LC_1) {
      change_device_state(device, 1);
      data.LC_1 = 1;
    } else {
      change_device_state(device, 0);
      data.LC_1 = 0;
    }
    break;
  
  case AC_1:
    if (data.AC_1) {
      change_device_state(device, 1);
      data.AC_1 = 1;
    } else {
      change_device_state(device, 0);
      data.AC_1 = 0;
    }
    break;
  
  default:
    break;
  }

  set_data(data);
}

void handle_client(int socketClient) {
  char buffer[16];
  char response[16];
  int responseLength;
  int command;
  float temperature = -1;
  float humidity  = -1;

  dht22_read_data(&temperature, &humidity);

  if ((responseLength = recv(socketClient, buffer, 16, 0)) < 0) {
    printf("Erro no recv()\n");
  }

  sscanf(buffer, "%d", &command);
  handle_output_devices(command);
  snprintf(response, 15, "%d %.2f %.2f", command, temperature, humidity);

  if (send(socketClient, response, 16 - 1, 0) != 15) {
    printf("Erro no envio - sends()\n");
  }
}

void receive_messages() {
  struct sockaddr_in serverAddr;
  struct sockaddr_in clientAddr;
  unsigned int clientLength;

  if ((serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    printf("falha no socker do Servidor\n");
  }

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(PORT);

  if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    printf("Falha no Bind\n");
  }

  if (listen(serverSocket, 10) < 0) {
    printf("Falha no Listen\n");
  }

  while (1) {
    clientLength = sizeof(clientAddr);
    
    if ((socketClient = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientLength)) < 0) {
      printf("Falha no Accept\n");
    }

    printf("Client Connected %s\n", inet_ntoa(clientAddr.sin_addr));

    handle_client(socketClient);
    close(socketClient);
  }
  close(serverSocket);
}

void close_server_socket() {
  close(socketClient);
  close(serverSocket);
}
