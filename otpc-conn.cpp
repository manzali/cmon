#include "otpc-conn.hpp"

const std::string connection::message_ =
    "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n"
        "<html><head><title>test</title>"
        "</head><body><h1>Test</h1><p>This is a test!</p></body></html>";

connection::connection(ba::io_service& io_service)
    : io_service_(io_service),
      socket_(io_service) {
}

void connection::run() {
  try {
    ba::read_until(socket_, buf, boost::regex("\r\n\r\n"));
    ba::write(socket_, ba::buffer(message_), ba::transfer_all());
    socket_.close();
  } catch (std::exception& x) {
    std::cerr << "Exception: " << x.what() << std::endl;
  }
}

