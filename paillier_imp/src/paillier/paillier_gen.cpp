#include <fstream>
#include <gmp.h>
#include <NTL/mat_ZZ_p.h>
#include <SLA/ntl_random.hpp>
#include <SLA/linreg_files.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <paillier.h>

using namespace NTL;
using namespace std;

int main(int argc, char* argv[]) {
	//initiate variables
	long dim1, dim2, dim3;
	ofstream log("paillier_log.txt",ofstream::out);
	log<<"starting\n";
	dim1 = boost::lexical_cast<long>(argv[1]);
	dim2 = boost::lexical_cast<long>(argv[2]);
	dim3 = boost::lexical_cast<long>(argv[3]);
	ZZ q = boost::lexical_cast<ZZ>(argv[4]);
	ZZ_p::init(q);
	log<<"read input\n";
	Mat<ZZ_p> A_alice;
	Mat<ZZ_p> A_bob;
	Mat<ZZ_p> B_alice;
	Mat<ZZ_p> B_bob;
	Mat<ZZ_p> T_alice;
	
	log<<"alice generating\n";
	//alice random generation
	A_alice.SetDims(dim1,dim2);
	gen_rnd_mat(A_alice);
	B_alice.SetDims(dim2,dim3);
	gen_rnd_mat(B_alice);
	T_alice.SetDims(dim1,dim3);
	gen_rnd_mat(T_alice);

	log<<"bob generating\n";
	//bob random generation
	A_bob.SetDims(dim1,dim2);
	gen_rnd_mat(A_bob);
	B_bob.SetDims(dim2,dim3);
	gen_rnd_mat(B_bob);

	log<<"paillier\n";
	log.close();

	//paillier
	paillier_pubkey_t* pub;//The public key
   	paillier_prvkey_t* prv;//The private key 
	paillier_keygen((int)(q.size()), &pub, &prv,paillier_get_rand_devurandom);

	paillier_plaintext_t* pt;
	paillier_ciphertext_t* ct;

	//perform encryptions
	Mat<ZZ_p> enc_B_bob;
	enc_B_bob.SetDims(dim2,dim3);
	for(int r=1; r<=enc_B_bob.NumRows(); r++) {
		for(int c=1; c<=enc_B_bob.NumCols();c++) {
			pt=paillier_plaintext_from_ui(boost::lexical_cast<long>(B_bob(r,c)));
			ct = paillier_enc(NULL,pub,pt,paillier_get_rand_devurandom);
 			enc_B_bob(r,c) = boost::lexical_cast<ZZ_p>(paillier_ciphertext_to_bytes(sizeof(ct), ct ));
		}
	}

	Mat<ZZ_p> enc_A_bob;/*
	enc_A_bob.SetDims(dim1,dim2);
	for(int r=1; r<=enc_A_bob.NumRows(); r++) {
		for(int c=1; c<=enc_A_bob.NumCols();c++) {
			pt=paillier_plaintext_from_ui(boost::lexical_cast<long>(A_bob(r,c)));
 			enc_A_bob(r,c) = *paillier_enc(NULL,pub,pt,paillier_get_rand_devurandom);
		}
	}
*/
	Mat<ZZ_p> enc_T_alice;/*
	enc_T_alice.SetDims(dim1,dim2);
	for(int r=1; r<=enc_T_alice.NumRows(); r++) {
		for(int c=1; c<=enc_T_alice.NumCols();c++) {
			pt=paillier_plaintext_from_ui(boost::lexical_cast<long>(T_alice(r,c)));
 			enc_T_alice(r,c) = *paillier_enc(NULL,pub,pt,paillier_get_rand_devurandom);
		}
	}*/

	//get products
	
	Mat<ZZ_p> A_alice_B_bob;
	A_alice_B_bob.SetDims(dim2,dim2);
	mul(A_alice_B_bob,A_alice,enc_B_bob);

	Mat<ZZ_p> A_bob_B_alice;
	A_bob_B_alice.SetDims(dim2,dim2);
	mul(A_bob_B_alice, enc_A_bob, B_alice);

	Mat<ZZ_p> enc_C_bob;
	enc_C_bob.SetDims(dim2,dim2);
	add(enc_C_bob, A_alice_B_bob, A_bob_B_alice);
	sub(enc_C_bob, enc_C_bob, enc_T_alice);

	Mat<ZZ_p> C_bob;
	C_bob.SetDims(dim1,dim3);
	for(int r=1; r<=C_bob.NumRows(); r++) {
		for(int c=1; c<=C_bob.NumCols();c++) {
			ct = 
			pt = paillier_dec(0, pub, prv, *enc_C_bob(r,c));
			C_bob(r,c) = boost::lexical_cast<ZZ_p>(paillier_plaintext_to_str(pt));
		}
	}
}
