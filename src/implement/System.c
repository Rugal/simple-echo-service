#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include "Configuration.h"
#include "System.h"
#include "Socket.h"
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

void freeSystem(System* s) {
  assert(s != NULL);
  if(s->clientFileDescriptor)
    shutdown(s->clientFileDescriptor, 1);
  if(s->serverFileDescriptor)
    shutdown(s->serverFileDescriptor, 0);
  if(s->clientSocket)
    free(s->clientSocket);
  if(s->serverSocket)
    free(s->serverSocket);
  free(s);
}
