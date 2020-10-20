set multiplot layout 2,1 rowsfirst
set label 2 enhanced font "Verdana Bold, 12"

set key top rmargin

set label 1 "Plot of the functions f(x) and g(x)" at graph 0.32, 1.05
set label 2 "x" at graph 1.01, 0

plot "trapeze_1.txt" using 1:2 with lines title "f(x)", "trapeze_1.txt" using 1:3 with lines title "g(x)"

set logscale xy
set format x "10^{%T}"

set label 1 "Error as a function of h (logscale)" at graph 0.29, 1.05 
set label 2 "h" at graph 1.01, 0

plot "errTra.txt" using 1:2 with lines title "error on f(x)", "errTra.txt" using 1:3 with linespoints title "error on g(x)", "errTra.txt" using 1:4 with lines title "h^2"
