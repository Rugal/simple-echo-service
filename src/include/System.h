#ifndef SYSTEMH
#define SYSTEMH

#include <netinet/in.h>

#include "Configuration.h"
#include "System.h"

#define BUFFER_SIZE 1024

/**
 * System runtime parameter.
 */
typedef struct System {
  int serverFileDescriptor;
  int clientFileDescriptor;
  struct sockaddr_in* serverSocket;
  struct sockaddr_in* clientSocket;
} System;

/**
 * Create and setup server System object with provided configuration.
 */
System* createServer(Configuration*);

/**
 * Create and setup client System object with provided configuration.
 */
System* createClient(Configuration* configuration);

/**
 * Free system memory and release relevant resource.
 */
void freeSystem(System* );

#endif SYSTEMH
