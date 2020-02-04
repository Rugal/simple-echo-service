#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include "Configuration.h"
#include "System.h"
#include "log4c.h"

System* createServer(Configuration* configuration) {
  System *system = malloc(sizeof(System));
  bzero((char *) system, sizeof(System));
  system->serverFileDescriptor = createSocketFileDescriptor();
  system->serverSocket = createServerSocket(system, configuration);
  return system;
}

System* createClient(Configuration* configuration) {
  System *system = malloc(sizeof(System));
  bzero((char *) system, sizeof(System));
  system->clientFileDescriptor = createSocketFileDescriptor();
  system->clientSocket = connectServer(system, configuration);
  return system;
}
