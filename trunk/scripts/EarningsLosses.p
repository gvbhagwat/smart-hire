reset
  set term postscript eps enhanced color
set output "../plots/EarnngsVsLosses.eps"      

      set   autoscale                        # scale axes automatically
      unset log                              # remove any log-scaling
      unset label                            # remove any previous labels
      #set xtic auto                          # set xtics automatically
      set ytic auto                          # set ytics automatically

      set title "Earnings and Loasses"
      set xlabel "Car Number"
      set ylabel "Revenue in rupees "

## Make the x axis labels easier to read.
#set xtics rotate out
# Select histogram data
set style data histogram
# Give the bars a plain fill pattern, and draw a solid line around them.
set style fill solid border

set style histogram rowstacked
plot for [COL=2:3] '../data/revenue.dat' using COL:xticlabels(1) title columnheader

set term wxt
