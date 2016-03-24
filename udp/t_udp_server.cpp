#include <iostream>
#include <chrono>

#include "engine.hpp"
#include "udp/udp_server.hpp"

int main(int argc, char* argv[]) {

  int n_threads = 1;
  engine e(n_threads);

  int port = 7000;
  udp_server s(e.get(), port);

  std::this_thread::sleep_for(std::chrono::seconds(10));

  e.stop();

  return 0;
}

