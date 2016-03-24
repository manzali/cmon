#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>

class udp_server : private boost::noncopyable {
 public:
  udp_server(boost::asio::io_service& io_service, int port);

 private:
  void async_receive();
  void handle_receive(
      boost::system::error_code const& error,
      std::size_t bytes_transferred);
  boost::asio::io_service& m_io_service;
  boost::asio::ip::udp::socket m_socket;
  boost::asio::ip::udp::endpoint m_remote_endpoint;
  std::shared_ptr<boost::array<char, 128> > m_recv_buffer;
};

#endif
