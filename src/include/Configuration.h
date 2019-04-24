#ifndef CONFIGURATIONH
#define CONFIGURATIONH

#define HOST_NAME_LENGTH 1024

/**
 * Initialization parameter for bootstraping the system.
 */
typedef struct Configuration {
  int port;
  int queueLength;
  char hostname[HOST_NAME_LENGTH];
} Configuration;

#endif CONFIGURATIONH

