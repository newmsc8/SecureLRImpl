// Brian's Code :)

#include <fstream>
#include <NTL/mat_ZZ_p.h>
#include <SLA/ntl_random.hpp>
#include <SLA/linreg_files.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

using namespace NTL;
using namespace std;

int main(int argc, char* argv[])
{
	long type = boost::lexical_cast<long>(argv[1]);
  ZZ q = boost::lexical_cast<ZZ>(argv[2]);
  ZZ_p::init(q);
  long row = boost::lexical_cast<long>(argv[3]);
  long col = boost::lexical_cast<long>(argv[4]);
 	ZZ_p prec = boost::lexical_cast<ZZ_p>(argv[5]);
	ZZ lambda = boost::lexical_cast<ZZ>(argv[6]);   
  set_seed_prng();
	long dim1,dim2,dim3;
	string in1A,in1B,in2A,in2B;


	if (type == 1){
		dim1=col;
		dim2=row;
		dim3=col;
		in1A = X_ALICE;
		in1B = X_BOB;
		in2A = Y_ALICE;
		in2B = Y_BOB;
	}

	if (type == 2){
		dim1 = dim2 = dim3 = 1;
		in1A = TR_ALICE;
		in1B = TR_BOB;
		in2A = TR1_ALICE;
		in2B = TR1_BOB;
	}

	if (type == 3){
		dim1 = dim2 = dim3 = 1;
		in1A = TR1_ALICE;
		in1B = TR1_BOB;
		in2A = TR2_ALICE;
		in2B = TR2_BOB;
	}

	if (type == 4){
		dim1 = dim2 = dim3 = col;
		in1A = Z1_ALICE;
		in1B = Z1_BOB;
		in2A = Z2_ALICE;
		in2B = Z2_BOB;
	}

	if (type == 5){
		dim1 = dim2 = dim3 = col;
		in1A = Z2_ALICE;
		in1B = Z2_BOB;
		in2A = Z3_ALICE;
		in2B = Z3_BOB;
	}

	if (type == 6){
		dim1 = dim2 = col;
		dim3 = row;
		in1A = Z2_ALICE;
		in1B = Z2_BOB;
		in2A = XTF_ALICE;
		in2B = XTF_BOB;
	}
	if (type == 7){
		dim1 = col;
		dim2 = row;
		dim3 = 1;
		in1A = Z4_ALICE;
		in1B = Z4_BOB;
		in2A = YF_ALICE;
		in2B = YF_BOB;			
	}
// Multiplication Protocol TI

  Mat<ZZ_p> AA;
  AA.SetDims(dim1,dim2);
  gen_rnd_mat(AA);
  ofstream a_alice(A_ALICE, ios::trunc);
  a_alice << AA;
  a_alice.close();

  Mat<ZZ_p> AB;
  AB.SetDims(dim1,dim2);
  gen_rnd_mat(AB);
  ofstream a_bob(A_BOB, ios::trunc);
  a_bob << AB;
  a_bob.close();

  Mat<ZZ_p> BA;
  BA.SetDims(dim2,dim3);
  gen_rnd_mat(BA);
  ofstream b_alice(B_ALICE, ios::trunc);
  b_alice << BA;
  b_alice.close();

  Mat<ZZ_p> BB;
  BB.SetDims(dim2,dim3);
  gen_rnd_mat(BB);
  ofstream b_bob(B_BOB, ios::trunc);
  b_bob << BB;
  b_bob.close();

  Mat<ZZ_p> CA;
  CA.SetDims(dim1,dim3);
  gen_rnd_mat(CA);
  ofstream c_alice(C_ALICE, ios::trunc);
  c_alice << CA;
  c_alice.close();

  Mat<ZZ_p> AABB,ABBA,CB;
  AABB.SetDims(dim1,dim3);
  ABBA.SetDims(dim1,dim3);
  CB.SetDims(dim1,dim3);
  mul(AABB,AA,BB);
  mul(ABBA,AB,BA);
  add(CB,AABB,ABBA);
  sub(CB,CB,CA);
  ofstream c_bob(C_BOB, ios::trunc);
  c_bob << CB;
  c_bob.close();



// Truncation Protocol TI

	ZZ zprec = rep(prec);
  ZZ_p::init(zprec);
  Mat<ZZ_p> RP;
  RP.SetDims(dim1,dim3);
  gen_rnd_mat(RP);
  ZZ_p::init(lambda);
  Mat<ZZ_p> RPP;
  RPP.SetDims(dim1,dim3);
  gen_rnd_mat(RPP);    
  ZZ_p::init(q);
  Mat<ZZ_p> R;
  R.SetDims(dim1,dim3);
  R = RPP * prec + RP;
  

  Mat<ZZ_p> RA,RPA;
  RA.SetDims(dim1,dim3);
  RPA.SetDims(dim1,dim3);
  gen_rnd_mat(RA);
  gen_rnd_mat(RPA);
  Mat<ZZ_p> RB,RPB;
  RB.SetDims(dim1,dim3);
  RPB.SetDims(dim1,dim3);
  sub(RB,R,RA);
  sub(RPB,RP,RPA);  

  ofstream r_alice(R_ALICE, ios::trunc);
  r_alice << RA;
  r_alice.close();

  ofstream r_bob(R_BOB, ios::trunc);
  r_bob << RB;
  r_bob.close();

  ofstream rp_alice(RP_ALICE, ios::trunc);
  rp_alice << RPA;
  rp_alice.close();

  ofstream rp_bob(RP_BOB, ios::trunc);
  rp_bob << RPB;
  rp_bob.close();




/// preprocess stuff

	Mat<ZZ_p> XAYA,XBYB,XA,XB,YA,YB,X,Y;
	//XAYA.SetDims(dim1,dim3);
	//XBYB.SetDims(dim1,dim3);
	//XA.SetDims(dim1,dim2);
	//XB.SetDims(dim1,dim2);
	//YA.SetDims(dim2,dim3);
	//YB.SetDims(dim2,dim3);
	//X.SetDims(dim1,dim3);
	//Y.SetDims(dim1,dim3);

	ifstream x_alice(in1A.c_str());
	x_alice >> XA;
	x_alice.close();
	ifstream x_bob(in1B.c_str());
	x_bob >> XB;
	x_bob.close();
	ifstream y_alice(in2A.c_str());
	y_alice >> YA;
	y_alice.close();
	ifstream y_bob(in2B.c_str());
	y_bob >> YB;
	y_bob.close();

	


  mul(XAYA,XA,YA);
  ofstream xy_alice(XY_ALICE, ios::trunc);
  xy_alice << XAYA;
  xy_alice.close();

  mul(XBYB,XB,YB);
  ofstream xy_bob(XY_BOB, ios::trunc);
  xy_bob << XBYB;
  xy_bob.close();


////////////////////

}

