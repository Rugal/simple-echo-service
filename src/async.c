#include <errno.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "ArrayList.h"
#include "Asynchronization.h"
#include "Configuration.h"
#include "StringUtility.h"
#include "System.h"
#include "log4c.h"
#include "Socket.h"

//Set overall log level
int log4c_level = LOG4C_ALL;

static void readHandler(FileDescriptorPool* pool, int index)
{
  char buffer[BUFFER_SIZE];
  bzero(buffer, BUFFER_SIZE);

  struct pollfd current = pool->fds[index];
  if (read(current.fd, buffer, BUFFER_SIZE - 1) > 0) {
    LOG_INFO("[%d]: [%s]", current.fd, trim(buffer));
    return;
  }
  // connection closed
  removeFromPool(pool, index);
  LOG_INFO("[%d]: Connection close", current.fd);
}

static struct pollfd* connectionHandler(FileDescriptorPool* pool) {
  struct sockaddr_in client;
  int clientSize = sizeof(client);

  int clientFileDescriptor = accept(pool->fds[0].fd, (struct sockaddr*)&client, &clientSize);
  LOG_INFO("Get connection with file descriptor [%d]", clientFileDescriptor);
  struct pollfd* pfd = addToPool(pool, clientFileDescriptor);
  pfd->events = POLLIN;
  return pfd;
}

/**
 * This is a chat room server where people can join/leave this room and also broadcast/target chat.
 */
int main(int argc, char** argv)
{
  Configuration* configuration = parseConfiguration(argc, argv);
  System* system = createServer(configuration);
  ArrayList* list = createArrayList();
  FileDescriptorPool* pool = createFileDescriptorPool(8);

  //service section begin
  //start listening
  LOG_INFO("Start polling inbound request");
  struct pollfd* pfd = addToPool(pool, system->serverFileDescriptor);
  pfd->events = POLLIN;

  for (int changes = poll(pool->fds, pool->size, 2000);
    changes != -1;
    changes = poll(pool->fds, pool->size, 2000)) {
    // poll get something
    LOG_DEBUG("Poll return [%d]", changes);
    for (int i = 0; changes > 0 && i < pool->size; i++) {
      LOG_DEBUG("Check FD [%d]@[%d]", pool->fds[i].fd, i);
      // Check if someone's ready to read
      if ((pool->fds[i].revents & POLLIN)) {
        LOG_DEBUG("FD [%d]@[%d] has something to talk to us", pool->fds[i].fd, i);
        if (pool->fds[i].fd == system->serverFileDescriptor) {
          // connection event
          LOG_INFO("New connection incoming");
          connectionHandler(pool);
        }
        else {
          // read event
          LOG_INFO("New message incoming");
          readHandler(pool, i);
        }
      }
    }
    LOG_DEBUG("Poll again");
  }

  freeArrayList(list);
  freeConfiguration(configuration);
  freeSystem(system);
  freeFileDescriptorPool(pool);

  LOG_ERROR("Fail to poll client connection [%d]", errno);
  return 1;
}
