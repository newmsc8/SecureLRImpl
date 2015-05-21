//
// protocol_message.hpp
// ~~~~~~~~~~~~~~~~
//

#ifndef PROTOCOL_MESSAGE_HPP
#define PROTOCOL_MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <streambuf>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

typedef unsigned long length_type;

class protocol_char_buffer 
: public std::streambuf
{
  public:
  protocol_char_buffer()
  {
  }

  protocol_char_buffer(char* begin, char* end)
  : begin_(begin),
    end_(end)
  {
    reset_buffer();
  }
  
  void set_base_parameters(char* begin, char* end)
  {
    begin_=begin;
    end_=end;
    reset_buffer();
  }

  void set_buffer_length(length_type length)
  {
    
    length_ = length;
    this->setg(begin_, begin_, begin_+length_);
    this->setp(begin_,begin_+length_);
  }

  void reset_buffer()
  {
    this->setg(begin_, begin_, end_);
    this->setp(begin_,end_);
  }

  private:
  char* begin_;
  char* end_; 
  length_type length_;
};

struct header_type {
  length_type body_length;
  unsigned long sid;
};

class protocol_message
: public std::iostream
{
public:
  enum { header_length = sizeof(header_type) }; //size of header_type
  enum { max_body_length = 1000000000 };

  protocol_message()
  {
    this->body()[max_body_length]='\0';
    message_buffer.set_base_parameters(this->body(),this->body()+max_body_length);
    this->rdbuf(&message_buffer);
    header_.body_length = max_body_length;
    header_.sid = 0;
  }

  protocol_message(const protocol_message& msg)
  {  
    this->body()[max_body_length]='\0';
    message_buffer.set_base_parameters(this->body(),this->body()+max_body_length);
    this->rdbuf(&message_buffer);
    memcpy(data_, msg.data(), msg.length()+1);
    body_length(msg.body_length());
    header_.sid = msg.sid();
  }
   
  const char* data() const
  {
    return data_;
  }

  char* data()
  {
    return data_;
  }

  length_type length() const
  {
    return header_length + header_.body_length;
  }

  const char* body() const
  {
    return data_ + header_length;
  }

  char* body()
  {
    return data_ + header_length;
  }

  unsigned long sid() const
  {
    return header_.sid;
  }

  void sid(unsigned long sid)
  {
    header_.sid=sid;
  }

  length_type body_length() const
  {
    return header_.body_length;
  }

  length_type body_length(length_type new_length)
  {
    if (new_length <= max_body_length)
    {
      header_.body_length = new_length;
    }
    else
    {
      header_.body_length = max_body_length;      
    }
    message_buffer.set_buffer_length(header_.body_length);
    return header_.body_length;
  }

  bool decode_header()
  {
    using namespace std;
    memcpy(&header_, data_, header_length);
    if(header_.body_length <= max_body_length)
    {
      body_length(header_.body_length);
      return true;
    }
    return false;
  }

  void encode_header()
  {
    using namespace std; // For sprintf and memcpy.
    this->put('\0');
    header_.body_length = strlen(this->body());
    body_length(header_.body_length);

    memcpy(data_, &header_, header_length);
  }

  void reset_message()
  {
    message_buffer.reset_buffer();
    header_.body_length=max_body_length;
  }

private:
  char data_[header_length + max_body_length + 1]; //a null temrination character is added in the of every meessage
  protocol_char_buffer message_buffer;
  header_type header_;
};

typedef boost::shared_ptr<protocol_message> protocol_message_ptr;
#endif // CHAT_MESSAGE_HPP
