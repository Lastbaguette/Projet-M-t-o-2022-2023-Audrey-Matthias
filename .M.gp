set view map;
set dgrid3d 500,500;
set title "Moisture";
set xlabel "Longitude";
set ylabel "Latitude";
set autoscale;
set cbrange[*:*];
set yrange [*:*]noextend;
set xrange [*:*]noextend;

set palette rgb 10,13,33;


splot 'endsort' using 4:3:2 with pm3d title "Moisture (m)";


