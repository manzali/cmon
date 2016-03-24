#include <iostream>
#include <thread>
#include <chrono>

#include <boost/asio.hpp>

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_service io_service;

    boost::asio::ip::udp::resolver resolver(io_service);
    boost::asio::ip::udp::resolver::query query(
        boost::asio::ip::udp::v4(),
        argv[1],
        "7000");
    boost::asio::ip::udp::endpoint receiver_endpoint = *resolver.resolve(query);

    boost::asio::ip::udp::socket socket(io_service);
    socket.open(boost::asio::ip::udp::v4());

    for (int i = 0; i < 1000; ++i) {
      std::string str = std::to_string(i);
      socket.send_to(boost::asio::buffer(str), receiver_endpoint);
      //std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
