#include "socket_tcp.h"

#define SERVER_DISTRIBUTED_IP "192.168.0.52"
#define SERVER_DISTRIBUTED_PORT 10111
#define SERVER_CENTRAL_PORT 10011

void* recv_message() {
  struct sockaddr_in server_addr, client_addr;

	int socket_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&server_addr, '0', sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_CENTRAL_PORT);

	bind(socket_id, (struct sockaddr*) &server_addr, sizeof(server_addr));

	if (listen(socket_id, 10) == -1) {
		finishWithError(0);
	}

  while (1) {
	  unsigned int len = sizeof(client_addr);
	  int client_socket = accept(socket_id, (struct sockaddr*) &client_addr, &len);

    char buffer[16];
	  int size = recv(client_socket, buffer, 16, 0);

    if (size < 0) {
      finishWithError(0);
    }
    
    buffer[15] = '\0';

		int command;
		sscanf(buffer, "%d", &command);
    devices_out_handler(command);
		
		close(client_socket);
  }

	close(socket_id);
}

int send_command(int item, int status) {
  struct sockaddr_in client_addr;

  int socket_id = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_id == -1) {
    finishWithError(0);
  }

  client_addr.sin_family = AF_INET;
  client_addr.sin_addr.s_addr = inet_addr(SERVER_DISTRIBUTED_IP);
  client_addr.sin_port = htons(SERVER_DISTRIBUTED_PORT);

  if (connect(socket_id, (struct sockaddr*) &client_addr, sizeof(client_addr)) < 0) {
    finishWithError(0);
  }

  char buf[6];
  snprintf(buf, 6, "%d %d %d", 1, item, status);
  int size = strlen(buf);

  if (send(socket_id, buf, size, 0) != size) {
		finishWithError(0);
  }

  char buffer[16];
  int size_rec = recv(socket_id, buffer, 16, 0);

  if (size_rec < 0) {
    finishWithError(0);
  }

  buffer[15] = '\0';

  int res;
  sscanf(buffer, "%d", &res);

  close(socket_id);

  return res;
}

DHT22 request_data() {
  struct sockaddr_in client_addr;

  DHT22 dht22;
  dht22.temperature = 0.0;
  dht22.humidity = 0.0;

  int socket_id = socket(AF_INET, SOCK_STREAM, 0);
  
  if (socket_id == -1) {
    return dht22;
  }

  client_addr.sin_family = AF_INET;
  client_addr.sin_addr.s_addr = inet_addr(SERVER_DISTRIBUTED_IP);
  client_addr.sin_port = htons(SERVER_DISTRIBUTED_PORT);

  if (connect(socket_id, (struct sockaddr*) &client_addr, sizeof(client_addr)) < 0) {
    return dht22;
  }

  char buf[2];
  snprintf(buf, 2, "%d", 2);
  int size = strlen(buf);

  if (send(socket_id, buf, size, 0) != size) {
    close(socket_id);
    return dht22;
  }

  char buffer[16];
  int size_rec = recv(socket_id, buffer, 16, 0);

  if (size_rec < 0) {
    close(socket_id);
    return dht22;
  }

  buffer[15] = '\0';
	
  int command;
  float temperature;
  float humidity;

  sscanf(buffer, "%d %f %f", &command, &temperature, &humidity);
  dht22.temperature = temperature;
  dht22.humidity = humidity;

  close(socket_id);

  return dht22;
}
