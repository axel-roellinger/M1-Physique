set logscale xy

set key top rmargin

set title "Residual error as a function of h"
set xlabel "h"
set ylabel "Residual error"
plot "errRiemann.txt" using 1:2 with lines title "Residual error", "errRiemann.txt" using 1:3 with lines title "y = h"