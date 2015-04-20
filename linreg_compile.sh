#$BIN/bash
BIN=./bin/linreg
SRC=./src/linreg
SLA=./include/
BOOST=../boost_1_55_0
NTL=/usr/local/include/
GMP_LIB=/usr/local/lib/libgmp.a
NTL_LIB=/usr/local/lib/libntl.a

if [[ ! -f $BIN ]];
then
mkdir -p $BIN
fi

case $1 in

all)
$0 alice
$0 bob
$0 inputgen
$0 ti
$0 test
;;

ti)
echo "Compiling "$SRC"/linreg_ti.cpp"
c++ -I $NTL -I $BOOST -I $SLA -m64 -o $BIN/linreg_ti $SRC/linreg_ti.cpp $NTL_LIB $GMP_LIB
exit 0
;;

inputgen)
echo "Compiling "$SRC"/linreg_inputgen.cpp"
c++ -I $NTL -I $BOOST -I $SLA -m64 -o $BIN/linreg_inputgen $SRC/linreg_inputgen.cpp $NTL_LIB $GMP_LIB
exit 0
;;

bob)
echo "Compiling "$SRC"/linreg_bob.cpp"
c++ -I $NTL -I $BOOST -I $SLA -m64 -o $BIN/linreg_bob $SRC/linreg_bob.cpp $BOOST/stage/lib/libboost_thread.a $BOOST/stage/lib/libboost_system.a -lrt -lpthread $NTL_LIB $GMP_LIB
exit 0
;;

alice)
echo "Compiling "$SRC"/linreg_alice.cpp"
c++ -I $NTL -I $BOOST -I $SLA -m64 -o $BIN/linreg_alice $SRC/linreg_alice.cpp $BOOST/stage/lib/libboost_system.a $NTL_LIB $GMP_LIB
exit 0
;;

test)
echo "Compiling "$SRC"/linreg_test.cpp"
c++ -I $NTL -I $BOOST -I $SLA -m64 -o $BIN/linreg_test $SRC/linreg_test.cpp $NTL_LIB $GMP_LIB
exit 0
;;


*)
    echo "Usage: $0 {bob|alice|ti|inputgen|test}"
    exit 2
    ;;

esac
