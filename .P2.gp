set title "Line Plot of Data over Time";
set xlabel "Date and Time";
set timefmt "%Y-%m-%d";
set xdata time;
set format x "%Y-%m-%d";
set ylabel "Pressure";
set xrange [*:*]noextend;
set yrange [*:*]noextend;
plot 'endsort' using 1:3 with lines title "Pressure by date";
