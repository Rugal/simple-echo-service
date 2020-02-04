#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Configuration.h"
#include "System.h"
#include "log4c.h"
#include "Socket.h"

#define BUFFER_SIZE 1024

//Set overall log level
int log4c_level = LOG4C_ALL;

int main(int argc, char **argv) {
  Configuration *configuration = parseConfiguration(argc, argv);
  System *system = createClient(configuration);

  LOG_INFO("Please enter the message: ");
  char buffer[BUFFER_SIZE];
  bzero(buffer, BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE - 1, stdin);
  int n = write(system->clientFileDescriptor,buffer,strlen(buffer));
  if (n < 0)
    LOG_ERROR("Fail to write to server");

  return 0;
}
