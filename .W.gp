set xlabel "Longitude (West-East)";
set ylabel "Latitude (South-North)";
set xrange [-180:180];
set yrange [-90:90];
set yrange [*:*]noextend;
set xrange [*:*]noextend;

plot "endsort" using 5:4:2:3 with vectors lc rgb "red" notitle;
