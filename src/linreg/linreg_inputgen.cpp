// Bernardo's Code :)
//Generates random inputs for the linreg protocol
// Namely, XA, XB, YA, YB
// It also computes XA*YA and XB*YB in here (preprocessing) to reduce runtime in the online phase


#include <fstream>
#include <SLA/linreg_files.hpp>
#include <NTL/mat_ZZ_p.h>
#include <SLA/ntl_random.hpp>
#include <boost/lexical_cast.hpp>

using namespace NTL;
using namespace std;

int main(int argc, char* argv[])
{
  ZZ q = boost::lexical_cast<ZZ>(argv[1]);
  ZZ_p::init(q);
  long dim = boost::lexical_cast<long>(argv[2]);
	long bnd = boost::lexical_cast<long>(argv[3]);
  set_seed_prng();

	Mat<ZZ_p> X,XA,XB;
  X.SetDims(dim,dim);
	XA.SetDims(dim,dim);
	XB.SetDims(dim,dim);
  gen_rnd_mat(X,2 * bnd - 1,q);
	for (long i = 0; i<dim; i++)
		for (long j = 0; j<dim; j++)
			X[i][j] = X[i][j] - bnd + 1;
	gen_rnd_mat(XA);
	sub(XB,X,XA);
	ofstream x_alice(X_ALICE, ios::trunc);
	ofstream x_bob(X_BOB, ios::trunc);
	x_alice << XA;
	x_bob << XB;
	x_alice.close();
	x_bob.close();

	Mat<ZZ_p> Y,YA,YB;
  Y.SetDims(dim,dim);
	YA.SetDims(dim,dim);
	YB.SetDims(dim,dim);
  gen_rnd_mat(Y,2 * bnd - 1,q);
	for (long i = 0; i<dim; i++)
		for (long j = 0; j<dim; j++)
			Y[i][j] = Y[i][j] - bnd + 1;
	gen_rnd_mat(YA);
	sub(YB,Y,YA);
	ofstream y_alice(Y_ALICE, ios::trunc);
	ofstream y_bob(Y_BOB, ios::trunc);
	y_alice << YA;
	y_bob << YB;
	y_alice.close();
	y_bob.close();

	mul(X,X,Y);
	ofstream res_file(OUTPUT, ios::trunc);	
  res_file << X;
  res_file.close();

  mul(X,XA,YA);
  ofstream xy_alice(XY_ALICE, ios::trunc);
  xy_alice << X;
  xy_alice.close();

  mul(X,XB,YB);
  ofstream xy_bob(XY_BOB, ios::trunc);
  xy_bob << X;
  xy_bob.close();

}

