#include <iostream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class udp_server {
 public:
  udp_server(boost::asio::io_service& io_service, int port)
      : socket_(io_service, udp::endpoint(udp::v4(), port)) {
    post_receive();
  }

 private:
  void post_receive() {
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_),
        remote_endpoint_,
        boost::bind(&udp_server::handle_receive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
  }

  void handle_receive(const boost::system::error_code& error,
                      std::size_t bytes_transferred) {
    if (!error) {
      std::cout.write(recv_buffer_.data(), bytes_transferred);
      std::cout << std::endl;
    } else {
      std::cerr << error.message() << std::endl;
    }
    post_receive();
  }

  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  boost::array<char, 128> recv_buffer_;
};

int main() {
  try {
    boost::asio::io_service io_service;
    udp_server server(io_service, 7000);
    io_service.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
