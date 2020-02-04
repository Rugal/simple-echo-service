#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>

#include "Configuration.h"
#include "System.h"
#include "log4c.h"
#include "Socket.h"

int createSocketFileDescriptor() {
  const int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    LOG_ERROR("Fail to create file descriptor");
    exit(1);
  }
  LOG_DEBUG("Create socket file descriptor [%d]", fd);
  return fd;
}

struct sockaddr_in* createServerSocket(const System *system, const Configuration* configuration) {
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
  LOG_DEBUG("Start listening with queue length [%d]", configuration->queueLength);
  if(listen(system->serverFileDescriptor, configuration->queueLength) < 0) {
    LOG_ERROR("Fail to listen with queue with length [%d]", configuration->queueLength);
    exit(1);
  }
  return socket;
}

struct sockaddr_in* connectServer(const System *system, Configuration* configuration) {
  assert(configuration != NULL);
  assert(system != NULL);
  LOG_DEBUG("Try to resolve host [%s]", configuration->hostname);
  struct hostent *server = gethostbyname(configuration->hostname);
  if (server == NULL) {
    LOG_ERROR("Fail to get host by server name");
    exit(1);
  }

  LOG_DEBUG("Create client socket");
  struct sockaddr_in* serverAddress = malloc(sizeof(struct sockaddr_in));
  bzero(serverAddress, sizeof(struct sockaddr_in));

  LOG_DEBUG("Setup connection parameter");
  serverAddress->sin_family = AF_INET;
  serverAddress->sin_addr = *((struct in_addr *)server->h_addr);
  serverAddress->sin_port = htons(configuration->port);

  LOG_DEBUG("Try to connect to server");
  if (connect(system->clientFileDescriptor,
              (struct sockaddr *)serverAddress,
              sizeof(struct sockaddr)) < 0) {
    LOG_ERROR("Fail to connect to server");
    exit(1);
  }
  LOG_DEBUG("Connected to server [%s]:[%d]", configuration->hostname, configuration->port);
  return serverAddress;
}
