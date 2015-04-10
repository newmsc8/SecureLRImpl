//
// innerprod_alice.cpp
// ~~~~~~~~~~~~~~~
//

//#define _DEBUG 1

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <NTL/vec_ZZ_p.h> 
#include <SLA/linreg_params.hpp>
#include <SLA/debug.hpp>
#include <SLA/ntl_random.hpp>
#include <SLA/tcp_server_single.hpp>
#include <SLA/linreg_alice.hpp>

using boost::asio::ip::tcp;
using namespace NTL;

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 13)
    {
      std::cerr << "Usage: alice <modulus> <port> <x_alice> <y_alice> <a_alice> <b_alice> <c_alice> <dim> <out_alice> <xy_alice> <ra> <rpa>\n";
      return 1;
    }
   
    //set modulus to ModP
    long mod_ = boost::lexical_cast<long>(argv[1]);
    if (mod_ > MOD)
    {
      std::cerr << "Maximum modulus is: " << MOD;
      return 1;
    }
    ZZ p;
    p = mod_;
    ZZ_p::init(p);  
    DEBUG("set modulus to: " << p);

    //set NTL PRGN
    set_seed_prng();    
	std::cout << "SALAM1" << std::endl;
    boost::asio::io_service io_service;
	std::cout << "SALAM2" << std::endl;
    tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[2]));
	std::cout << "SALAM3" << std::endl;
    //create instance of protoco9l
    twoparty_runner_ptr protocol(new linreg_alice(argv[8],argv[3],argv[4],argv[5],argv[6],argv[7],argv[9],argv[10],argv[11],argv[12])); 
	std::cout << "SALAM4" << std::endl;    
	tcp_server server(io_service, endpoint, protocol);
	std::cout << "SALAM5" << std::endl;	
	//std::cout << "SALAM3" << std::endl;
    io_service.run();
	std::cout << "SALAM6" << std::endl;	
	//std::cout << "SALAM4" << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
