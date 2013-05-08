reset
set term postscript eps enhanced color
set output "../plots/passengerArrivalDistribution.eps"      

      set   autoscale                        # scale axes automatically
      unset log                              # remove any log-scaling
      unset label                            # remove any previous labels
      set xtic auto                          # set xtics automatically
      set ytic auto                          # set ytics automatically
      set title "Passenger Requests With Time"
      set xlabel "Simulation Time in Seconds"
      set ylabel "Number of Passenger Requests"
      	#set key 0.01,130
     	# set label "MAPE (Base) = 8.0522048667" at 13,19
	#set label "MAPE  = 6.9982" at 5,15
	
      	#set arrow from 0.0028,250 to 0.003,280D
	#set xr [0:6000]
	#set yr [0:4]
	set grid
#set style histogram
set label "9:00 AM " at 32400,1
set label "12:00 PM " at 43200,1
set label "5:00 PM " at 61200,1
set label "4:00 AM " at 14400,1
set label "10:00 PM " at 79200,1
set label "Total Passenger Requests =2000" at 20,37
plot    "../data/passengerReqCount.dat" using 1:2 title 'Passenger Requests' with linespoints lw 2 lc 1 lt 1
set term wxt
