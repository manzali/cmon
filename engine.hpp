#ifndef ENGINE_H
#define ENGINE_H

#include <thread>
#include <chrono>

#include <boost/asio.hpp>

class engine : private boost::noncopyable {

 public:
  engine(int n_threads)
      : m_io_service(),
        m_work(m_io_service),
        m_threads(n_threads) {
    assert(n_threads > 0 && "Required at least 1 thread");
    for (auto& th : m_threads) {
      th = std::thread([&]() {m_io_service.run();});
    }
  }

  void post() {

  }

  void stop() {
    m_io_service.stop();
    for (auto& th : m_threads) {
      if (th.joinable()) {
        th.join();
      }
    }
  }

  ~engine() {
    stop();
  }

  boost::asio::io_service& get() {
    return m_io_service;
  }

 private:
  boost::asio::io_service m_io_service;
  boost::asio::io_service::work m_work;
  std::vector<std::thread> m_threads;
};

#endif
