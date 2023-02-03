set style data lines

set title "Min-Max on y represented by temp shaded region" 
set xlabel "ID" 

set ylabel "Temperature (°C)" 
set yrange [ * : * ] noreverse 

set zrange [ * : * ] noreverse

plot 'endsort' using 2:5:4 with filledcurve fc rgb "#80E0A080" title "Shaded region", 'endsort' using 2:3 with lines lw 2 title "Average temp"

