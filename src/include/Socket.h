#ifndef SOCKETH
#define SOCKETH

#include <netinet/in.h>

#include "Configuration.h"
#include "System.h"

/**
 * Create file descriptor for socket.
 */
int createSocketFileDescriptor();

/**
 * Create socket object and bind it to configuration specified host and port.
 * Setup listening queue etc.,
 */
struct sockaddr_in* createServerSocket(const System*, const Configuration*);

/**
 * Connect client side to server side with provided configuration.
 */
struct sockaddr_in* connectServer(const System*, Configuration*) ;

#endif SOCKETH
