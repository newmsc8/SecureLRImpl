//
// innerprod_bob.cpp
// ~~~~~~~~~~~~~~~
//Inner product bob
//

//#define _DEBUG 1

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <NTL/mat_ZZ_p.h>
#include <NTL/mat_ZZ.h>
//#include <NTL/vec_ZZ_p.h>
#include <SLA/linreg_params.hpp>
#include <SLA/debug.hpp>
#include <SLA/protocol_message.hpp>
#include <SLA/protocol_session.hpp>
#include <sys/time.h>
#include <time.h>

using namespace NTL;

//typedef boost::shared_ptr< Vec<ZZ_p> > vector_ptr;

class innerprod_bob
  : public twoparty_runner,
    public boost::enable_shared_from_this<innerprod_bob>
{
public:
  innerprod_bob(const char* d, const char* x_file, const char* y_file, const char* a_file, const char* b_file, const char* c_file, char* out_file, const char* xy_file, const char* r_file, const char* rp_file)
  {


	dim = boost::lexical_cast<long>(d);
	XB.SetDims(dim,dim);
	YB.SetDims(dim,dim);
	AB.SetDims(dim,dim);
	BB.SetDims(dim,dim);
	CB.SetDims(dim,dim);
	XBYB.SetDims(dim,dim);
	out_bob = out_file;
    //loading files
    std::ifstream x_bob(x_file);
    if (x_bob.is_open())
    {
      x_bob >> XB;
    } else {
      std::cerr << "Failed to Open TI data file: " << x_file << std::endl;
    }
    x_bob.close();
    DEBUG("loaded x value xa: " << XB);
    
    std::ifstream y_bob(y_file);
    if (y_bob.is_open())
    {
      y_bob >> YB;
    } else {
      std::cerr << "Failed to Open TI data file: " << y_file << std::endl;
    }
    y_bob.close();
    DEBUG("loaded y value ya: " << YB);

    std::ifstream a_bob(a_file);
    if (a_bob.is_open())
    {
      a_bob >> AB;
    } else {
      std::cerr << "Failed to Open TI data file: " << a_file << std::endl;
    }
    a_bob.close();
    DEBUG("loaded a value aa: " << AB);

    std::ifstream b_bob(b_file);
    if (b_bob.is_open())
    {
      b_bob >> BB;
    } else {
      std::cerr << "Failed to Open TI data file: " << b_file << std::endl;
    }
    b_bob.close();
    DEBUG("loaded b value ba: " << BB);

    std::ifstream c_bob(c_file);
    if (c_bob.is_open())
    {
      c_bob >> CB;
    } else {
      std::cerr << "Failed to Open TI data file: " << c_file << std::endl;
    }
    c_bob.close();
    DEBUG("loaded c value ca: " << CB);

	std::ifstream xy_bob(xy_file);
	xy_bob >> XBYB;
	xy_bob.close();


	std::ifstream r_bob(r_file);
    r_bob >> RB;
    r_bob.close();

	std::ifstream rp_bob(rp_file);
    rp_bob >> RPB;
    rp_bob.close();


/*
    //loading TI values
    std::ifstream ti_bob(ti_file);

    if (ti_bob.is_open())
    {
      ti_bob >> y0;
      ti_bob >> s0;
    } else {
      std::cout << "Failed to Open TI data file: " << ti_file << std::endl;
    }
    
    ti_bob.close();

    DEBUG("loaded TI values y0: " << y0 << " and s0: " << s0);

    //loading input vector
    std::ifstream input_bob(input_file);

    if (input_bob.is_open())
    {
      vector_ptr input(new Vec<ZZ_p>);
      input_bob >> *input;
      y = input;
    } else {
      std::cout << "Failed to Open input file: " << input_file << std::endl;
    }

    input_bob.close(); 
    DEBUG("loaded input y: " << y);
*/

  }

  
/*
  innerprod_bob(const char* ti_file, vector_ptr input)
  {

    //loading TI values
    std::ifstream ti_bob(ti_file);

    if (ti_bob.is_open())
    {
      ti_bob >> y0;
      ti_bob >> s0;
    } else {
      std::cout << "Failed to Open TI data file: " << ti_file << std::endl;
    }

    ti_bob.close();

    DEBUG("loaded TI values y0: " << y0 << " and s0: " << s0);

    y = input;

    DEBUG("loaded input y: " << *y);
  }
 
*/
  bool msg_xayb()
  {



	Mat<ZZ_p> XBAB,YBBB;
	XBAB.SetDims(dim,dim);
	YBBB.SetDims(dim,dim);
	//XAAA.SetDims(dim,dim);
	//YABA.SetDims(dim,dim);
	//DA.SetDims(dim,dim);
	//DB.SetDims(dim,dim);

	sub(XBAB,XB,AB);
	sub(YBBB,YB,BB);

    protocol_message_ptr msg(new protocol_message);

    //*(input_msg) >> XBAB >> YBBB;

	//sub(XAAA,XA,AA);
	//sub(YABA,YA,BA);
	
	//gen_rnd_mat(DA);

	//mul(YBBB,YBBB,AA);
	//mul(XBAB,XBAB,BA);

	//mul(DB,XA,YA);
	//add(DB,DB,YBBB);
	//add(DB,DB,XBAB);
	//sub(DB,DB,DA);
	
	*(msg) << XBAB << std::endl;
	*(msg) << YBBB << std::endl;
	//*(msg) << DB << std::endl;
	
	
	//add(CA,CA,DA);

	//ofstream a_out(out_alice, ios::trunc);
  	//DEBUG("Writing " << argv[3]);
  	//if (a_out.is_open())
  	//{
   	//  a_out << CA;
  	//} else {
    //  std::cerr << "Failed to Open/Create file " << out_alice << std::endl;
  	//}
  	//a_out.close();

    //DEBUG("received message y1: " << );   


    //add(x1,*x,x0);
    
    //u = random_ZZ_p();
    //InnerProduct(u1, *x, y1);
    //sub(u1,u1,u);

    //*(msg) << x1 << std::endl;
    //*(msg) << u1 << std::endl;
    
    //DEBUG("sending message: " << (*msg));
    send_message(msg);
















/*
    Vec<ZZ_p> y1;   
    protocol_message_ptr msg(new protocol_message);

    //compute message y1
    sub(y1,*y,y0);

    *(msg) << y1;
   
    DEBUG("msg.max_body_length: " << msg->body_length()); 
    DEBUG("y1 : " << y1); 
    DEBUG("sending message: " << *(msg)); 
    send_message(msg);
*/
    return true;
  }

  bool msg_v(protocol_message_ptr msg)
  {
	Mat<ZZ_p> XAAA,YABA,DB,ZA;
	//XBAB.SetDims(dim,dim);
	//YBBB.SetDims(dim,dim);
	XAAA.SetDims(dim,dim);
	YABA.SetDims(dim,dim);
	//DA.SetDims(dim,dim);
	DB.SetDims(dim,dim);
	ZA.SetDims(dim,dim);

    //protocol_message_ptr msg(new protocol_message);

    *(msg) >> XAAA >> YABA >> DB >> ZA;

	mul(XAAA,XAAA,YB);
	mul(YABA,XB,YABA);
	//mul(XB,XB,YB);
	
	add(CB,CB,DB);
	add(CB,CB,XBYB);
	add(CB,CB,XAAA);
	add(CB,CB,YABA);


	add(ZA,ZA,CB);
	add(ZA,ZA,RB);

	Mat<ZZ> CP;
	CP.SetDims(dim,dim);
	for (long i=0;i<dim;i++)
	  for (long j=0;j<dim;j++){
		CP[i][j]=rep(ZA[i][j]);
		ZA[i][j]=rem(CP[i][j],10);
	  }
	
	
	add(CB,CB,RPB);
	sub(CB,CB,ZA);
	ZZ_p one(1);
	ZZ_p ten(10);
	div(one,one,ten);
	mul(CB,CB,one);

	
	//gen_rnd_mat(DA);

	//mul(YBBB,YBBB,AA);
	//mul(XBAB,XBAB,BA);

	//mul(DB,XA,YA);
	//add(DB,DB,YBBB);
	//add(DB,DB,XBAB);
	//sub(DB,DB,DA);
	
	//*(msg) << XAAA << std::endl;
	//*(msg) << YABA << std::endl;
	//*(msg) << DB << std::endl;
	
	
	//add(CA,CA,DA);

	std::ofstream b_out(out_bob, std::ios::trunc);
  	//DEBUG("Writing " << argv[3]);
  	if (b_out.is_open())
  	{
   	  b_out << CB;
  	} else {
      std::cerr << "Failed to Open/Create file " << out_bob << std::endl;
  	}
  	b_out.close();

    //DEBUG("received message y1: " << );   


    //add(x1,*x,x0);
    
    //u = random_ZZ_p();
    //InnerProduct(u1, *x, y1);
    //sub(u1,u1,u);

    //*(msg) << x1 << std::endl;
    //*(msg) << u1 << std::endl;
    
    //DEBUG("sending message: " << (*msg));
    //send_message(msg);





/*
    ZZ_p u1;
    Vec<ZZ_p> x1;
    
    *(msg) >> x1;
    *(msg) >> u1;
    
    DEBUG("received x1: " << x1 << " and u1: " << u1);
    
    InnerProduct(v, x1, y0);
    add(v,v,u1);
    sub(v,v,s0);
*/    
    gettimeofday(&now, NULL);
    exec_time = now.tv_sec - then.tv_sec + 1e-6 * (now.tv_usec - then.tv_usec); 
    std::cout << "Protocol execution time: " << exec_time << std::endl;

    return true;
  }

  void protocol_start()
  {
    gettimeofday(&then, NULL);
    msg_xayb();  
  }

  void receive_msg(protocol_message_ptr msg)
  {
    msg_v(msg);
    terminate_protocol();
  }

  //ZZ_p output()
  //{
  //  return v;
  //}

private:
//ZZ_p s0,v;
//Vec<ZZ_p> y0;
//vector_ptr y;
Mat<ZZ_p> XB,YB,AB,BB,CB,XBYB,RB,RPB;
long dim;
char* out_bob;
struct timeval then, now;
double exec_time;
};

//typedef boost::shared_ptr<innerprod_bob> innerprod_bob_ptr;
