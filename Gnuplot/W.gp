set xlabel "Longitude (West-East)";
set ylabel "Latitude (South-North)";
set xrange [-180:180];
set yrange [-90:90];
set xrange [*:*]noextend;
set yrange [*:*]noextend;
plot "b.txt" using 5:4:2:3 with vectors head size 0.05,20 filled lc rgb "red" notitle;
