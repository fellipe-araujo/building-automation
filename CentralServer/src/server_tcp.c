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

#define SERVER_CENTRAL_PORT 10032

void process_client_tcp(int client_id) {
  char buffer[16];
  int size;

  if ((size = recv(client_id, buffer, 16, 0)) < 0) {
    char *message = "ERRO NO RECV: Messagem recebida com o tamanho menor do que o esperado!";
    quit_handler(message);
  }

  while (size > 0) {
    int command;
    sscanf(buffer, "%d", &command);

    devices_in_handler(command);

    if (send(client_id, buffer, size, 0) != size) {
      char *message = "ERROR NO SEND: Número de bytes enviados diferente do esperado!";
      quit_handler(message);
    }

    if ((size = recv(client_id, buffer, 16, 0)) < 0) {
      char *message = "ERRO NO RECV: Messagem recebida com o tamanho menor do que o esperado!";
      quit_handler(message);
    }
  }
}

void* recv_message() {
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;

	int server_id = socket(AF_INET, SOCK_STREAM, 0);

  if (server_id < 0) {
    char *message = "ERRO NO SOCKET DO SERVIDOR!";
    quit_handler(message);
  }

	memset(&server_addr, '0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_CENTRAL_PORT);

	if (bind(server_id, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
    char *message = "ERRO NO BIND!";
    quit_handler(message);
  }

	if (listen(server_id, 10) < 0) {
		char *message = "ERRO NO LISTEN!";
		quit_handler(message);
	}

  while (1) {
	  unsigned int client_length = sizeof(client_addr);
	  int client_id = accept(server_id, (struct sockaddr*) &client_addr, &client_length);

    if (client_id < 0) {
      char *message = "ERRO NO ACCEPT!";
		  quit_handler(message);
    }

    process_client_tcp(client_id);
		
		close(client_id);
  }

	close(server_id);
}
