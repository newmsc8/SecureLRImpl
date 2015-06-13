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
//#include <string>

using namespace NTL;
using namespace std;

class linreg_alice
  : public twoparty_runner,
    public boost::enable_shared_from_this<linreg_alice>
{
public:
  linreg_alice(const char* t, const char* r, const char* c, const char* minus1)
  {
		type = boost::lexical_cast<long>(t);
		row = boost::lexical_cast<long>(r);
		col = boost::lexical_cast<long>(c);
		m1 = boost::lexical_cast<ZZ_p>(minus1);
		if (type == 1){
			dim1 = col;
			dim2 = row;
			dim3 = col;
			outA = Z1_ALICE;
			in1A = X_ALICE;
			in2A = Y_ALICE;
		}
		if (type == 2){
			dim1 = dim2 = dim3 = 1;
			outA = TR2_ALICE;
			in1A = TR_ALICE;
			in2A = TR1_ALICE;
		}
		if (type == 3){
			dim1 = dim2 = dim3 = 1;
			outA = TR1_ALICE;
			in1A = TR1_ALICE;
			in2A = TR2_ALICE;			
		}
		if (type == 4){
			dim1 = dim2 = dim3 = col;
			outA = Z3_ALICE;
			in1A = Z1_ALICE;
			in2A = Z2_ALICE;			
		}
		if (type == 5){
			dim1 = dim2 = dim3 = col;
			outA = Z2_ALICE;
			in1A = Z2_ALICE;
			in2A = Z3_ALICE;			
		}
		if (type == 6){
			dim1 = dim2 = col;
			dim3 = row;
			outA = Z4_ALICE;
			in1A = Z2_ALICE;
			in2A = XTF_ALICE;			
		}
		if (type == 7){
			dim1 = col;
			dim2 = row;
			dim3 = 1;
			outA = Z5_ALICE;
			in1A = Z4_ALICE;
			in2A = YF_ALICE;			
		}
		
    std::ifstream x_alice(in1A.c_str());
    x_alice >> XA;
    x_alice.close();
    std::ifstream y_alice(in2A.c_str());
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
		Mat<ZZ_p> XBAB,YBBB,XAAA,YABA,DA,DB,XBABBA,AAYBBB;
		DA.SetDims(dim1,dim3);

    protocol_message_ptr msg(new protocol_message);
    *(input_msg) >> XBAB >> YBBB;
		sub(XAAA,XA,AA);
		sub(YABA,YA,BA);
	
		gen_rnd_mat(DA);
		mul(AAYBBB,AA,YBBB);
		mul(XBABBA,XBAB,BA);

		add(DB,XAYA,AAYBBB);

		add(DB,DB,XBABBA);
		sub(DB,DB,DA);
	
		*(msg) << XAAA << std::endl;
		*(msg) << YABA << std::endl;
		*(msg) << DB << std::endl;
	
		add(CA,CA,DA);
		// WA is CA from this point forward
		add(RA,RA,CA);
		// Send WA + RA to Bob
		*(msg) << RA <<std::endl;

		add(CA,CA,RPA);
		// CA is WA + RPA from this point forward
		mul(CA,CA,m1);
		std::ofstream a_out(outA.c_str(), std::ios::trunc);
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
  }
  
private:
Mat<ZZ_p> XA,YA,AA,BA,CA,XAYA,RA,RPA;
long row,col,type,dim1,dim2,dim3;
string outA,in1A,in2A;
ZZ_p m1;
char* out_alice;
};

