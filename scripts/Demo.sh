#! /bin/bash

cd ../src/
make

#./sim config.cfg

cd ../scripts/

#plot the Number of Passeger Arrived request with time
./passengerReqCount.sh
gnuplot passengerReqCount.p

cd  ../simdumps/

# extract the Revenew Earnings and Losses after the end of simulation
tail -1 carsRevenueLosses.dat | tr "\t" "\n" | sed '1d' | sed '$d'  > 1.txt
tail -1 carsRevenueEarnings.dat | tr "\t" "\n" | sed '1d' | sed '$d' > 2.txt
NumberOfCars=`cat 1.txt | wc -l`
        for i in `seq 1 $NumberOfCars`;
        do
                echo $i >>3.txt
        done
#put earling and loses of all cars in a file for ploting
echo "CarNumber RevenewEarned RevenewLost" >../data/revenue.dat
paste 3.txt 2.txt 1.txt >>../data/revenue.dat
rm 1.txt 2.txt 3.txt			#remove temp. files


#plot car battery power
cd ../scripts/
gnuplot carsBatteryPower.p


