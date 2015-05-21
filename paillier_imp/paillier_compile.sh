#$BIN/bash
BIN=./bin/paillier
SRC=./src/paillier
SLA=./include/
BOOST=../boost_1_58_0
NTL=/usr/local/include/
PAIL=../libpaillier-0.8/
GMP_LIB=/usr/local/lib/libgmp.a
NTL_LIB=/usr/local/lib/libntl.a
PAIL_LIB=/usr/local/lib/libpaillier.a

if [[ ! -f $BIN ]];
then
mkdir -p $BIN
fi

case $1 in

all)
echo "Compiling "$SRC"/paillier_gen.cpp"
g++ -I $NTL -I $BOOST -I $SLA -I $PAIL -m64 -o $BIN/paillier_gen $SRC/paillier_gen.cpp $NTL_LIB $GMP_LIB $PAIL_LIB
exit 0
;;


*)
    echo "Usage: $0 {paillier_gen}"
    exit 2
    ;;

esac
