//
// linreg_alice.cpp
// ~~~~~~~~~~~~~~~
//

//#define _DEBUG 1

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
//#include <NTL/vec_ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <SLA/linreg_params.hpp>
#include <SLA/debug.hpp>
#include <SLA/protocol_message.hpp>
#include <SLA/protocol_session.hpp>
#include <SLA/ntl_random.hpp>

using namespace NTL;

//typedef boost::shared_ptr< Mat<ZZ_p> > matrix_ptr; 

class linreg_alice
  : public twoparty_runner,
    public boost::enable_shared_from_this<linreg_alice>
{
public:
  linreg_alice(const char* d, const char* x_file, const char* y_file, const char* a_file, const char* b_file, const char* c_file, char* out_file, const char* xy_file, const char* r_file, const char* rp_file)
  {

	dim = boost::lexical_cast<long>(d);
	XA.SetDims(dim,dim);
	YA.SetDims(dim,dim);
	AA.SetDims(dim,dim);
	BA.SetDims(dim,dim);
	CA.SetDims(dim,dim);
	XAYA.SetDims(dim,dim);
	RA.SetDims(dim,dim);
	RPA.SetDims(dim,dim);
	out_alice = out_file;
    //loading files
    std::ifstream x_alice(x_file);
    if (x_alice.is_open())
    {
      x_alice >> XA;
    } else {
      std::cerr << "Failed to Open TI data file: " << x_file << std::endl;
    }
    x_alice.close();
    DEBUG("loaded x value xa: " << XA);
    
    std::ifstream y_alice(y_file);
    if (y_alice.is_open())
    {
      y_alice >> YA;
    } else {
      std::cerr << "Failed to Open TI data file: " << y_file << std::endl;
    }
    y_alice.close();
    DEBUG("loaded y value ya: " << YA);

    std::ifstream a_alice(a_file);
    if (a_alice.is_open())
    {
      a_alice >> AA;
    } else {
      std::cerr << "Failed to Open TI data file: " << a_file << std::endl;
    }
    a_alice.close();
    DEBUG("loaded a value aa: " << AA);

    std::ifstream b_alice(b_file);
    if (b_alice.is_open())
    {
      b_alice >> BA;
    } else {
      std::cerr << "Failed to Open TI data file: " << b_file << std::endl;
    }
    b_alice.close();
    DEBUG("loaded b value ba: " << BA);

    std::ifstream c_alice(c_file);
    if (c_alice.is_open())
    {
      c_alice >> CA;
    } else {
      std::cerr << "Failed to Open TI data file: " << c_file << std::endl;
    }
    c_alice.close();
    DEBUG("loaded c value ca: " << CA);

    std::ifstream xy_alice(xy_file);
	xy_alice >> XAYA;
	xy_alice.close();


	std::ifstream r_alice(r_file);
    r_alice >> RA;
    r_alice.close();
	
	std::ifstream rp_alice(rp_file);
    rp_alice >> RPA;
    rp_alice.close();


    //loading input vector
    //std::ifstream input_alice(input_file);

/*
    if (input_alice.is_open())
    {
      vector_ptr input(new Vec<ZZ_p>); 
      input_alice >> *input;
      x=input;
    } else {
      std::cerr << "Failed to Open input file: " << input_file << std::endl;
    }

    input_alice.close();
    DEBUG("loaded input x: " << *x);
*/    
    //RNG seed MUST be set in the calling program if you comment this out
    //set NTL PRGN
    //set_seed_prng();
  }

/*
  innerprod_alice(const char* ti_file, vector_ptr input)
  {
    //loading TI values
    std::ifstream ti_alice(ti_file);

    if (ti_alice.is_open())
    {
      ti_alice >> x0;
    } else {
      std::cerr << "Failed to Open TI data file: " << ti_file << std::endl;
    }

    ti_alice.close();
    DEBUG("loaded ti value x0: " << x0);

    x = input;

    DEBUG("Loaded input value x:i " << *x);

    //RNG seed MUST be set in the calling program if you comment this out
    //set NTL PRGN
    //set_seed_prng();
  }
 
*/

  bool msg_w(protocol_message_ptr input_msg)
  {
    //ZZ_p u1;
    //Vec<ZZ_p> x1,y1;

	Mat<ZZ_p> XBAB,YBBB,XAAA,YABA,DA,DB;
	XBAB.SetDims(dim,dim);
	YBBB.SetDims(dim,dim);
	XAAA.SetDims(dim,dim);
	YABA.SetDims(dim,dim);
	DA.SetDims(dim,dim);
	DB.SetDims(dim,dim);

    protocol_message_ptr msg(new protocol_message);

    *(input_msg) >> XBAB >> YBBB;

	sub(XAAA,XA,AA);
	sub(YABA,YA,BA);
	
	gen_rnd_mat(DA);

	mul(YBBB,AA,YBBB);
	mul(XBAB,XBAB,BA);

	//mul(DB,XA,YA);
	add(DB,XAYA,YBBB);
	add(DB,DB,XBAB);
	sub(DB,DB,DA);
	
	*(msg) << XAAA << std::endl;
	*(msg) << YABA << std::endl;
	*(msg) << DB << std::endl;
	
	
	add(CA,CA,DA);

	add(RA,RA,CA);
	*(msg) << RA <<std::endl;

	add(CA,CA,RPA);
	ZZ_p one(1);
	ZZ_p ten(10);
	div(one,one,ten);
	mul(CA,CA,one);

	std::ofstream a_out(out_alice, std::ios::trunc);
  	//DEBUG("Writing " << argv[3]);
  	if (a_out.is_open())
  	{
   	  a_out << CA;
  	} else {
      std::cerr << "Failed to Open/Create file " << out_alice << std::endl;
  	}
  	a_out.close();

    //DEBUG("received message y1: " << );   


    //add(x1,*x,x0);
    
    //u = random_ZZ_p();
    //InnerProduct(u1, *x, y1);
    //sub(u1,u1,u);

    //*(msg) << x1 << std::endl;
    //*(msg) << u1 << std::endl;
    
    //DEBUG("sending message: " << (*msg));
    send_message(msg);



    
    //std::cout << "OUTPUT u: " << u << endl;
    return true;
  }
   
  void protocol_start()
  {
    DEBUG("protocol started\n");
  }

  void receive_msg(protocol_message_ptr msg) 
  {
    msg_w(msg);
    //terminate_protocol();
  }
  
//  ZZ_p output()
//  {
//    return u;
//  }
private:
Mat<ZZ_p> XA,YA,AA,BA,CA,XAYA,RA,RPA;
long dim;
char* out_alice;
//vector_ptr x;
//ZZ_p u;
};

//typedef boost::shared_ptr<innerprod_alice> innerprod_alice_ptr;
//----------------------------------------------------------------------
