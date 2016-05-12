#include <thread>

#include <boost/detail/lightweight_test.hpp>

#include "shared_queue/shared_queue.hpp"

int main() {

  {
    shared_queue<int> queue;
    int const n = 1000;

    std::thread th1([&]() {
      for (int i = 0; i < n; ++i) {
        queue.push(i);
      }
    });

    std::thread th2([&]() {
      int counter = 0;
      while(++counter < n) {
        int t = queue.pop();
        BOOST_TEST_EQ(counter, t + 1);
      }
      BOOST_TEST_EQ(counter, n);
    });

    th1.join();
    th2.join();
  }

  {
    shared_queue<int> queue;
    int const n = 1000;

    std::thread th1([&]() {
      boost::optional<int> opt;
      int counter = 0;
      while(counter != n) {
        opt = queue.pop_no_wait();
        if(opt) {
          BOOST_TEST_EQ(counter, opt.get());
          ++counter;
        }
      }
      BOOST_TEST_EQ(counter, n);
    });

    std::thread th2([&]() {
      for (int i = 0; i < n; ++i) {
        queue.push(i);
      }
    });

    th1.join();
    th2.join();
  }

  boost::report_errors();
}
