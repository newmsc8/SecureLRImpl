// Bernardo's Code :)

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <NTL/mat_ZZ_p.h>
#include <SLA/protocol_message.hpp>
#include <SLA/protocol_session.hpp>
#include <SLA/ntl_random.hpp>
#include <SLA/linreg_files.hpp>

using namespace NTL;

class linreg_alice
  : public twoparty_runner,
    public boost::enable_shared_from_this<linreg_alice>
{
public:
  linreg_alice(const char* d, const char* minus1)
  {

		dim = boost::lexical_cast<long>(d);
		m1 = boost::lexical_cast<ZZ_p>(minus1);
		XA.SetDims(dim,dim);
		YA.SetDims(dim,dim);
		AA.SetDims(dim,dim);
		BA.SetDims(dim,dim);
		CA.SetDims(dim,dim);
		XAYA.SetDims(dim,dim);
		RA.SetDims(dim,dim);
		RPA.SetDims(dim,dim);

    std::ifstream x_alice(X_ALICE);
    x_alice >> XA;
    x_alice.close();
    
    std::ifstream y_alice(Y_ALICE);
    y_alice >> YA;
    y_alice.close();

    std::ifstream a_alice(A_ALICE);
    a_alice >> AA;
    a_alice.close();

    std::ifstream b_alice(B_ALICE);
    b_alice >> BA;
    b_alice.close();

    std::ifstream c_alice(C_ALICE);
    c_alice >> CA;
    c_alice.close();

    std::ifstream xy_alice(XY_ALICE);
		xy_alice >> XAYA;
		xy_alice.close();

		std::ifstream r_alice(R_ALICE);
    r_alice >> RA;
    r_alice.close();
	
		std::ifstream rp_alice(RP_ALICE);
    rp_alice >> RPA;
    rp_alice.close();
  }

  bool msg_w(protocol_message_ptr input_msg)
  {

		Mat<ZZ_p> XBAB,YBBB,XAAA,YABA,DA,DB;
		XBAB.SetDims(dim,dim);
		YBBB.SetDims(dim,dim);
		XAAA.SetDims(dim,dim);
		YABA.SetDims(dim,dim);
		DA.SetDims(dim,dim);
		DB.SetDims(dim,dim);

    protocol_message_ptr msg(new protocol_message);

    *(input_msg) >> XBAB >> YBBB;

		sub(XAAA,XA,AA);
		sub(YABA,YA,BA);
	
		gen_rnd_mat(DA);

		mul(YBBB,AA,YBBB);
		mul(XBAB,XBAB,BA);

		add(DB,XAYA,YBBB);
		add(DB,DB,XBAB);
		sub(DB,DB,DA);
	
		*(msg) << XAAA << std::endl;
		*(msg) << YABA << std::endl;
		*(msg) << DB << std::endl;
	
	
		add(CA,CA,DA);
		// WA is CA from this point forward
		//std::cout << CA[0][0] << std::endl;

		add(RA,RA,CA);
		// Send WA + RA to Bob
		*(msg) << RA <<std::endl;

		add(CA,CA,RPA);
		//std::cout << CA[0][0] << std::endl;
		// CA is WA + RPA from this point forward
		mul(CA,CA,m1);
		//std::cout << CA[0][0] << std::endl;
		std::ofstream a_out(OUT_ALICE, std::ios::trunc);
 	  a_out << CA;
  	a_out.close();
    send_message(msg);
    return true;
  }
   
  void protocol_start()
  {
  }

  void receive_msg(protocol_message_ptr msg) 
  {
    msg_w(msg);
    //terminate_protocol();
  }
  
private:
Mat<ZZ_p> XA,YA,AA,BA,CA,XAYA,RA,RPA;
long dim;
ZZ_p m1;
char* out_alice;
};

