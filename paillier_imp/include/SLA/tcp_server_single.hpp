//
// tcp_server.cpp
// ~~~~~~~~~~~~~~~
//
//

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <SLA/protocol_session.hpp>

using boost::asio::ip::tcp;

class tcp_server
{
public:
      tcp_server(boost::asio::io_service& io_service,
      const tcp::endpoint& endpoint,
      twoparty_runner_ptr protocol)
    : io_service_(io_service),
      acceptor_(io_service, endpoint),
      protocol_(protocol)
  {
    start_accept();
  }

  void start_accept()
  {
    protocol_session_ptr new_session(new protocol_session(io_service_,protocol_));
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }

  void handle_accept(protocol_session_ptr session,
      const boost::system::error_code& error)
  { 

    if (!error)
    {
      session->start();
    }
    else
    {
      std::cout << error.value() << "," <<  error.message() << "\n";
    }
  }

private:
  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
  twoparty_runner_ptr protocol_;
};

