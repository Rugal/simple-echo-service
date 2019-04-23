#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include "Configuration.h"
#include "System.h"
#include "log4c.h"
#include "socket.h"

int createFileDescriptor() {
  const int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    LOG_ERROR("Fail to create file descriptor");
    exit(1);
  }
  LOG_DEBUG("Create socket file descriptor [%d]", fd);
  return fd;
}

struct sockaddr_in* createSocket(const System *system, const Configuration* configuration) {
  assert(configuration != NULL);
  assert(system != NULL);
  struct sockaddr_in* socket = malloc(sizeof(struct sockaddr_in));
  LOG_DEBUG("Memory allocate for socket");
  bzero((char *) socket, sizeof(socket));
  socket->sin_family = AF_INET;
  socket->sin_addr.s_addr = INADDR_ANY;
  socket->sin_port = htons(configuration->port);
  LOG_DEBUG("Bind socket to port [%d]", configuration->port);
  if (bind(system->serverFileDescriptor, (struct sockaddr *) socket, sizeof(*socket)) < 0) {
    LOG_ERROR("Fail to bind to port [%d]", configuration->port);
    exit(1);
  }
  LOG_DEBUG("Start listening with queue with length [%d]", configuration->queueLength);
  if(listen(system->serverFileDescriptor, configuration->queueLength) < 0) {
    LOG_ERROR("Fail to listen with queue with length [%d]", configuration->queueLength);
    exit(1);
  }
    LOG_INFO("Server start");
  return socket;
}

