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
//#include <string.h>
using namespace NTL;
using namespace std;

class innerprod_bob
  : public twoparty_runner,
    public boost::enable_shared_from_this<innerprod_bob>
{
public:
  innerprod_bob(const char* t, const char* r, const char* c, const char* minus1, const char* pre)
  {
		type = boost::lexical_cast<long>(t);
		row = boost::lexical_cast<long>(r);
		col = boost::lexical_cast<long>(c);
		m1 = boost::lexical_cast<ZZ_p>(minus1);
		prec = boost::lexical_cast<ZZ_p>(pre);
		if (type == 1){
			dim1 = col;
			dim2 = row;
			dim3 = col;
			outB = Z1_BOB;
			in1B = X_BOB;
			in2B = Y_BOB;
		}
		if (type == 2){
			dim1 = 1;
			dim2 = 1;
			dim3 = 1;
			outB = TR2_BOB;
			in1B = TR_BOB;
			in2B = TR1_BOB;
		}
		if (type == 3){
			dim1 = 1;
			dim2 = 1;
			dim3 = 1;
			outB = TR1_BOB;
			in1B = TR1_BOB;
			in2B = TR2_BOB;
		}
		if (type == 4){
			dim1 = dim2 = dim3 = col;
			outB = Z3_BOB;
			in1B = Z1_BOB;
			in2B = Z2_BOB;
		}
		if (type == 5){
			dim1 = dim2 = dim3 = col;
			outB = Z2_BOB;
			in1B = Z2_BOB;
			in2B = Z3_BOB;
		}
		if (type == 6){
			dim1 = dim2 = col;
			dim3 = row;
			outB = Z4_BOB;
			in1B = Z2_BOB;
			in2B = XTF_BOB;
		}
		if (type == 7){
			dim1 = col;
			dim2 = row;
			dim3 = 1;
			outB = Z5_BOB;
			in1B = Z4_BOB;
			in2B = YF_BOB;			
		}
		XB.SetDims(dim1,dim2);
		YB.SetDims(dim2,dim3);
		AB.SetDims(dim1,dim2);
		BB.SetDims(dim2,dim3);
		CB.SetDims(dim1,dim3);
		XBYB.SetDims(dim1,dim3);
		std::ifstream x_bob(in1B.c_str());
		x_bob >> XB;
		x_bob.close();
		std::ifstream y_bob(in2B.c_str());
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
		Mat<ZZ_p> XAAA,YABA,DB,ZA,XAAAYB,XBYABA;
		*(msg) >> XAAA >> YABA >> DB >> ZA;
		mul(XAAAYB,XAAA,YB);
		mul(XBYABA,XB,YABA);
		add(CB,CB,DB);
		add(CB,CB,XBYB);
		add(CB,CB,XAAAYB);
		add(CB,CB,XBYABA);

		add(ZA,ZA,CB);
		add(ZA,ZA,RB);

		Mat<ZZ> CP;
		CP.SetDims(dim1,dim3);
		for (long i=0;i<dim1;i++)
			for (long j=0;j<dim3;j++){
				
				CP[i][j]=rep(ZA[i][j]);
				ZZ k;
				rem(k,CP[i][j],rep(prec));
				ZA[i][j] = boost::lexical_cast<ZZ_p>(k);
			}
			
		add(CB,CB,RPB);
		sub(CB,CB,ZA);
		mul(CB,CB,m1);
		ofstream b_out(outB.c_str(), ios::trunc);
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
long type,row,col,dim1,dim2,dim3;
ZZ_p m1,prec;
string outB,in1B,in2B;
struct timeval then, now;
double exec_time;
};

