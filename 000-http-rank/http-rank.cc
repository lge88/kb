#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char* argv[]) {
  const int port = 8888;
  int sockFd, newSockFd;

  socklen_t clientLen;
  char buffer[256];

  sockaddr_in serverAddress, clientAddress;
  int n;

  sockFd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockFd < 0)
    error("Error opening socket.");

  bzero((char *)&serverAddress, sizeof(serverAddress));

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(port);

  if (bind(sockFd, (sockaddr*) &serverAddress, sizeof(serverAddress)) < 0)
    error("Error on binding.");

  listen(sockFd, 5);
  clientLen = sizeof(clientAddress);
  newSockFd = accept(sockFd, (sockaddr *)&clientAddress, &clientLen);
  if (newSockFd < 0)
    error("Error on accept.");

  bzero(buffer, 256);
  n = read(newSockFd, buffer, 255);
  if (n < 0) error("Error reading from socket");

  std::cout << "Here is the message: " << buffer << "\n";

  n = write(newSockFd, "I got you message", 18);
  if (n < 0) error("Error writing to socket.");

  close(newSockFd);
  close(sockFd);
  return 0;
}
