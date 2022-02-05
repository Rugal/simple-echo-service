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
  system->configuration = configuration;
  return system;
}

System* createClient(Configuration* configuration) {
  System *system = malloc(sizeof(System));
  bzero((char *) system, sizeof(System));
  system->clientFileDescriptor = createSocketFileDescriptor();
  system->clientSocket = connectServer(system, configuration);
  system->configuration = configuration;
  return system;
}

void freeSystem(System* s) {
  assert(s != NULL);
  if(s->clientFileDescriptor) {
    LOG_TRACE("shutdown client FD");
    // shutdown(s->clientFileDescriptor, 1);
    close(s->clientFileDescriptor);
  }
  if(s->serverFileDescriptor) {
    LOG_TRACE("Shutdown server FD");
    // shutdown(s->serverFileDescriptor, 0);
    close(s->serverFileDescriptor);
  }
  if(s->clientSocket) {
    LOG_TRACE("Free client socket");
    free(s->clientSocket);
  }
  if(s->serverSocket) {
    LOG_TRACE("Free server socket");
    free(s->serverSocket);
  }
  if(s->configuration) {
    LOG_TRACE("Free system configuration");
    freeConfiguration(s->configuration);
  }
  LOG_TRACE("Free system object");
  free(s);
}
