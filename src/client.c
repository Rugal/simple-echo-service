#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "Configuration.h"
#include "System.h"
#include "log4c.h"
#include "socket.h"

//Set overall log level
int log4c_level = LOG4C_ALL;

int main() {
  Configuration configuration;
  configuration.port = 8080;
  strcpy(configuration.hostname, "localhost");
  System system;
  system.clientFileDescriptor = createFileDescriptor();
  system.clientSocket = connectServer(&system, &configuration);

  printf("Please enter the message: ");
  char buffer[256];
  bzero(buffer,256);
  fgets(buffer,255,stdin);
  int n = write(system.clientFileDescriptor,buffer,strlen(buffer));
  if (n < 0)
    LOG_ERROR("Fail to write to server");

  return 0;
}
