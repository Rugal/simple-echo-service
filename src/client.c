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
#include "socket.h"

//Set overall log level
int log4c_level = LOG4C_ALL;

int main(int argc, char **argv) {
  Configuration configuration;
  configuration.port = 8080;
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
        printf("unknown option: %c\n", optopt);
        break;
    }
  }

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
