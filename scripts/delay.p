reset
  set term postscript eps enhanced color
set output "../plots/Delay.eps"      
	# Gnuplot script file for plotting data in file "Day1.dat"
      # This file is called   plot.p
      set   autoscale                        # scale axes automatically
      unset log                              # remove any log-scaling
      unset label                            # remove any previous labels
      set xtic auto                          # set xtics automatically
      set ytic auto                          # set ytics automatically
      set title "Delay In Servicing Passenger"
      set xlabel "Passenger Request Arrival Time in seconds"
      set ylabel "Delay in seconds"
      #set key 0.01,130
      set label "Delay = Response Time - Max Waiting Time" at 10000,1700
	set label "Number Of Cars = 500" at 10000,1300
	set label "Number Of Passenger Requests = 2000" at 10000,1200
	#set label "MAPE  = 6.9982" at 5,15
	
set arrow from 0.0 to 80000,0 nohead lw 3 lc 1
      
#set yr [10:2500]
set grid
#set style histogram
plot    "../simdumps/servicePerLocation.dat" using 1:6 title 'Delay' with lines lw 1 lc 3 lt 1



set term wxt
