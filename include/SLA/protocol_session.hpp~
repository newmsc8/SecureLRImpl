// protocol_session.hpp
// ~~~~~~~~~~~~~~~
// Generic protocol session/runner classes
//

#ifndef PROTOCOL_SESSION_HPP
#define PROTOCOL_SESSION_HPP

#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
//#include <boost/thread/thread.hpp>
#include <SLA/protocol_message.hpp>

using boost::asio::ip::tcp;

typedef std::deque<protocol_message_ptr> protocol_message_queue;

//----------------------------------------------------------------------

class protocol_party
{
public:
  virtual ~protocol_party() {}
  virtual void deliver(protocol_message_ptr msg) = 0;
  virtual void disconnect() = 0;
};

typedef boost::shared_ptr<protocol_party> protocol_party_ptr;

//----------------------------------------------------------------------

class twoparty_runner
  : public protocol_party
{
public:
  #ifdef _DEBUG
  ~twoparty_runner()
  {
	DEBUG("protocol terminated");      
  }
  #endif

  void register_party(protocol_party_ptr party)
  {
    //DEBUG("party registered");

    party_=party;
    protocol_start();
  }

  void unregister_party()
  {
	DEBUG("party unregistered");      

    party_.reset();
  }

  void set_sid(long sid)
  {
    sid_=sid;
  }

  long sid()
  {
    return sid_;
  }

  void terminate_protocol()
  {
	DEBUG("protocol terminating");      

    party_->disconnect();
//    unregister_party();
  }

  void deliver(protocol_message_ptr msg)
  {
    party_->deliver(msg);
  }

  void send_message(protocol_message_ptr msg)
  {
    //DEBUG("delivering message");
    msg->encode_header();
    party_->deliver(msg);
  }
   
  void disconnect()
  {
	DEBUG("virtual party disconnecting");
  }

  virtual void protocol_start() = 0;
  virtual void receive_msg(protocol_message_ptr msg) = 0;

private:
  protocol_party_ptr party_;
  long sid_;
};

typedef boost::shared_ptr<twoparty_runner> twoparty_runner_ptr;

//----------------------------------------------------------------------

class protocol_session
  : public protocol_party,
    public boost::enable_shared_from_this<protocol_session>
{
public:
  protocol_session(boost::asio::io_service& io_service, twoparty_runner_ptr protocol)
    : socket_(io_service),
      protocol_(protocol)
  {
  }
 
  #ifdef _DEBUG 
  ~protocol_session()
  {
	DEBUG("session terminated");
  }
  #endif

  tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {

	DEBUG("session started"); 
     
    protocol_->register_party(shared_from_this());

    protocol_message_ptr read_msg_(new protocol_message);

    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_->data(), protocol_message::header_length),
        boost::bind(
          &protocol_session::handle_read_header, shared_from_this(),
          read_msg_, boost::asio::placeholders::error));
  }

  void deliver(protocol_message_ptr msg)
  {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
      boost::asio::async_write(socket_,
          boost::asio::buffer(write_msgs_.front()->data(),
            write_msgs_.front()->length()),
          boost::bind(&protocol_session::handle_write, shared_from_this(),
            boost::asio::placeholders::error));
    }
  }

  void disconnect()
  {
    //DEBUG("session disconnecting");
      
    #ifdef _DEBUG
    boost::system::error_code error;

    socket_.shutdown(tcp::socket::shutdown_both, error);
    
    if (error)
    {
      std::cout << "disconnect: shutdown error: " << error.value() << "," <<  error.message() << "\n"; 
    }

    socket_.close(error);
    
    if (error)
    {
      std::cout << "disconnect: close error: " << error.value() << "," <<  error.message() << "\n"; 
    }
    #else
    socket_.shutdown(tcp::socket::shutdown_both);

    socket_.close();
    #endif

  }

private:

  void handle_read_header(protocol_message_ptr read_msg_, const boost::system::error_code& error)
  {
    //DEBUG("message received.");

    if (!error && read_msg_->decode_header())
    {
      boost::asio::async_read(socket_,
          boost::asio::buffer(read_msg_->body(), read_msg_->body_length()),
          boost::bind(&protocol_session::handle_read_body, shared_from_this(),
          read_msg_, boost::asio::placeholders::error));
    }
    else
    {
      DEBUG(error.value() << "," << error.message()); 

      protocol_->unregister_party();
    }
  }

  void handle_read_body(protocol_message_ptr deliver_msg, const boost::system::error_code& error)
  {

    DEBUG("message body: " << deliver_msg->body()); 

    protocol_->receive_msg(deliver_msg);

    protocol_message_ptr read_msg_(new protocol_message);

    if (!error)
    {
      boost::asio::async_read(socket_,
          boost::asio::buffer(read_msg_->data(), protocol_message::header_length),
          boost::bind(&protocol_session::handle_read_header, shared_from_this(),
          read_msg_, boost::asio::placeholders::error));
    }
    else
    {
      DEBUG(error.value() << "," << error.message()); 

      protocol_->unregister_party();
    }
  }

  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      write_msgs_.pop_front();
      if (!write_msgs_.empty())
      {
        boost::asio::async_write(socket_,
            boost::asio::buffer(write_msgs_.front()->data(),
              write_msgs_.front()->length()),
            boost::bind(&protocol_session::handle_write, shared_from_this(),
              boost::asio::placeholders::error));
      }
    }
    else
    {
      DEBUG(error.value() << "," << error.message()); 

      protocol_->unregister_party();
    }
  }

private:
  tcp::socket socket_;
  protocol_message_queue write_msgs_;
  twoparty_runner_ptr protocol_;
};

typedef boost::shared_ptr<protocol_session> protocol_session_ptr;

#endif //PROTOCOL_SESSION_HPP
