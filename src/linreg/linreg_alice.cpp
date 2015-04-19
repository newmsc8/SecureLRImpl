// Bernardo's Code :)

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <SLA/ntl_random.hpp>
#include <SLA/tcp_server_single.hpp>
#include <SLA/linreg_alice.hpp>

using boost::asio::ip::tcp;
using namespace NTL;

int main(int argc, char* argv[])
{
  try
  {
    ZZ q = boost::lexical_cast<ZZ>(argv[1]);
    ZZ_p::init(q);  
    set_seed_prng();    
    boost::asio::io_service io_service;
    tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[2]));
    twoparty_runner_ptr protocol(new linreg_alice(argv[3],argv[4])); 
		tcp_server server(io_service, endpoint, protocol);
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
