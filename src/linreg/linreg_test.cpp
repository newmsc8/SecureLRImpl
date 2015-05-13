// Bernardo's Code :)

#include <fstream>
#include <SLA/linreg_files.hpp>
#include <NTL/mat_ZZ_p.h>
#include <SLA/ntl_random.hpp>
#include <boost/lexical_cast.hpp>

using namespace NTL;
using namespace std;

int main(int argc, char* argv[])
{
	//long type = boost::lexical_cast<long>(argv[1]);
  ZZ q = boost::lexical_cast<ZZ>(argv[1]);
  ZZ_p::init(q);


		Mat<ZZ_p> TO,AO,BO;
		//TO.SetDims(dim,dim);
		//AO.SetDims(dim,dim);
		//BO.SetDims(dim,dim);
	
		std::ifstream o_alice(Z3_ALICE);
		o_alice >> AO;
		o_alice.close();

		std::ifstream o_bob(Z3_BOB);
		o_bob >> BO;
		o_bob.close();

		add(TO,AO,BO);
	
		std::ofstream trunc_out(Z3, ios::trunc);
		trunc_out << TO;
		trunc_out.close();


		Mat<ZZ_p> T,A,B;
		//TO.SetDims(dim,dim);
		//AO.SetDims(dim,dim);
		//BO.SetDims(dim,dim);
	
		std::ifstream oo_alice(Z2_ALICE);
		oo_alice >> A;
		oo_alice.close();

		std::ifstream oo_bob(Z2_BOB);
		oo_bob >> B;
		oo_bob.close();

		add(T,A,B);
	
		std::ofstream trunc_oout(Z2, ios::trunc);
		trunc_oout << T;
		trunc_oout.close();


		Mat<ZZ_p> TOO,AOO,BOO;
		//TO.SetDims(dim,dim);
		//AO.SetDims(dim,dim);
		//BO.SetDims(dim,dim);
	
		std::ifstream ooo_alice(Z5_ALICE);
		ooo_alice >> AOO;
		ooo_alice.close();

		std::ifstream ooo_bob(Z5_BOB);
		ooo_bob >> BOO;
		ooo_bob.close();

		add(TOO,AOO,BOO);
	
		std::ofstream ooo_out(Z5, ios::trunc);
		ooo_out << TOO;
		ooo_out.close();

		Mat<ZZ_p> A1,B1;
		//TO.SetDims(dim,dim);
		//AO.SetDims(dim,dim);
		//BO.SetDims(dim,dim);
	
		std::ifstream t2_alice(TR2_ALICE);
		t2_alice >> A1;
		t2_alice.close();

		std::ifstream t2_bob(TR2_BOB);
		t2_bob >> B1;
		t2_bob.close();

		cout << A1[0][0] + B1[0][0] <<endl;	

		Mat<ZZ_p> A2,B2;
		//TO.SetDims(dim,dim);
		//AO.SetDims(dim,dim);
		//BO.SetDims(dim,dim);
	
		std::ifstream t_alice(TR1_ALICE);
		t_alice >> A2;
		t_alice.close();

		std::ifstream t_bob(TR1_BOB);
		t_bob >> B2;
		t_bob.close();

		cout << A2[0][0] + B2[0][0] <<endl;	


}

