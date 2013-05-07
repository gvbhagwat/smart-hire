#! /bin/bash
echo "#Time Count" >../data/passengerReqCount.dat
a=`cat ../simdumps/passengerReqArrival.dat |sort -n | grep '^...$' |wc -l`

    for i in `seq 1 87`;
        do
               	a=`cat ../simdumps/passengerReqArrival.dat |sort -n | grep "^$i...$" |wc -l`
		let j=i+1
		echo $j"000 " $a>> ../data/passengerReqCount.dat
        done  
