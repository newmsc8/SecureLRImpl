// Brian's Code :)

#include <fstream>
#include <NTL/mat_ZZ_p.h>
#include <SLA/ntl_random.hpp>
#include <SLA/linreg_files.hpp>
#include <boost/lexical_cast.hpp>

using namespace NTL;
using namespace std;

int main(int argc, char* argv[])
{
  ZZ q = boost::lexical_cast<ZZ>(argv[1]);
  ZZ_p::init(q);
  long dim = boost::lexical_cast<long>(argv[2]);
  long prec = boost::lexical_cast<long>(argv[3]);
	ZZ lambda = boost::lexical_cast<ZZ>(argv[4]);   
  set_seed_prng();

  Mat<ZZ_p> AA;
  AA.SetDims(dim,dim);
  gen_rnd_mat(AA);
  ofstream a_alice(A_ALICE, ios::trunc);
  a_alice << AA;
  a_alice.close();

  Mat<ZZ_p> AB;
  AB.SetDims(dim,dim);
  gen_rnd_mat(AB);
  ofstream a_bob(A_BOB, ios::trunc);
  a_bob << AB;
  a_bob.close();

  Mat<ZZ_p> BA;
  BA.SetDims(dim,dim);
  gen_rnd_mat(BA);
  ofstream b_alice(B_ALICE, ios::trunc);
  b_alice << BA;
  b_alice.close();

  Mat<ZZ_p> BB;
  BB.SetDims(dim,dim);
  gen_rnd_mat(BB);
  ofstream b_bob(B_BOB, ios::trunc);
  b_bob << BB;
  b_bob.close();

  Mat<ZZ_p> CA;
  CA.SetDims(dim,dim);
  gen_rnd_mat(CA);
  ofstream c_alice(C_ALICE, ios::trunc);
  c_alice << CA;
  c_alice.close();

  Mat<ZZ_p> AABB,ABBA,CB;
  AABB.SetDims(dim,dim);
  ABBA.SetDims(dim,dim);
  CB.SetDims(dim,dim);
  mul(AABB,AA,BB);
  mul(ABBA,AB,BA);
  add(CB,AABB,ABBA);
  sub(CB,CB,CA);
  ofstream c_bob(C_BOB, ios::trunc);
  c_bob << CB;
  c_bob.close();

	ZZ zprec(prec);
  ZZ_p::init(zprec);
  Mat<ZZ_p> RP;
  RP.SetDims(dim,dim);
  gen_rnd_mat(RP);
  ZZ_p::init(lambda);
  Mat<ZZ_p> RPP;
  RPP.SetDims(dim,dim);
  gen_rnd_mat(RPP);    
  ZZ_p::init(q);
  Mat<ZZ_p> R;
  R.SetDims(dim,dim);
  R = RPP * prec + RP;
  

  Mat<ZZ_p> RA,RPA;
  RA.SetDims(dim,dim);
  RPA.SetDims(dim,dim);
  gen_rnd_mat(RA);
  gen_rnd_mat(RPA);
  Mat<ZZ_p> RB,RPB;
  RB.SetDims(dim,dim);
  RPB.SetDims(dim,dim);
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

}

