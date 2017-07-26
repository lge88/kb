#include <iostream>
#include <string>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "Msg.hh"

class Sender {
 public:
  Sender();
  ~Sender();

  template<typename M>
  void send(const M& msg, const std::string& ip, int port);

 private:
  int fd_;
};

Sender::Sender() {
  fd_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd_ < 0) throw std::runtime_error("Can not create socket.");
}

Sender::~Sender() {
  close(fd_);
}

template<typename M>
void Sender::send(const M& msg, const std::string& ip, int port) {
  std::vector<iovec> iovecList;
  msg.serialize(iovecList);

  sockaddr_in dest;
  dest.sin_family = AF_INET;
  dest.sin_addr.s_addr = inet_addr(ip.c_str());
  dest.sin_port = htons(port);

  msghdr msgInternal;
  msgInternal.msg_name = static_cast<void *>(&dest);
  msgInternal.msg_namelen = sizeof(dest);
  msgInternal.msg_iov = iovecList.data();
  msgInternal.msg_iovlen = iovecList.size();
  msgInternal.msg_control = nullptr;
  msgInternal.msg_controllen = 0;
  msgInternal.msg_flags = 0;

  sendmsg(fd_, &msgInternal, 0);
}

int main(int argc, char* argv[]) {

  Sender sender;

  MsgGet m1 = { argv[1] };
  sender.send(m1, "127.0.0.1", 9999);

  return 0;
}
