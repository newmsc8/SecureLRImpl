# ifndef NTL_RANDOM_HPP
#define NTL_RANDOM_HPP

#include <NTL/mat_ZZ_p.h>
#include <time.h>
#include<fstream>
#include<boost/lexical_cast.hpp>

using namespace std;
using namespace NTL;

void set_seed_prng()
{
  ZZ seed;
  seed = (ZZ)time(NULL);
  SetSeed(seed);
}

void gen_rnd_mat(Mat<ZZ_p>& m)
{	
  for (long i = 1; i <= m.NumRows(); i++)
		for (long j = 1; j <= m.NumCols(); j++)
			m(i,j) = random_ZZ_p();
}


void gen_rnd_mat(Mat<ZZ_p>& m, long bnd, ZZ q)
{
	ZZ zbnd(bnd);
	ZZ_p::init(zbnd);
  for (long i = 1; i <= m.NumRows(); i++)
		for (long j = 1; j <= m.NumCols(); j++)
			m(i,j) = random_ZZ_p();
  ZZ_p::init(q);
}

#endif //NTL_RANDOM_HPP
