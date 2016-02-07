#ifndef OTPC_CONN_H
#define OTPC_CONN_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/regex.hpp>

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include <iostream>
#include <string>

namespace ba = boost::asio;
namespace bs = boost::system;

typedef boost::shared_ptr<ba::ip::tcp::socket> socket_ptr;
typedef boost::shared_ptr<ba::io_service> io_service_ptr;

class connection {

 public:
  typedef boost::shared_ptr<connection> pointer;

  connection(ba::io_service& io_service);

  static pointer create(ba::io_service& io_service) {
    return boost::make_shared<connection>(boost::ref(io_service));
  }

  ba::ip::tcp::socket& socket() {
    return socket_;
  }
  void run();

 private:
  ba::io_service& io_service_;
  ba::ip::tcp::socket socket_;
  ba::streambuf buf;
  const static std::string message_;
};

#endif
