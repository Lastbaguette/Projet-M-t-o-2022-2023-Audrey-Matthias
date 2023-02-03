set style data lines

set title "Min-Max on y represented by pressure shaded region" 
set xlabel "ID" 
set xtics font ".2"
set term qt size 1900,700
set ylabel "Pressure (Pa)" 
set yrange [ * : * ] noreverse 
set ytics font "1"


plot 'endsort' using 1:5:4:xtic(2) with filledcurve fc rgb "#80E0A080" title "Shaded region", 'endsort' using 1:3:xtic(2) with lines lw 2 title "Average Pressure"
