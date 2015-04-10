# ifndef NTL_RANDOM_HPP
#define NTL_RANDOM_HPP

#include <NTL/vec_ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <time.h>
#include<fstream>
#include<boost/lexical_cast.hpp>
#include "SLA/debug.hpp"

#define rnd_length 4 //length of random seed in bytes in the variable length mode, min=1, max=8

using namespace std;
using namespace NTL;

void set_seed_prng()
{
  ZZ seed;
  seed = (long)time(NULL);
  SetSeed(seed);
}

void set_seed_rng()
{
  ifstream randomData("/dev/random", ios::binary);  
  //char RandomBuffer[rnd_length]; //use this for a variable length buffer
  unsigned  long RandomBuffer; //use this for a 8 bytes buffer
  //unsigned int RandomBuffer; //use this for a 4 bytes buffer
  streamsize randomDataLen = 0;
  while (randomDataLen < sizeof(RandomBuffer))
  {
    randomData.read(((char *)&RandomBuffer) + randomDataLen, sizeof(RandomBuffer) - randomDataLen);
    
    #ifdef _DEBUG
    if (randomData.gcount() < sizeof(RandomBuffer))
    {
      DEBUG("out of entropy, only read " << randomData.gcount() << "bytes");
    } else {
      DEBUG("read " << randomData.gcount() << " bytes that are equal to " << RandomBuffer);
    }
    #endif

    randomDataLen += randomData.gcount();
  }
  randomData.close();
  
  ZZ seed;
  seed = RandomBuffer;
  SetSeed(seed);

}

void gen_rnd_vec(Vec<ZZ_p>& v, long length)
{
  v.SetLength(length);

  for (long i = 1; i <= v.length(); i++)
  {
     v(i) = random_ZZ_p();
  }
}

void gen_rnd_vec(Vec<ZZ_p>& v)
{

  for (long i = 1; i <= v.length(); i++)
  {
    v(i) = random_ZZ_p();
  }
}

void gen_rnd_vec(Vec<ZZ_p>& v, long mod, ZZ p){

  ZZ m;
  m = mod; 
  ZZ_p::init(m);
  for (long i = 1; i <= v.length(); i++)
  {
    v(i) = random_ZZ_p();
  }
  ZZ_p::init(p);

}

void gen_rnd_mat(Mat<ZZ_p>& m, long rows, long cols)
{
  m.SetDims(rows,cols);

  // generate random v1 and v2
  for (long i = 1; i <= m.NumRows(); i++)
  {
    gen_rnd_vec(m(i));
  }

}

void gen_rnd_mat(Mat<ZZ_p>& m)
{
  // generate random v1 and v2
  for (long i = 1; i <= m.NumRows(); i++)
  {
    gen_rnd_vec(m(i));
  }
  
}

void gen_rnd_mat(Mat<ZZ_p>& m, long mod,ZZ p)
{
  // generate random v1 and v2
  for (long i = 1; i <= m.NumRows(); i++)
  {
    gen_rnd_vec(m(i),mod,p);
  }
  
}

#endif //NTL_RANDOM_HPP
