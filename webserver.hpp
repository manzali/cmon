#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <memory>

#include <boost/asio.hpp>

class webserver : private boost::noncopyable {
 public:
  webserver(boost::asio::io_service& io_service, int port);

 private:

  class connection {

   public:
    connection(boost::asio::io_service& io_service);
    void run();
    boost::asio::ip::tcp::socket& socket() {
      return m_socket;
    }

   private:
    boost::asio::ip::tcp::socket m_socket;
  };

  void handle_accept(boost::system::error_code const& err);
  boost::asio::io_service& m_io_service;
  boost::asio::ip::tcp::acceptor m_acceptor;
  std::shared_ptr<connection> m_new_conn;
};

#endif
