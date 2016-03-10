#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <boost/asio.hpp>

class webserver : private boost::noncopyable {
 public:
  webserver(boost::asio::io_service& io_service, int port);

 private:
  void async_accept();
  void handle_accept(boost::system::error_code const& err);
  boost::asio::io_service& m_io_service;
  boost::asio::ip::tcp::acceptor m_acceptor;
  std::shared_ptr<boost::asio::ip::tcp::socket> m_new_socket;
};

#endif
