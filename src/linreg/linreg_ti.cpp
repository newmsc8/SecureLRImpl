//
//innerprod_ti.cpp
//

#define _DEBUG

#include <fstream>
#include <SLA/linreg_params.hpp>
#include <NTL/vec_ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <SLA/ntl_random.hpp>
#include <boost/lexical_cast.hpp>
#include <SLA/debug.hpp>

using namespace NTL;

int main(int argc, char* argv[])
{

  if (argc != 14)
  {
    std::cerr << "Usage: " << argv[0] << " <modulus> <vector_length> <a_alice> <a_bob> <b_alice> <b_bob> <c_alice> <c_bob> <seed> <ra> <rb> <rpa> <rpb>" << std::endl;
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

  //create vectors of ZZ_p
  long dim;
  dim = boost::lexical_cast<long>(argv[2]);
  
  if (dim > MAX_MAT_DIM)
  {
    std::cerr << "Maximum matrix dimension is: " << MAX_MAT_DIM << std::endl;
    return 1;
  }

  //set ntl rng seed
  set_seed_prng();


  long bnd = boost::lexical_cast<long>(argv[9]);  
  ZZ_p bndp(bnd);
  Mat<ZZ_p> K;
  K.SetDims(dim,dim);
  for (long i = 0;i<dim;i++)
	for (long j = 0; j < dim; j++)
	  K[i][j] = -1 * (bndp/2);


  DEBUG("Generating A_A");
  Mat<ZZ_p> AA;
  AA.SetDims(dim,dim);
  gen_rnd_mat(AA,bnd,p);
  add(AA,AA,K);
  ofstream a_alice(argv[3], ios::trunc);
  DEBUG("Writing " << argv[3]);
  if (a_alice.is_open())
  {
    a_alice << AA;
  } else {
    std::cerr << "Failed to Open/Create file " << argv[3] << std::endl;
  }
  a_alice.close();


  DEBUG("Generating A_B");
  Mat<ZZ_p> AB;
  AB.SetDims(dim,dim);
  gen_rnd_mat(AB,bnd,p);
  add(AB,AB,K);
  ofstream a_bob(argv[4], ios::trunc);
  DEBUG("Writing " << argv[4]);
  if (a_bob.is_open())
  {
    a_bob << AB;
  } else {
    std::cerr << "Failed to Open/Create file " << argv[4] << std::endl;
  }
  a_bob.close();

  DEBUG("Generating B_A");
  Mat<ZZ_p> BA;
  BA.SetDims(dim,dim);
  gen_rnd_mat(BA,bnd,p);
  add(BA,BA,K);
  ofstream b_alice(argv[5], ios::trunc);
  DEBUG("Writing " << argv[5]);
  if (b_alice.is_open())
  {
    b_alice << BA;
  } else {
    std::cerr << "Failed to Open/Create file " << argv[5] << std::endl;
  }
  b_alice.close();


  DEBUG("Generating B_B");
  Mat<ZZ_p> BB;
  BB.SetDims(dim,dim);
  gen_rnd_mat(BB,bnd,p);
  add(BB,BB,K);
  ofstream b_bob(argv[6], ios::trunc);
  DEBUG("Writing " << argv[6]);
  if (b_bob.is_open())
  {
    b_bob << BB;
  } else {
    std::cerr << "Failed to Open/Create file " << argv[6] << std::endl;
  }
  b_bob.close();


  DEBUG("Generating C_A");
  Mat<ZZ_p> CA;
  CA.SetDims(dim,dim);
  gen_rnd_mat(CA,bnd,p);
  add(CA,CA,K);
  ofstream c_alice(argv[7], ios::trunc);
  DEBUG("Writing " << argv[7]);
  if (c_alice.is_open())
  {
    c_alice << CA;
  } else {
    std::cerr << "Failed to Open/Create file " << argv[7] << std::endl;
  }
  c_alice.close();



  DEBUG("Generating C_B");
  Mat<ZZ_p> AABB,ABBA,CB;
  AABB.SetDims(dim,dim);
  ABBA.SetDims(dim,dim);
  CB.SetDims(dim,dim);
  //gen_rnd_mat(XA);

  //std::cout<<"ADD"<<std::endl;
  mul(AABB,AA,BB);
  //std::cout<<"ADD"<<std::endl;
  mul(ABBA,AB,BA);
  //std::cout<<"MUL"<<std::endl;
  add(CB,AABB,ABBA);
  sub(CB,CB,CA);

  
  ofstream c_bob(argv[8], ios::trunc);
  DEBUG("Writing " << argv[8]);
  if (c_bob.is_open())
  {
    c_bob << CB;
  } else {
    std::cerr << "Failed to Open/Create file " << argv[8] << std::endl;
  }
  c_bob.close();

/////////truncation stuff
  ZZ F(10);
  ZZ lk(100000);
  // to be moved to run file
  //ZZ_p one = 1;
  //ZZ_p fm = div(one,ten);
  ZZ_p::init(F);
  Mat<ZZ_p> RP;
  RP.SetDims(dim,dim);
  gen_rnd_mat(RP);
  //ZZ_p rp = random_ZZ_p();
  ZZ_p::init(lk);
  Mat<ZZ_p> RPP;
  RPP.SetDims(dim,dim);
  gen_rnd_mat(RPP);    
  //ZZ_p rpp = random_ZZ_p();
  ZZ_p::init(p);
  Mat<ZZ_p> R;
  R.SetDims(dim,dim);
  //gen_rnd_mat(RP);
  R = RPP * 10 + RP;
  

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

  ofstream r_alice(argv[10], ios::trunc);
  r_alice << RA;
  r_alice.close();

  ofstream r_bob(argv[11], ios::trunc);
  r_bob << RB;
  r_bob.close();

  ofstream rp_alice(argv[12], ios::trunc);
  rp_alice << RPA;
  rp_alice.close();

  ofstream rp_bob(argv[13], ios::trunc);
  rp_bob << RA;
  rp_bob.close();





}

