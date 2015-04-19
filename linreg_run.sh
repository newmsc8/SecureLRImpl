#!/bin/bash
BIN=./bin/linreg
MOD=999999999999999
MINUS1=100000000000000
SEED=100
PREC=10
LAMBDA=10000000000
DIM=100
PORT=7878
ALICE_HOST=127.0.0.1

if [[ ! -f $BIN ]];
then
mkdir -p $BIN
fi

case $1 in

pre)
$0 inputgen
$0 ti
;;


alice)
$BIN/linreg_alice $MOD $PORT $DIM $MINUS1
exit 0
;;

bob)
$BIN/linreg_bob $MOD $ALICE_HOST $PORT $DIM $MINUS1
exit 0
;;

ti)
$BIN/linreg_ti $MOD $DIM $PREC $LAMBDA
exit 0
;;

inputgen)
$BIN/linreg_inputgen $MOD $DIM $SEED
exit 0
;;

test)
$BIN/linreg_test $MOD $DIM
exit 0
;;

*)
  echo "Usage: $0 (alice|bob|ti|inputgen|test)"
  exit 2
  ;;

esac
