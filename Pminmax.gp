set style data lines

set title "Min-Max on y represented by filledcurve shaded region" 
set xlabel "ID" 
set xrange [ * : * ] noreverse 

set ylabel "Pressure (Pa)" 
set yrange [ * : * ] noreverse 

set zrange [ * : * ] noreverse

plot 'endsort' using 1:4:3 with filledcurve fc rgb "#80E0A080" title "Shaded region", 'endsort' using 1:2 with lines lw 2 title "Monotonic spline through data"

