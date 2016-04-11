#include "udp_server.hpp"

#include <iostream>
#include <string>

#include <boost/bind.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace {
boost::asio::ip::udp::endpoint remote_endpoint;
}

udp_server::udp_server(boost::asio::io_service& io_service, int port)
    : m_socket(
        io_service,
        boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)) {
  async_receive();
}

void udp_server::async_receive() {
  m_socket.async_receive_from(
      boost::asio::buffer(m_recv_buffer),
      remote_endpoint,
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
    m_socket.get_io_service().post(
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
    m_queue.push(child);
  } catch (boost::property_tree::json_parser::json_parser_error& error) {
    std::cerr << error.message() << std::endl;
  }
}

boost::property_tree::ptree udp_server::pop() {
  return m_queue.pop();
}
