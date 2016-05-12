#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

#include <array>

#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>

#include "shared_queue/shared_queue.hpp"

namespace {
size_t const buffer_size = 64 * 1024;
}

class udp_server {

 public:

  udp_server(boost::asio::io_service& io_service, int port);
  boost::property_tree::ptree pop();

 private:

  void async_receive();
  void handle_receive(
      boost::system::error_code const& error,
      std::size_t bytes_transferred);
  void parse(std::string str);

  boost::asio::ip::udp::socket m_socket;
  std::array<char, buffer_size> m_recv_buffer;
  shared_queue<boost::property_tree::ptree> m_queue;
};

#endif
