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
#include "Socket.h"

#define BUFFER_SIZE 1024

//Set overall log level
int log4c_level = LOG4C_ALL;

int main(int argc, char **argv) {
  //TODO: need to destroy these object in the end
  Configuration* configuration = parseConfiguration(argc, argv);
  System *system = createServer(configuration);

  //service section begin
  struct sockaddr_in client;
  int clientSize = sizeof(client);
  //start listening
  LOG_INFO("Start accepting inbound request");
  for(int clientFileDescriptor;
      (clientFileDescriptor = accept(system->serverFileDescriptor,
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
