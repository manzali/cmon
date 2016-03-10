#include "webserver.hpp"

#include <string>
#include <iostream>

#include <boost/regex.hpp>
#include <boost/bind.hpp>

void handle_connection(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
  try {
    boost::asio::streambuf buffer;
    boost::asio::read_until(*socket, buffer, boost::regex("\r\n\r\n"));

    std::istream is(&buffer);
    std::string line;
    std::getline(is, line);
    std::cout << line << std::endl;

    std::string const message =
        "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n"
            "<html><head><title>test</title>"
            "</head><body><h1>Test</h1><p>This is a test!</p></body></html>";
    boost::asio::write(*socket, boost::asio::buffer(message),
                       boost::asio::transfer_all());
    socket->close();
  } catch (std::exception& ex) {
    std::cerr << "Exception: " << ex.what() << std::endl;
  }
}

webserver::webserver(boost::asio::io_service& io_service, int port)
    : m_io_service(io_service),
      m_acceptor(
          m_io_service,
          boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
  async_accept();
}

void webserver::async_accept() {
  m_new_socket = std::make_shared<boost::asio::ip::tcp::socket>(
      std::ref(m_io_service));
  m_acceptor.async_accept(
      *m_new_socket,
      boost::bind(&webserver::handle_accept, this,
                  boost::asio::placeholders::error));
}

void webserver::handle_accept(boost::system::error_code const& err) {
  if (!err) {
    m_io_service.post(boost::bind(&handle_connection, m_new_socket));
    async_accept();
  } else {
    std::cerr << "Unhandled error in handle_accept\n";
  }
}
