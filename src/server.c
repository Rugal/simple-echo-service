#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "Configuration.h"
#include "StringUtility.h"
#include "System.h"
#include "log4c.h"
#include "socket.h"

#define BUFFER_SIZE 1024

//Set overall log level
int log4c_level = LOG4C_ALL;

int main(int argc, char **argv) {
  Configuration configuration;
  configuration.port = 8080;
  configuration.queueLength = 5;
  strcpy(configuration.hostname, "localhost");

  for (int opt; (opt = getopt(argc, argv, "h:p:q:")) != -1;) {
    LOG_TRACE("Process option [%c]", opt);
    switch(opt) {
      case 'q':
        configuration.queueLength = atoi(optarg);
        LOG_DEBUG("Set connection queue length to [%d]", configuration.queueLength);
        break;
      case 'h':
        strcpy(configuration.hostname, optarg);
        LOG_DEBUG("Set server host to [%s]", configuration.hostname);
        break;
      case 'p':
        configuration.port = atoi(optarg);
        LOG_DEBUG("Set server port to [%d]", configuration.port);
        break;
      case '?':
        LOG_INFO("unknown option: [%c]", optopt);
        break;
    }
  }

  System system;
  system.serverFileDescriptor = createFileDescriptor();
  system.serverSocket = createSocket(&system, &configuration);

  //service section begin
  struct sockaddr_in client;
  int clientSize = sizeof(client);
  //start listening
  for(int clientFileDescriptor;
      (clientFileDescriptor = accept(system.serverFileDescriptor,
                                     (struct sockaddr *) &client,
                                     &clientSize)) >= 0;) {
    LOG_INFO("Get connection with file descriptor [%d]", clientFileDescriptor);
    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);
    if (read(clientFileDescriptor, buffer, BUFFER_SIZE - 1) < 0) {
      LOG_ERROR("ERROR reading from socket");
    } else {
      LOG_INFO("Here is the message: [%s]", trim(buffer));
    }
  }
  LOG_ERROR("Fail to accept client connection");

  return 0;
}

