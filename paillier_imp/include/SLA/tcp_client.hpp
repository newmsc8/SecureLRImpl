#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <SLA/protocol_session.hpp>

using boost::asio::ip::tcp;

class tcp_client
{
public:
  tcp_client(boost::asio::io_service& io_service,
      tcp::resolver::iterator endpoint_iterator, twoparty_runner_ptr protocol)
    : io_service_(io_service),
      endpoint_iterator_(endpoint_iterator),
      protocol_(protocol)
  {
    start_connect();
  }

  ~tcp_client()
  {
  }

  void start_connect()
  {
    protocol_session_ptr new_session(new protocol_session(io_service_,protocol_));  
    boost::asio::async_connect(new_session->socket(), endpoint_iterator_,
        boost::bind(&tcp_client::handle_connect, this, new_session,
          boost::asio::placeholders::error));
  }

  void handle_connect(protocol_session_ptr session,
      const boost::system::error_code& error)
  {

    if (!error)
    {
      session->start();
    }
    else
    {
      std::cout << __PRETTY_FUNCTION__ << error.value() << "," <<  error.message() << "\n";
    }

  } 


private:
  boost::asio::io_service& io_service_;
  tcp::resolver::iterator endpoint_iterator_;
  twoparty_runner_ptr protocol_;
};

#endif //TCP_CLIENT_HPP
