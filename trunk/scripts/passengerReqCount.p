reset
set term postscript eps enhanced color
set output "../plots/passengerArrivalDistribution.eps"      

      set   autoscale                        # scale axes automatically
      unset log                              # remove any log-scaling
      unset label                            # remove any previous labels
      set xtic auto                          # set xtics automatically
      set ytic auto                          # set ytics automatically
      set title "Passenger Requests With Time using Random Function"
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
set label "2:30 AM " at 6,0.6
set label "7:30 AM " at 26,0.6
set label "13:30 PM " at 46,0.6
set label "5:30 PM " at 66,0.6
set label "13:30 PM " at 86,0.6

plot    "../data/passengerReqCount.dat" using 1:2 title 'Number Of Requests' with linespoints lw 2 lc 1 lt 1
set term wxt