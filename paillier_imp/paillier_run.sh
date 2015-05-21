#!/bin/bash
BIN=./bin/paillier
#MOD=9999999999999999999999999999999999999999999999999999999
#ROW=25180
#COL=35
MOD=2
ROW=5
COL=5

if [[ ! -f $BIN ]];
then
mkdir -p $BIN
fi

case $1 in

run)
echo "Running "$BIN"/paillier_gen"
$BIN/paillier_gen $ROW $COL $ROW $MOD
exit 0
;;

*)
  echo "Usage: $0 (pailler_gen)"
  exit 2
  ;;

esac
