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
	ZZ_p in_prec = boost::lexical_cast<ZZ_p>(argv[7]);


	if (type == 1){
		Mat<ZZ_p> XR,YR;
		XR.SetDims(row,col);
		YR.SetDims(row,1);
		ifstream xr_file("x_file.txt");
		ifstream yr_file("y_file.txt");
		double d;
		for (int i=0; i<row; i++){
			for (int j=0; j<col; j++){
				xr_file >> d;
				XR[i][j] = (long)(d * 100000);
				mul(XR[i][j],XR[i][j],in_prec);
			}
			yr_file >> d;
			YR[i][0] = (long)(d * 100000);
			mul(YR[i][0],YR[i][0],in_prec);
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


		//cout<<"x_file"<<endl;
		ofstream x_file(XF,ios::trunc);
		x_file << XR;
		x_file.close();		
		//cout<<"xa_file"<<endl;
		ofstream xa_file(Y_ALICE, ios::trunc);
		xa_file << XA;
		xa_file.close();
		//cout<<"xb_file"<<endl;
		ofstream xb_file(Y_BOB, ios::trunc);
		xb_file << XB;
		xb_file.close();
		//cout<<"xt_file"<<endl;
		ofstream xt_file(XTF,ios::trunc);
		xt_file << XT;
		xt_file.close();		
		//cout<<"xta_file"<<endl;
		ofstream xta_file(X_ALICE, ios::trunc);
		xta_file << XTA;
		xta_file.close();
		//cout<<"xtb_file"<<endl;
		ofstream xtb_file(X_BOB, ios::trunc);
		xtb_file << XTB;
		xtb_file.close();
		//cout<<"xtfa_file"<<endl;
		ofstream xtf_alice(XTF_ALICE, ios::trunc);
		xtf_alice << XTA;
		xtf_alice.close();
		//cout<<"xtfb_file"<<endl;
		ofstream xtf_bob(XTF_BOB, ios::trunc);
		xtf_bob << XTB;
		xtf_bob.close();
		//cout<<"y_file"<<endl;
		ofstream y_file(YF, ios::trunc);
		y_file << YR;
		y_file.close();
		
		
		Mat<ZZ_p> YFA,YFB;
		YFA.SetDims(row,1);
		YFB.SetDims(row,1);
		set_seed_prng();
		//cout<<"Gen Random Matrix"<<endl;
		gen_rnd_mat(YFA);
		//cout<<"Subtracting"<<endl;
		sub(YFB,YR,YFA);
		//cout<<"writing yfa and yfb files"<<endl;
		ofstream yf_alice(YF_ALICE, ios::trunc);
		ofstream yf_bob(YF_BOB, ios::trunc);
		yf_alice << YFA;
		yf_bob << YFB;
		yf_alice.close();
		yf_bob.close();
		//cout<<"All Done"<<endl;

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
		TR1A[0][0] = 100000;
		TR1B[0][0] = 100000;
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

