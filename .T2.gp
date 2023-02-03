set title "Line Plot of Data over Time";
set xlabel "Date and Time";
set timefmt "%Y-%m-%d %H:%M:%S";
set xdata time;
set format x "%Y-%m-%d\n%H:%M:%S";
set ylabel "Temperature";
set xrange [*:*]noextend;
set yrange [*:*]noextend;
plot 'endsort' using 1:3 with lines title "temperature by date";
