#ifndef SHARED_QUEUE_HPP
#define SHARED_QUEUE_HPP

#include <queue>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <boost/optional.hpp>
#include <boost/core/noncopyable.hpp>

template<typename T>
class shared_queue : private boost::noncopyable {

 public:

  T pop() {
    std::unique_lock<std::mutex> mlock(m_mutex);
    while (m_queue.empty()) {
      m_cond.wait(mlock);
    }
    T item(m_queue.front());
    m_queue.pop();
    return item;
  }

  boost::optional<T> pop_no_wait() {
    std::unique_lock<std::mutex> mlock(m_mutex);
    boost::optional<T> opt;
    if (m_queue.empty()) {
      return opt;
    }
    opt = m_queue.front();
    m_queue.pop();
    return opt;
  }

  boost::optional<T> pop_with_timeout(std::chrono::milliseconds ms) {
    std::unique_lock<std::mutex> mlock(m_mutex);
    if (m_queue.empty()) {
      m_cond.wait_for(mlock, ms);
    }
    boost::optional<T> opt;
    if (m_queue.empty()) {
      return opt;
    }
    opt = m_queue.front();
    m_queue.pop();
    return opt;
  }

  void push(T const& item) {
    std::unique_lock<std::mutex> mlock(m_mutex);
    m_queue.push(item);
    m_cond.notify_one();
  }

 private:

  std::queue<T> m_queue;
  std::mutex m_mutex;
  std::condition_variable m_cond;
};

#endif
