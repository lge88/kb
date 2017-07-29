#include <string>
#include <cstring>
#include <iostream>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  std::cout << "fd: " << fd << "\n";

  int port = 9999;
  sockaddr_in host;
  host.sin_family = AF_INET;
  host.sin_addr.s_addr = htonl(INADDR_ANY);
  host.sin_port = htons(port);

  if (bind(fd, (sockaddr *) &host, sizeof(sockaddr_in)) < 0) {
    std::cout << "bind failed.\n";
    std::cout << "errno: " << errno << "\n";
    std::cout << "EACCES: " << EACCES << '\n';
    std::cout << "EADDRINUSE: " << EADDRINUSE << '\n';
    std::cout << "EBADF: " << EBADF << '\n';
    std::cout << "EINVAL: " << EINVAL << '\n';
    std::cout << "ENOTSOCK: " << ENOTSOCK << '\n';
    return 1;
  }

  int type;
  char buf[1024];
  memset((char *)&buf, 0, sizeof(buf));
  iovec vecs[2] = {
    { (void *)&type,  1U },
    { (void *)&buf, sizeof(buf) }
  };

  msghdr msg;
  memset((char *)&msg, 0, sizeof(msg));
  msg.msg_iovlen = 2;
  msg.msg_iov = &vecs[0];

  int nBytes = recvmsg(fd, &msg, 0);
  while (nBytes >= 0) {
    std::cout << "nBytes: " << nBytes << "\n";
    std::cout << "msg type: " << type << "\n";
    char* p = (char *) msg.msg_iov[1].iov_base;
    std::cout << "data: " << std::string(p, p + nBytes - 1) << "\n\n";
    nBytes = recvmsg(fd, &msg, 0);
  }

  std::cout << "recv failed.\n";
  return 1;
}
