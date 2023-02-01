set style data lines;

set title "Min-Max on y represented by filledcurve shaded region"; 
set xlabel "ID" ;
set xrange [ * : * ] noreverse ;

set ylabel "temperature (°C)" ;
set yrange [ -50 : 100 ] noreverse;

set zrange [ * : * ] noreverse; 


Shadecolor = "#80E0A080";
plot 'endsort' using 1:($4):($3)       with filledcurve fc rgb Shadecolor title "Shaded region", \;
     '' using 1:2 smooth mcspline lw 2   ti	tle "Monotonic spline through data";

