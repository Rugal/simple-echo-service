#ifndef SYSTEMH
#define SYSTEMH

#include <netinet/in.h>

/**
 * System runtime parameter.
 */
typedef struct System {
  int serverFileDescriptor;
  struct sockaddr_in* serverSocket;
} System;

#endif SYSTEMH

