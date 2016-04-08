#include <iostream>
#include <chrono>

#include "engine.hpp"
#include "webserver.hpp"

int main(int argc, char* argv[]) {

  int n_threads = 2;
  engine e(n_threads);

  int port = 10001;
  webserver s(e.get(), port);

  std::this_thread::sleep_for(std::chrono::seconds(10));

  e.stop();

  return 0;
}

