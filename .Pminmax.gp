set style data lines

set title "Min-Max on y represented by pressure shaded region" 
set xlabel "ID" 

set ylabel "Pressure (Pa)" 
set yrange [ * : * ] noreverse 

set zrange [ * : * ] noreverse

plot 'endsort' using 2:5:4 with filledcurve fc rgb "#80E0A080" title "Shaded region", 'endsort' using 2:3 with lines lw 2 title "Average Pressure"
