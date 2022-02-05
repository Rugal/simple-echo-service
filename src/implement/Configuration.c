#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

#include "Configuration.h"
#include "System.h"
#include "log4c.h"

Configuration* parseConfiguration(int argc, char **argv) {
  Configuration *c = malloc(sizeof(Configuration));
  bzero((char *) c, sizeof(Configuration));
  // set default value
  c->port = 8080;
  c->queueLength = 5;
  strcpy(c->hostname, "localhost");
  // parse input parameter and override
  for (int opt; (opt = getopt(argc, argv, "h:p:q:")) != -1;) {
    LOG_TRACE("Process option [%c]", opt);
    switch(opt) {
      case 'q':
        c->queueLength = atoi(optarg);
        LOG_DEBUG("Set connection queue length to [%d]", c->queueLength);
        break;
      case 'h':
        strcpy(c->hostname, optarg);
        LOG_DEBUG("Set server host to [%s]", c->hostname);
        break;
      case 'p':
        c->port = atoi(optarg);
        LOG_DEBUG("Set server port to [%d]", c->port);
        break;
      case '?':
        LOG_INFO("unknown option: [%c]", optopt);
        break;
    }
  }
  return c;
}

void freeConfiguration(Configuration* c) {
  assert(c != NULL);
  LOG_TRACE("Free configuration object");
  free(c);
}
