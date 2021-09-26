#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LEN 16

#define IP_Server "192.168.0.53"
#define Port_Server 10011

void send_command(int command, int state) {
  int clientSocket;
  struct sockaddr_in serverAddr;
  char message[LEN];
  char buffer[LEN];
  unsigned int messageLength;

  int totalBytesReceived;

  sprintf(message, "%d %d", command, state);

  if ((clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    printf("Erro no socket()");
  }

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = inet_addr(IP_Server);
  serverAddr.sin_port = htons(Port_Server);

  if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    printf("Erro no connect()\n");
  }

  messageLength = strlen(message);

  if (send(clientSocket, message, messageLength, 0) != messageLength) {
    printf("Erro no envio: numero de bytes enviados diferente do esperado\n");
  }

  totalBytesReceived = recv(clientSocket, buffer, LEN - 1, 0);

  if (totalBytesReceived < 1) {
    printf("Não recebeu o total de bytes enviados\n");
  }

  printf("%s\n", buffer);

  close(clientSocket);
}
