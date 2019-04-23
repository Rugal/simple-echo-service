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

  return 0;
}

