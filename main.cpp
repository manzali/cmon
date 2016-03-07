
#include <iostream>

#include <boost/lexical_cast.hpp>

#include "webserver.hpp"

int main(int argc, char* argv[]) {
  try {
    int port = 10001;
    if (argc > 1) {
      port = boost::lexical_cast<int>(argv[1]);
    }
    boost::asio::io_service io_service;
    webserver s(io_service, port);
    io_service.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}

