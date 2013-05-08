reset
set term postscript eps enhanced color
set output "../plots/carsBatteryPower.eps"      

      set   autoscale                        # scale axes automatically
      unset log                              # remove any log-scaling
      unset label                            # remove any previous labels
      set xtic auto                          # set xtics automatically
      set ytic auto                          # set ytics automatically
      set title "Car Battery Behaviour"
      set xlabel "Simulation Time in Seconds"
      set ylabel "% Charge in Battery"
      	#set key 0.01,130
     	# set label "MAPE (Base) = 8.0522048667" at 13,19
	#set label "MAPE  = 6.9982" at 5,15
	
      	#set arrow from 0.0028,250 to 0.003,280D
	#set xr [0:6000]
	#set xr [0:110]
	set grid
#set style histogram

plot    "../simdumps/carsBatteryPower.dat" using 1:2 title 'CAR 1' with lines lw 2 lc 1 lt 1\
, "../simdumps/carsBatteryPower.dat" using 1:3 title 'CAR 2' with lines lw 2 lc 2 lt 1\
, "../simdumps/carsBatteryPower.dat" using 1:4 title 'CAR 3' with lines lw 2 lc 3 lt 1\
, "../simdumps/carsBatteryPower.dat" using 1:5 title 'CAR 4' with lines lw 2 lc 4 lt 1\
, "../simdumps/carsBatteryPower.dat" using 1:6 title 'CAR 5' with lines lw 2 lc 5 lt 1\
, "../simdumps/carsBatteryPower.dat" using 1:21 title 'CAR 20' with lines lw 2 lc 6 lt 1\
, "../simdumps/carsBatteryPower.dat" using 1:31 title 'CAR 30' with lines lw 2 lc 7 lt 1

set term wxt
