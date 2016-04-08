#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

#include <array>

#include <boost/asio.hpp>
#include <boost/core/noncopyable.hpp>

namespace {
size_t const buffer_size = 512;
}

class udp_server : private boost::noncopyable {

 public:

  udp_server(boost::asio::io_service& io_service, int port);

 private:

  void async_receive();
  void handle_receive(
      boost::system::error_code const& error,
      std::size_t bytes_transferred);
  void parse(std::string str);

  boost::asio::io_service& m_io_service;
  boost::asio::ip::udp::socket m_socket;
  boost::asio::ip::udp::endpoint m_remote_endpoint;
  std::array<char, buffer_size> m_recv_buffer;

};

#endif
