#ifndef SYSTEMH
#define SYSTEMH

#include <netinet/in.h>

/**
 * System runtime parameter.
 */
typedef struct System {
  int serverFileDescriptor;
  int clientFileDescriptor;
  struct sockaddr_in* serverSocket;
  struct sockaddr_in* clientSocket;
} System;

#endif SYSTEMH
