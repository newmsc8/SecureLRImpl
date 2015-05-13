#include <fstream>
#include <SLA/linreg_files.hpp>
#include <NTL/mat_ZZ_p.h>
#include <SLA/ntl_random.hpp>
#include <boost/lexical_cast.hpp>

using namespace NTL;
using namespace std;

int main(int argc, char* argv[])
{
	long type = boost::lexical_cast<long>(argv[1]);
  ZZ q = boost::lexical_cast<ZZ>(argv[2]);
  ZZ_p::init(q);
	ZZ_p prec = boost::lexical_cast<ZZ_p>(argv[3]);
	string subA,subB;
	if (type == 1){
		subA = TR2_ALICE;
		subB = TR2_BOB;
	}
	if (type == 2){
		subA = Z3_ALICE;
		subB = Z3_BOB;
	}


	Mat<ZZ_p> A,B;

	ifstream i_alice(subA.c_str());
	i_alice >> A;
	i_alice.close();
	ifstream i_bob(subB.c_str());
	i_bob >> B;
	i_bob.close();
	
	for (int i=0;i<A.NumRows();i++){
		for (int j=0;j<A.NumCols();j++){
			A[i][j] = - A[i][j];
			B[i][j] = - B[i][j];
		}
		A[i][i] = A[i][i] + prec;
		B[i][i] = B[i][i] + prec;
	}	
	


	ofstream o_alice(subA.c_str(), ios::trunc);
	o_alice << A;
	o_alice.close();
	ofstream o_bob(subB.c_str(), ios::trunc);
	o_bob << B;
	o_bob.close();

}

