#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "Configuration.h"
#include "System.h"
#include "log4c.h"
#include "socket.h"

//Set overall log level
int log4c_level = LOG4C_ALL;

int main() {
  Configuration configuration;
  configuration.port = 8080;
  configuration.queueLength = 5;

  struct sockaddr_in serv_addr;

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    LOG_ERROR("Fail to create socket file descriptor");
    exit(1);
  }
  struct hostent *server = gethostbyname("localhost");
  if (server == NULL) {
    LOG_ERROR("Fail to get host by server name");
    exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
      (char *)&serv_addr.sin_addr.s_addr,
      server->h_length);
  serv_addr.sin_port = htons(configuration.port);
  if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
    LOG_ERROR("Fail to connect to server");
    exit(1);
  }
  printf("Please enter the message: ");
  char buffer[256];
  bzero(buffer,256);
  fgets(buffer,255,stdin);
  int n = write(sockfd,buffer,strlen(buffer));
  if (n < 0)
    LOG_ERROR("Fail to write to server");

  return 0;
}
