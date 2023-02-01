set xdata time
set timefmt "%Y-%m-%d %H:%M:%S"
set xlabel "Date and Time"
set timefmt "%Y-%m-%d %H:%M:%S"
set xdata time
set ylabel "Value"
set key autotitle columnhead
set format x "%Y-%m-%d\n%H:%M:%S"
set xrange [*:*]noextend
set yrange [*:*]noextend

plot "b.txt" using 2:4 ,\
     '' using 1:2 smooth mcspline lw 2   ti	tle "Monotonic spline through data"
   
     
     set title "Line Plot of Data over Time"

set format x "%Y-%m-%d\n%H:%M:%S";
set ylabel "Values";
plot 'endsort' using 1:3 with lines title "Values";
