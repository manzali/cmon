#include "udp_server.hpp"

#include <iostream>
#include <string>

#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

std::ostream& operator<<(
    std::ostream& os,
    boost::property_tree::ptree const& child) {
  write_json(os, child);
  return os;
}

udp_server::udp_server(boost::asio::io_service& io_service, int port)
    : m_io_service(io_service),
      m_socket(
          io_service,
          boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)) {
  async_receive();
}

void udp_server::async_receive() {
  m_socket.async_receive_from(
      boost::asio::buffer(m_recv_buffer),
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
        boost::bind(
            &udp_server::parse,
            this,
            std::string(m_recv_buffer.data(), bytes_transferred)));
  } else {
    std::cerr << error.message() << std::endl;
  }
  async_receive();
}

void udp_server::parse(std::string str) {
  boost::property_tree::ptree child;
  try {
    std::istringstream iss(str);
    read_json(iss, child);
    std::cout << child << std::endl;
  } catch (boost::property_tree::json_parser::json_parser_error& error) {
    //std::cerr << error.message() << std::endl;
  }
}
