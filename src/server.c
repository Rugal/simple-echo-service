#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include "Configuration.h"
#include "System.h"
#include "log4c.h"
#include "socket.h"

//Set overall log level
int log4c_level = LOG4C_ALL;

int main() {
  Configuration configuration;
  configuration.port = 8080;
  configuration.queueLength = 5;

  System system;
  system.serverFileDescriptor = createFileDescriptor();
  system.serverSocket = createSocket(&system, &configuration);


  //service section begin
  struct sockaddr_in client;
  int clientSize = sizeof(client);
  //start listening
  int clientFileDescriptor = accept(system.serverFileDescriptor, (struct sockaddr *) &client, &clientSize);

  if (clientFileDescriptor < 0)
    LOG_ERROR("Fail to accept client connection");
  char buffer[256];
  bzero(buffer, 256);
  int n = read(clientFileDescriptor, buffer, 255);
  if (n < 0)
    LOG_ERROR("ERROR reading from socket");
  printf("Here is the message: %s\n",buffer);

  return 0;
}

