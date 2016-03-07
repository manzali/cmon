#include "webserver.hpp"

#include <string>

#include <boost/regex.hpp>

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include <boost/algorithm/string.hpp>

connection::connection(boost::asio::io_service& io_service)
    : m_socket(io_service) {
}

void connection::run() {
  try {
    boost::asio::streambuf buffer;
    boost::asio::read_until(m_socket, buffer, boost::regex("\r\n\r\n"));

    std::istream is(&buffer);
        std::string line;
        std::getline(is, line);
    std::cout << line << std::endl;

    std::string const message =
        "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n"
            "<html><head><title>test</title>"
            "</head><body><h1>Test</h1><p>This is a test!</p></body></html>";
    boost::asio::write(m_socket, boost::asio::buffer(message), boost::asio::transfer_all());
    m_socket.close();
  } catch (std::exception& ex) {
    std::cerr << "Exception: " << ex.what() << std::endl;
  }
}

webserver::webserver(boost::asio::io_service& io_service, int port)
    : m_io_service(io_service),
      m_acceptor(
          m_io_service,
          boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      m_new_conn(
          boost::make_shared < connection > (boost::ref(m_io_service))) {
  m_acceptor.async_accept(
      m_new_conn->socket(),
      boost::bind(&webserver::handle_accept, this,
                  boost::asio::placeholders::error));
}

void webserver::handle_accept(boost::system::error_code const& err) {
  if (!err) {
    boost::thread t(boost::bind(&connection::run, m_new_conn));
    m_new_conn = boost::make_shared < connection
        > (boost::ref(m_io_service));
    m_acceptor.async_accept(
        m_new_conn->socket(),
        boost::bind(&webserver::handle_accept, this,
                    boost::asio::placeholders::error));
  }
}
