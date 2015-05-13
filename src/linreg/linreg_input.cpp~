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
	long row = boost::lexical_cast<long>(argv[4]);
	long col = boost::lexical_cast<long>(argv[5]);	  
	long colA = boost::lexical_cast<long>(argv[6]);


	if (type == 1){
		Mat<ZZ_p> XR,YR;
		XR.SetDims(row,col);
		YR.SetDims(row,1);
		ifstream xr_file("x_file.txt");
		ifstream yr_file("y_file.txt");
		long k;
		for (int i=0; i<row; i++){
			for (int j=0; j<col; j++){
				xr_file >> k;
				XR[i][j] = k;
				mul(XR[i][j],XR[i][j],prec);
			}
			yr_file >> k;
			YR[i][0] = k;
			mul(YR[i][0],YR[i][0],prec);
		}
		xr_file.close();
		yr_file.close();
		Mat<ZZ_p> XA,XB,XT,XTA,XTB;
		XA.SetDims(row,col);
		XB.SetDims(row,col);
		XT.SetDims(col,row);
		XTA.SetDims(col,row);
		XTB.SetDims(col,row);

		for (int i=0;i<row;i++)
			for (int j=0;j<colA;j++)
				XA[i][j] = XT[j][i] = XTA[j][i] = XR[i][j];
			
	
		for (int i=0;i<row;i++)
			for (int j=colA;j<col;j++)
				XB[i][j] = XT[j][i] = XTB[j][i] = XR[i][j];

		ofstream x_file(XF,ios::trunc);
		ofstream xa_file(Y_ALICE, ios::trunc);
		ofstream xb_file(Y_BOB, ios::trunc);
		ofstream xt_file(XTF,ios::trunc);
		ofstream xta_file(X_ALICE, ios::trunc);
		ofstream xtb_file(X_BOB, ios::trunc);
		
		ofstream xtf_alice(XTF_ALICE, ios::trunc);
		ofstream xtf_bob(XTF_BOB, ios::trunc);

		ofstream y_file(YF, ios::trunc);
		x_file << XR;
		xa_file << XA;
		xb_file << XB;
		xt_file << XT;
		xta_file << XTA;
		xtb_file << XTB;
		xtf_alice << XTA;
		xtf_bob << XTB;
		y_file << YR;
		x_file.close();		
		xa_file.close();
		xb_file.close();
		xt_file.close();		
		xta_file.close();
		xtb_file.close();
		xtf_alice.close();
		xtf_bob.close();
		y_file.close();

		Mat<ZZ_p> YFA,YFB;
		YFA.SetDims(row,1);
		YFB.SetDims(row,1);
		set_seed_prng();
		gen_rnd_mat(YFA);
		sub(YFB,YR,YFA);
		ofstream yf_alice(YF_ALICE, ios::trunc);
		ofstream yf_bob(YF_BOB, ios::trunc);
		yf_alice << YFA;
		yf_bob << YFB;
		yf_alice.close();
		yf_bob.close();

	}

	if (type == 2){
		Mat<ZZ_p> TRA,TRB,TR1A,TR1B,Z1A,Z1B;
	
		std::ifstream z1_alice(Z1_ALICE);
		z1_alice >> Z1A;
		z1_alice.close();

		std::ifstream z1_bob(Z1_BOB);
		z1_bob >> Z1B;
		z1_bob.close();

		TRA.SetDims(1,1);
		TRB.SetDims(1,1);
		TR1A.SetDims(1,1);
		TR1B.SetDims(1,1);		
		ZZ_p sumA(0),sumB(0);		
		for (int i=0; i<col; i++){
			add(sumA,sumA,Z1A[i][i]);
			add(sumB,sumB,Z1B[i][i]);
		}	
		cout << sumA + sumB << endl;
		TRA[0][0] = sumA;
		TRB[0][0] = sumB;
		TR1A[0][0] = 100000000000;
		TR1B[0][0] = 100000000000;
		ofstream tr_alice(TR_ALICE,ios::trunc);
		tr_alice << TRA; 
		tr_alice.close();

		ofstream tr_bob(TR_BOB,ios::trunc);
		tr_bob << TRB; 
		tr_bob.close();


		ofstream tr1_alice(TR1_ALICE,ios::trunc);
		tr1_alice << TR1A; 
		tr1_alice.close();

		ofstream tr1_bob(TR1_BOB,ios::trunc);
		tr1_bob << TR1B; 
		tr1_bob.close();
	}

	if (type == 3){
		Mat<ZZ_p> Z2A,Z2B,TR1A,TR1B;
		ident(Z2A,col);
		ident(Z2B,col);

		//Z2A.SetDims(col,col);
		//Z2B.SetDims(col,col);
		
		std::ifstream tr1_alice(TR1_ALICE);
		tr1_alice >> TR1A;
		tr1_alice.close();

		std::ifstream tr1_bob(TR1_BOB);
		tr1_bob >> TR1B;
		tr1_bob.close();
		
		mul(Z2A,Z2A,TR1A[0][0]);
		mul(Z2B,Z2B,TR1B[0][0]);
		
		ofstream z2_alice(Z2_ALICE,ios::trunc);
		z2_alice << Z2A; 
		z2_alice.close();

		ofstream z2_bob(Z2_BOB,ios::trunc);
		z2_bob << Z2B; 
		z2_bob.close();
			

	}

}

