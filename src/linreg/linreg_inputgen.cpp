//linreg_inputgen.cpp
//Generates random inputs for the linreg protocol

#define _DEBUG

#include <fstream>
#include <SLA/linreg_params.hpp>
//#include <NTL/vec_ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <SLA/ntl_random.hpp>
#include <boost/lexical_cast.hpp>
#include <SLA/debug.hpp>

using namespace NTL;

int main(int argc, char* argv[])
{



  if (argc != 11)
  {
    std::cerr << "Usage:" << argv[0] << "<modulus> <matrix_dim> <x_alice> <x_bob> <y_alice> <y_bob> <output_file> <xy_alice> <xy_bob> <seed>\n";
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




  //create matrices of ZZ_p
  long dim;
  dim = boost::lexical_cast<long>(argv[2]);
  if (dim > MAX_MAT_DIM)
  {
    std::cerr << "Maximum vector length is: " << MAX_MAT_DIM << std::endl;
    return 1;
  }

  //set ntl rng seed
  long bnd = boost::lexical_cast<long>(argv[10]);
  set_seed_prng();
  
  ZZ_p bndp(bnd);
  //ZZ_p pm(mod_-1);
  
    //std::cout<<"it sees here"<<std::endl;

  Mat<ZZ_p> K;
  K.SetDims(dim,dim);
  for (long i = 0;i<dim;i++)
	for (long j = 0; j < dim; j++)
	  K[i][j] = -1 * (bndp/2);


//	  sub(K(i)(j),K(i)(j),(bndp/2));
    


  DEBUG("Generating X_A");
  Mat<ZZ_p> XA;
  XA.SetDims(dim,dim);
  gen_rnd_mat(XA,bnd,p);
  add(XA,XA,K);
  ofstream x_alice(argv[3], ios::trunc);
  DEBUG("Writing " << argv[3]);
  if (x_alice.is_open())
  {
    x_alice << XA;
  } else {
    std::cerr << "Failed to Open/Create file " << argv[3] << std::endl;
  }
  x_alice.close();

  DEBUG("Generating X_B");
  Mat<ZZ_p> XB;
  XB.SetDims(dim,dim);
  gen_rnd_mat(XB,bnd,p);
  add(XB,XB,K);
  ofstream x_bob(argv[4], ios::trunc);
  DEBUG("Writing " << argv[4]);
  if (x_bob.is_open())
  {
    x_bob << XB;
  } else {
    std::cerr << "Failed to Open/Create file " << argv[4] << std::endl;
  }
  x_bob.close();

  DEBUG("Generating Y_A");
  Mat<ZZ_p> YA;
  YA.SetDims(dim,dim);
  gen_rnd_mat(YA,bnd,p);
  add(YA,YA,K);
  ofstream y_alice(argv[5], ios::trunc);
  DEBUG("Writing " << argv[5]);
  if (y_alice.is_open())
  {
    y_alice << YA;
  } else {
    std::cerr << "Failed to Open/Create file " << argv[5] << std::endl;
  }
  y_alice.close();

  DEBUG("Generating Y_B");
  Mat<ZZ_p> YB;
  YB.SetDims(dim,dim);
  gen_rnd_mat(YB,bnd,p);
  add(YB,YB,K);
  ofstream y_bob(argv[6], ios::trunc);
  DEBUG("Writing " << argv[6]);
  if (y_bob.is_open())
  {
    y_bob << YB;
  } else {
    std::cerr << "Failed to Open/Create file " << argv[6] << std::endl;
  }
  y_bob.close();



  DEBUG("Generating OUTPUT");
  Mat<ZZ_p> X,Y,Res;
  Res.SetDims(dim,dim);
  X.SetDims(dim,dim);
  Y.SetDims(dim,dim);
  //gen_rnd_mat(XA);

  //std::cout<<"ADD"<<std::endl;
  add(X,XA,XB);
  //std::cout<<"ADD"<<std::endl;
  add(Y,YA,YB);
  //std::cout<<"MUL"<<std::endl;
  mul(Res,X,Y);

  
  ofstream res_file(argv[7], ios::trunc);
  DEBUG("Writing " << argv[7]);
  if (res_file.is_open())
  {
    res_file << Res;
  } else {
    std::cerr << "Failed to Open/Create file " << argv[7] << std::endl;
  }
  res_file.close();


  mul(Res,XA,YA);
  ofstream xy_alice(argv[8], ios::trunc);
  xy_alice << Res;
  xy_alice.close();

  mul(Res,XB,YB);
  ofstream xy_bob(argv[9], ios::trunc);
  xy_bob << Res;
  xy_bob.close();

  

}

