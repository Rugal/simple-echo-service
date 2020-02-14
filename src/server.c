#include <netinet/in.h>
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

typedef struct ThreadData
{
  int fd;
  pthread_t thread;
} ThreadData;

void clientHandler(void *input)
{
  ThreadData *data = (ThreadData *)input;
  char buffer[BUFFER_SIZE];
  for (bzero(buffer, BUFFER_SIZE);
       read(data->fd, buffer, BUFFER_SIZE - 1) > 0;
       bzero(buffer, BUFFER_SIZE))
  {
    LOG_INFO("[%d]: [%s]", data->fd, trim(buffer));
    sleep(1);
  }
  LOG_INFO("[%d]: disconnect", data->fd);
}

/**
 * This is a chat room server where people can join/leave this room and also broadcast/target chat.
 */
int main(int argc, char **argv)
{
  Configuration *configuration = parseConfiguration(argc, argv);
  System *system = createServer(configuration);
  ArrayList *list = createArrayList();

  //service section begin
  struct sockaddr_in client;
  int clientSize = sizeof(client);
  //start listening
  LOG_INFO("Start accepting inbound request");
  for (int clientFileDescriptor;
       (clientFileDescriptor = accept(system->serverFileDescriptor,
                                      (struct sockaddr *)&client,
                                      &clientSize)) >= 0;)
  {
    LOG_INFO("Get connection with file descriptor [%d]", clientFileDescriptor);
    ThreadData *data = malloc(sizeof(ThreadData));
    add(list, data);
    data->fd = clientFileDescriptor;
    pthread_create(&data->thread, NULL, clientHandler, data);
  }
  LOG_ERROR("Fail to accept client connection");

  /*
    Clean up everything
  */
  for (int i = 0; i < size(list); ++i)
  {
    ThreadData *d = (ThreadData *)get(list, i);
    pthread_join(d->thread, NULL);
    free(d);
  }
  freeArrayList(list);

  freeConfiguration(configuration);
  freeSystem(system);
  return 0;
}
