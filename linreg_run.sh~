#!/bin/bash
BIN=./bin/linreg
MOD=9999999999999999999999999999999999999999999999999999999
MINUS1=100000000000000000000000000000000000
SEED=1000
PREC=100000000000000000000
LAMBDA=10000000000000000000000000
ROW=25180
COL=35
COLA=6
DIM=10
PORT=7878
ALICE_HOST=127.0.0.1

if [[ ! -f $BIN ]];
then
mkdir -p $BIN
fi

case $1 in

alice)
$BIN/linreg_alice $2 $MOD $PORT $ROW $COL $MINUS1
exit 0
;;

bob)
$BIN/linreg_bob $2 $MOD $ALICE_HOST $PORT $ROW $COL $MINUS1 $PREC
exit 0
;;

ti)
$BIN/linreg_ti $2 $MOD $ROW $COL $PREC $LAMBDA
exit 0
;;

input)
$BIN/linreg_input $2 $MOD $PREC $ROW $COL $COLA 
exit 0
;;

test)
$BIN/linreg_test $MOD
exit 0
;;

sub)
$BIN/linreg_sub $2 $MOD $PREC
exit 0
;;

mul)
$BIN/linreg_ti $2 $MOD $ROW $COL $PREC $LAMBDA
$BIN/linreg_alice $2 $MOD $PORT $ROW $COL $MINUS1 &
sleep 5
$BIN/linreg_bob $2 $MOD $ALICE_HOST $PORT $ROW $COL $MINUS1 $PREC
exit 0
;;

tr)
$BIN/linreg_ti 2 $MOD $ROW $COL $PREC $LAMBDA
$BIN/linreg_alice 2 $MOD $PORT $ROW $COL $MINUS1 &
sleep 0.5
$BIN/linreg_bob 2 $MOD $ALICE_HOST $PORT $ROW $COL $MINUS1 $PREC
$BIN/linreg_sub 1 $MOD $PREC
$BIN/linreg_ti 3 $MOD $ROW $COL $PREC $LAMBDA
$BIN/linreg_alice 3 $MOD $PORT $ROW $COL $MINUS1 &
sleep 0.5
$BIN/linreg_bob 3 $MOD $ALICE_HOST $PORT $ROW $COL $MINUS1 $PREC
$BIN/linreg_test $MOD
exit 0
;;

inv)
$BIN/linreg_ti 4 $MOD $ROW $COL $PREC $LAMBDA
$BIN/linreg_alice 4 $MOD $PORT $ROW $COL $MINUS1 &
sleep 0.5
$BIN/linreg_bob 4 $MOD $ALICE_HOST $PORT $ROW $COL $MINUS1 $PREC
$BIN/linreg_sub 2 $MOD $PREC
$BIN/linreg_ti 5 $MOD $ROW $COL $PREC $LAMBDA
$BIN/linreg_alice 5 $MOD $PORT $ROW $COL $MINUS1 &
sleep 0.5
$BIN/linreg_bob 5 $MOD $ALICE_HOST $PORT $ROW $COL $MINUS1 $PREC
$BIN/linreg_test $MOD
exit 0
;;


all)
$BIN/linreg_input 1 $MOD $PREC $ROW $COL $COLA 
$BIN/linreg_ti 1 $MOD $ROW $COL $PREC $LAMBDA
$BIN/linreg_alice 1 $MOD $PORT $ROW $COL $MINUS1 &
sleep 2
$BIN/linreg_bob 1 $MOD $ALICE_HOST $PORT $ROW $COL $MINUS1 $PREC
$BIN/linreg_input 2 $MOD $PREC $ROW $COL $COLA 
for i in {1..50}
do
	$BIN/linreg_ti 2 $MOD $ROW $COL $PREC $LAMBDA
	$BIN/linreg_alice 2 $MOD $PORT $ROW $COL $MINUS1 &
	sleep 2
	$BIN/linreg_bob 2 $MOD $ALICE_HOST $PORT $ROW $COL $MINUS1 $PREC
	$BIN/linreg_sub 1 $MOD $PREC
	$BIN/linreg_ti 3 $MOD $ROW $COL $PREC $LAMBDA
	$BIN/linreg_alice 3 $MOD $PORT $ROW $COL $MINUS1 &
	sleep 2
	$BIN/linreg_bob 3 $MOD $ALICE_HOST $PORT $ROW $COL $MINUS1 $PREC
done
$BIN/linreg_input 3 $MOD $PREC $ROW $COL $COLA 
for i in {1..50}
do
	$BIN/linreg_ti 4 $MOD $ROW $COL $PREC $LAMBDA
	$BIN/linreg_alice 4 $MOD $PORT $ROW $COL $MINUS1 &
	sleep 2
	$BIN/linreg_bob 4 $MOD $ALICE_HOST $PORT $ROW $COL $MINUS1 $PREC
	$BIN/linreg_sub 2 $MOD $PREC
	$BIN/linreg_ti 5 $MOD $ROW $COL $PREC $LAMBDA
	$BIN/linreg_alice 5 $MOD $PORT $ROW $COL $MINUS1 &
	sleep 2
	$BIN/linreg_bob 5 $MOD $ALICE_HOST $PORT $ROW $COL $MINUS1 $PREC
done
$BIN/linreg_ti 6 $MOD $ROW $COL $PREC $LAMBDA
$BIN/linreg_alice 6 $MOD $PORT $ROW $COL $MINUS1 &
sleep 2
$BIN/linreg_bob 6 $MOD $ALICE_HOST $PORT $ROW $COL $MINUS1 $PREC
$BIN/linreg_ti 7 $MOD $ROW $COL $PREC $LAMBDA
$BIN/linreg_alice 7 $MOD $PORT $ROW $COL $MINUS1 &
sleep 2
$BIN/linreg_bob 7 $MOD $ALICE_HOST $PORT $ROW $COL $MINUS1 $PREC
$BIN/linreg_test $MOD
exit 0
;;






*)
  echo "Usage: $0 (alice|bob|ti|input|test)"
  exit 2
  ;;

esac
