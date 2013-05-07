reset
  set term postscript eps enhanced color
set output "../plots/nCarVariation.eps"      
	# Gnuplot script file for plotting data in file "Day1.dat"
      # This file is called   plot.p
      set   autoscale                        # scale axes automatically
      unset log                              # remove any log-scaling
      unset label                            # remove any previous labels
      set xtic auto                          # set xtics automatically
      set ytic auto                          # set ytics automatically
      set title "Service With Varying Battery Discharge Rates(% per meter)"
      set xlabel "Number Of cars"
      set ylabel "Number Of passenger requests satisfied out of 2000"
      #set key 0.01,130
     # set label "MAPE (Base) = 8.0522048667" at 13,19
	#set label "MAPE  = 6.9982" at 5,15
	
      #set arrow from 0.0028,250 to 0.003,280D
set yr [10:2500]
set grid
#	set style histogram
plot    "../data/nCarVariation.dat" using 1:2 title 'Total Passenger Request' with lines lw 1 lc 5 lt 1\
, "../data/nCarVariation.dat" using 1:3 title 'Satisfied(0.001%)' with lines lw 3 lc 1 lt 1\
, "../data/nCarVariation.dat" using 1:4 title 'Unsatisfied' with lines lw 2 lc 1 lt 4\
, "../data/nCarVariation.dat" using 1:7 title 'Satisfied(0.00125%)' with lines lw 3 lc 2 lt 1\
, "../data/nCarVariation.dat" using 1:8 title 'Unsatisfied' with lines lw 2 lc 2 lt 4\
, "../data/nCarVariation.dat" using 1:11 title 'Satisfied(0.0015%)' with lines lw 3 lc 3 lt 1\
, "../data/nCarVariation.dat" using 1:12 title 'Unsatisfied' with lines lw 2 lc 3 lt 4\
, "../data/nCarVariation.dat" using 1:15 title 'Satisfied(0.00175%)' with lines lw 3 lc 4 lt 1\
, "../data/nCarVariation.dat" using 1:16 title 'Unsatisfied' with lines lw 2 lc 4 lt 4
set term wxt
