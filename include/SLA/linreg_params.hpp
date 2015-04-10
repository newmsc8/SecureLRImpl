#ifndef INNERPROD_PARAMS_HPP
#define INNERPROD_PARAMS_HPP
//Parameters for the Inner Product protocol

//Order q of the field F_q over which vectors are defined
#define MOD 1000000000000000

//Number of digits of the decimal representation of the order MOD
#define MOD_SIZE 3

//Maximum vector length supported
#define MAX_MAT_DIM 10000

//Maximum protocol message body length
// 
//This value is basically determined by the maximum vector lenght MAX_VEC_LENGTH
//and the number digits MOD_SIZE of the decimal representation of the field order MOD
//
//The protocol's largest message is of the form v\nb where "v" is a vector of field elements
//and "b" is a single field element, where v is represented as [v(1) v(2) v(3) ...v(MAX_VEC_LENGTH)].
// MAX_BODY_LENGTH = 1+MAX_VEC_LENGTH*(MOD_SIZE+1)+1+MOD_SIZE
#define MAX_BODY_LENGTH MAX_MAT_DIM * MAX_MAT_DIM * (MOD_SIZE+2)

#endif
