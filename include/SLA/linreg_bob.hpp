// Bernardo's Code :)

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <NTL/mat_ZZ_p.h>
#include <NTL/mat_ZZ.h>
#include <SLA/protocol_message.hpp>
#include <SLA/protocol_session.hpp>
#include <SLA/linreg_files.hpp>
#include <sys/time.h>
#include <time.h>

using namespace NTL;

class innerprod_bob
  : public twoparty_runner,
    public boost::enable_shared_from_this<innerprod_bob>
{
public:
  innerprod_bob(const char* d, const char* minus1)
  {
		dim = boost::lexical_cast<long>(d);
		m1 = boost::lexical_cast<ZZ_p>(minus1); 
		XB.SetDims(dim,dim);
		YB.SetDims(dim,dim);
		AB.SetDims(dim,dim);
		BB.SetDims(dim,dim);
		CB.SetDims(dim,dim);
		XBYB.SetDims(dim,dim);

		std::ifstream x_bob(X_BOB);
		x_bob >> XB;
		x_bob.close();
		  
		std::ifstream y_bob(Y_BOB);
		y_bob >> YB;
		y_bob.close();

		std::ifstream a_bob(A_BOB);
		a_bob >> AB;
		a_bob.close();

		std::ifstream b_bob(B_BOB);
		b_bob >> BB;
		b_bob.close();

    std::ifstream c_bob(C_BOB);
    c_bob >> CB;
    c_bob.close();

		std::ifstream xy_bob(XY_BOB);	
		xy_bob >> XBYB;
		xy_bob.close();


		std::ifstream r_bob(R_BOB);
    r_bob >> RB;
    r_bob.close();

		std::ifstream rp_bob(RP_BOB);
    rp_bob >> RPB;
    rp_bob.close();
  }


  bool msg_xayb()
  {

		Mat<ZZ_p> XBAB,YBBB;
		XBAB.SetDims(dim,dim);
		YBBB.SetDims(dim,dim);
		sub(XBAB,XB,AB);
		sub(YBBB,YB,BB);
    protocol_message_ptr msg(new protocol_message);
		*(msg) << XBAB << std::endl;
		*(msg) << YBBB << std::endl;
    send_message(msg);

    return true;
  }

  bool msg_v(protocol_message_ptr msg)
  {
		Mat<ZZ_p> XAAA,YABA,DB,ZA;
		XAAA.SetDims(dim,dim);
		YABA.SetDims(dim,dim);
		DB.SetDims(dim,dim);
		ZA.SetDims(dim,dim);
		*(msg) >> XAAA >> YABA >> DB >> ZA;
		mul(XAAA,XAAA,YB);
		mul(YABA,XB,YABA);
		add(CB,CB,DB);
		add(CB,CB,XBYB);
		add(CB,CB,XAAA);
		add(CB,CB,YABA);

		//std::cout << CB[0][0] << std::endl;

		add(ZA,ZA,CB);
		add(ZA,ZA,RB);
		Mat<ZZ> CP;
		CP.SetDims(dim,dim);
		//std::cout << ZA[0][0] << std::endl;
		for (long i=0;i<dim;i++)
			for (long j=0;j<dim;j++){
				CP[i][j]=rep(ZA[i][j]);
				ZA[i][j]=rem(CP[i][j],10);
			}
		//std::cout << ZA[0][0] << std::endl;				
			
		add(CB,CB,RPB);
		//std::cout << CB[0][0] << std::endl;
		sub(CB,CB,ZA);
		//std::cout << CB[0][0] << std::endl;
		mul(CB,CB,m1);
		//std::cout << CB[0][0] << std::endl;
		std::ofstream b_out(OUT_BOB, std::ios::trunc);
		b_out << CB;
  	b_out.close();

    gettimeofday(&now, NULL);
    exec_time = now.tv_sec - then.tv_sec + 1e-6 * (now.tv_usec - then.tv_usec); 
    std::cout << "Protocol execution time: " << exec_time << std::endl;

    return true;
  }

  void protocol_start()
  {
    gettimeofday(&then, NULL);
    msg_xayb();  
  }

  void receive_msg(protocol_message_ptr msg)
  {
    msg_v(msg);
    terminate_protocol();
  }

private:
Mat<ZZ_p> XB,YB,AB,BB,CB,XBYB,RB,RPB;
long dim;
ZZ_p m1;
struct timeval then, now;
double exec_time;
};

