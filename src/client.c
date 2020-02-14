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
#include "StringUtility.h"

//Set overall log level
int log4c_level = LOG4C_ALL;

int main(int argc, char **argv)
{
  Configuration *configuration = parseConfiguration(argc, argv);
  System *system = createClient(configuration);

  char buffer[BUFFER_SIZE];
  bzero(buffer, BUFFER_SIZE);
  LOG_INFO("Please enter the message: ");
  for (fgets(buffer, BUFFER_SIZE - 1, stdin);
       strcmp(trim(buffer), "exit") != 0;
       fgets(buffer, BUFFER_SIZE - 1, stdin))
  {
    const int n = write(system->clientFileDescriptor, buffer, strlen(buffer));
    if (n < 0)
      LOG_ERROR("Fail to write to server");
    bzero(buffer, BUFFER_SIZE);
    LOG_INFO("Please enter the message: ");
  }

  freeConfiguration(configuration);
  freeSystem(system);

  return 0;
}
