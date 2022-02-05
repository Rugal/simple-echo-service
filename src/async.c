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
#include "Configuration.h"
#include "StringUtility.h"
#include "System.h"
#include "log4c.h"
#include "Socket.h"

//Set overall log level
int log4c_level = LOG4C_ALL;

static void readHandler(struct pollfd fds[], int index, int* size)
{
  struct pollfd current = fds[index];
  char buffer[BUFFER_SIZE];
  bzero(buffer, BUFFER_SIZE);
  if (read(current.fd, buffer, BUFFER_SIZE - 1) > 0) {
    LOG_INFO("[%d]: [%s]", current.fd, trim(buffer));
  }
  else {
    // connection closed
    fds[index] = fds[*size - 1];
    --(*size);
    LOG_INFO("[%d]: Connection close", current.fd);
  }
}

static int connectionHandler(struct pollfd fds[], int* size) {
  struct sockaddr_in client;
  int clientSize = sizeof(client);

  int clientFileDescriptor = accept(fds[0].fd, (struct sockaddr*)&client, &clientSize);
  LOG_INFO("Get connection with file descriptor [%d]", clientFileDescriptor);
  fds[*size].fd = clientFileDescriptor;
  fds[*size].events = POLLIN;
  LOG_DEBUG("Advance FD, Now we have [%d] FDs", ++(*size));

  return clientFileDescriptor;
}

/**
 * This is a chat room server where people can join/leave this room and also broadcast/target chat.
 */
int main(int argc, char** argv)
{
  Configuration* configuration = parseConfiguration(argc, argv);
  System* system = createServer(configuration);
  ArrayList* list = createArrayList();

  //service section begin
  //start listening
  LOG_INFO("Start polling inbound request");
  struct pollfd fds[configuration->queueLength];
  memset(fds, 0, sizeof(struct pollfd) * configuration->queueLength);
  fds[0].fd = system->serverFileDescriptor;
  fds[0].events = POLLIN;
  int available = 1;

  for (int poll_count = poll(fds, available, 2000); poll_count != -1; poll_count = poll(fds, available, -1)) {
    // poll get something
    LOG_DEBUG("Poll return [%d]", poll_count);
    for (int i = 0; poll_count > 0 && i < available; i++) {
      LOG_DEBUG("Check FD [%d]@[%d]", fds[i].fd, i);
      // Check if someone's ready to read
      if ((fds[i].revents & POLLIN)) {
        LOG_DEBUG("FD [%d]@[%d] has something to talk to us", fds[i].fd, i);
        if (fds[i].fd == system->serverFileDescriptor) {
          // connection event
          LOG_INFO("New connection incoming");
          connectionHandler(fds, &available);
        }
        else {
          // read event
          LOG_INFO("New message incoming");
          readHandler(fds, i, &available);
        }
      }
    }
    LOG_DEBUG("Poll again");
  }

  freeArrayList(list);
  freeConfiguration(configuration);
  freeSystem(system);

  LOG_ERROR("Fail to poll client connection [%d]", errno);
  return 1;
}
