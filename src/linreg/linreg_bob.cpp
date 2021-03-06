#include <cstdlib>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <SLA/tcp_client.hpp>
#include <SLA/linreg_bob.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
  {
    ZZ q = boost::lexical_cast<ZZ>(argv[2]);
    ZZ_p::init(q);
    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(argv[3], argv[4]);
		tcp::resolver::iterator iterator = resolver.resolve(query);
    twoparty_runner_ptr protocol(new innerprod_bob(argv[1],argv[5],argv[6],argv[7],argv[8]));
    tcp_client c(io_service, iterator, protocol);
    io_service.run();   
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
