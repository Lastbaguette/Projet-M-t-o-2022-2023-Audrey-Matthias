set view map
set dgrid3d 500,500
set title "Height"
set xlabel "Longitude"
set ylabel "Latitude"
set autoscale
set cbrange[*:*]
set xrange [*:*]noextend
set yrange [*:*]noextend
set palette rgb 10,13,33


splot 'endsort' using 4:3:2 with pm3d title "Height (m)"
