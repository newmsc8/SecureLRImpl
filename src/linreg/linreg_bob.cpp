//
// innerprod_bob.cpp
// ~~~~~~~~~~~~~~~
//Inner product bob
//

//#define _DEBUG 1

#include <cstdlib>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <NTL/vec_ZZ_p.h>
#include <SLA/linreg_params.hpp>
#include <SLA/debug.hpp>
#include <SLA/tcp_client.hpp>
#include <SLA/linreg_bob.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 14)
    {
      std::cerr << "Usage: bob <modulus> <host> <port> <x_bob> <y_bob> <a_bob> <b_bob> <c_bob> <dim> <out_bob> <xy_bob> <rb> <rpb>\n";
      return 1;
    }
    
    //set the modulus size used in NTL to MOD defined in the includes
    ZZ p;
    p = boost::lexical_cast<long>(argv[1]);
    ZZ_p::init(p);
    DEBUG("set modulus to: " << p);
	//std::cout << "SALAM1" << std::endl;
    //setup network connection
    boost::asio::io_service io_service;
	std::cout << "SALAM1" << std::endl;
    tcp::resolver resolver(io_service);
	std::cout << "SALAM2" << std::endl;
    tcp::resolver::query query(argv[2], argv[3]);
	std::cout << "SALAM3" << std::endl;    
	tcp::resolver::iterator iterator = resolver.resolve(query);
	//std::cout << "SALAM2" << std::endl;    
    //create instance of protoco9l
	std::cout << "SALAM4" << std::endl;
    twoparty_runner_ptr protocol(new innerprod_bob(argv[9],argv[4],argv[5],argv[6],argv[7],argv[8],argv[10],argv[11],argv[12],argv[13]));
	//std::cout << "SALAM3" << std::endl;
    //create tcp/ip client to run protocol
	std::cout << "SALAM5" << std::endl;
    tcp_client c(io_service, iterator, protocol);
	//std::cout << "SALAM4" << std::endl;
	std::cout << "SALAM6" << std::endl;    
    io_service.run();
	std::cout << "SALAM7" << std::endl;
	//std::cout << "SALAM5" << std::endl;
    
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
