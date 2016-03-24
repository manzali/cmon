#include "udp_server.hpp"

#include <iostream>

#include <boost/bind.hpp>

void print_buffer(
    std::shared_ptr<boost::array<char, 128> > recv_buffer,
    std::size_t bytes_transferred) {
  std::cout.write(recv_buffer->data(), bytes_transferred);
  std::cout << std::endl;
}

udp_server::udp_server(boost::asio::io_service& io_service, int port)
    : m_io_service(io_service),
      m_socket(
          io_service,
          boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)) {
  async_receive();
}

void udp_server::async_receive() {
  m_recv_buffer.reset(new boost::array<char, 128>());
  m_socket.async_receive_from(
      boost::asio::buffer(*m_recv_buffer),
      m_remote_endpoint,
      boost::bind(
          &udp_server::handle_receive,
          this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
}

void udp_server::handle_receive(
    boost::system::error_code const& error,
    std::size_t bytes_transferred) {
  if (!error) {
    m_io_service.post(
        boost::bind(&print_buffer, m_recv_buffer, bytes_transferred));
  } else {
    std::cerr << error.message() << std::endl;
  }
  async_receive();
}
