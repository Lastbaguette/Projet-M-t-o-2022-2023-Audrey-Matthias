set style data lines

set title "Min-Max on y represented by filledcurve shaded region" 
set xlabel "ID" 

set xtics("07005" 0,"07015" 50,"07020" 100,"07027" 150,"07037" 200,"07072" 250,"07110" 300,"07117" 350,"07130" 400,"07139" 450,"07149" 500,"07168" 550,"07181" 600,"07190" 650,"07207" 700,"07222" 750,"07240" 800,"07255" 850,"07280" 900,"07299" 950,"07314" 1000,"07335" 1050,"07434" 1100,"07460" 1150,"07471" 1200,"07481" 1250,"07510" 1300,"07535" 1350,"07558" 1400,"07577" 1450,"07591" 1500,"07607" 1550,"07621" 1600, "07627" 1650,"07630" 1700,"07643" 1750,"07650" 1800,"07661" 1850,"07690" 1900,"07747" 1950,"07761" 2000,"07790" 2050,"61968" 2100,"61970" 2150,"61972" 2200,"61976" 2250,"61980" 2300,"61996" 2350,"61997" 2400,"61998" 2450,"67005" 2500,"71805" 2550,"78890" 2600,"78894" 2650,"78897" 2700,"78922" 2750,"78925" 2800,"81401" 2850,"81405" 2900,"81408" 2950,"81415" 3000,"89642" 3050)

set ylabel "Temperature (°C)" 
set yrange [ * : * ] noreverse 

set zrange [ * : * ] noreverse

plot 'endsort' using 1:4:3 with filledcurve fc rgb "#80E0A080" title "Shaded region", 'endsort' using 1:2 with lines lw 2 title "Monotonic spline through data"

