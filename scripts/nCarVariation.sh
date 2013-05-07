#! /bin/bash

if [ $# -eq 0 ]; then
        echo "Usage: ./Filename arg1 arg2 ..."
        exit 1;
fi
echo "#NumberOfCars TotalPassangerReq. SatiesfiedPassangerReq UnsatiesfiedPassangerReq">../data/nCarVariation.dat

COUNTER=$1
let FINAL=COUNTER+1000
while [  $COUNTER -lt $FINAL ]; do
      


	cat ../src/config.cfg | sed "s/\(NUMBER_OF_CARS = \).*/\1 $COUNTER/" >1.cfg
	rm ../src/config.cfg
	cp 1.cfg config.cfg
	mv config.cfg ../src/config.cfg
	rm 1.cfg
	cd ../src
	make
	./sim config.cfg
	
	totalPassengerRequest=`tail -n+2 ../simdumps/servicePerLocation.dat |wc -l`
	
	satisfiedPassengerRequest=`tail -n+2 ../simdumps/servicePerLocation.dat |awk '{print $5}'| awk '{ sum+=$1} END {print sum}'`

	unsatisfiedPassengerRequest=$(( $totalPassengerRequest - $satisfiedPassengerRequest ))
	
	echo $COUNTER $totalPassengerRequest $satisfiedPassengerRequest $unsatisfiedPassengerRequest >>../data/nCarVariation.dat


      let COUNTER=COUNTER+20 
done

