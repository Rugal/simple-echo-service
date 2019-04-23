#ifndef SOCKETH
#define SOCKETH

#include <netinet/in.h>

#include "Configuration.h"
#include "System.h"

int createFileDescriptor();
struct sockaddr_in* createSocket(const System *system, const Configuration* configuration);

#endif SOCKETH

