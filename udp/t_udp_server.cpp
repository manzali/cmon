#include <iostream>
#include <chrono>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "engine.hpp"
#include "udp/udp_server.hpp"

std::ostream& operator<<(
    std::ostream& os,
    boost::property_tree::ptree const& child) {
  write_json(os, child);
  return os;
}

int main(int argc, char* argv[]) {

  int n_threads = 2;
  engine e(n_threads);

  int port = 7000;
  udp_server s(e.get(), port);

  //std::this_thread::sleep_for(std::chrono::seconds(10));

  while (true) {
    std::cout << s.pop() << std::endl;
  }

  e.stop();

  return 0;
}

