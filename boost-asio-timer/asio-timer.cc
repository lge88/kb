#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

void syncWaitExample() {
  boost::asio::io_service io;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(2));
  cout << "hello\n";
  t.wait();
  cout << "world\n";
}

void callback(const boost::system::error_code& e) {
  cout << "world\n";
}

void asyncWaitExample() {
  boost::asio::io_service io;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(2));
  t.async_wait(&callback);
  cout << "hello\n";
  io.run();
}

int main(int argc, char* argv[]) {

  asyncWaitExample();

  return 0;
}
