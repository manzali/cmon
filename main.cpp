#include "otpc-conn.hpp"

class server : private boost::noncopyable {
 public:
  server(ba::io_service& io_service, int port);

 private:
  void handle_accept(const boost::system::error_code& e);

  ba::io_service& io_service_;
  ba::ip::tcp::acceptor acceptor_;
  connection::pointer new_connection_;
};

server::server(ba::io_service& io_service, int port)
    : io_service_(io_service),
      acceptor_(io_service_, ba::ip::tcp::endpoint(ba::ip::tcp::v4(), port)),
      new_connection_(connection::create(io_service_)) {
  acceptor_.async_accept(
      new_connection_->socket(),
      boost::bind(&server::handle_accept, this, ba::placeholders::error));
}

void server::handle_accept(const boost::system::error_code& e) {
  if (!e) {
    boost::thread t(boost::bind(&connection::run, new_connection_));
    new_connection_ = connection::create(io_service_);
    acceptor_.async_accept(
        new_connection_->socket(),
        boost::bind(&server::handle_accept, this, ba::placeholders::error));
  }
}

int main(int argc, char* argv[]) {
  try {
    int port = 10001;
    if (argc > 1){
      port = boost::lexical_cast<int>(argv[1]);
    }
    ba::io_service io_service;
    server s(io_service, port);
    io_service.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}

