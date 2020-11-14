set multiplot layout 2,2 rowsfirst

set key top rmargin

plot "second_scheme.txt" using 1:2 with lines t "Second scheme", "second_scheme.txt" using 1:3 with lines t "Analytical curve"

plot "ABM_scheme.txt" using 1:2 with lines t "ABM scheme", "second_scheme.txt" using 1:3 with lines t "Analytical curve"

set logscale xy

plot "error_second_scheme.txt" using 1:2 with lines t "Error", "error_second_scheme.txt" using 1:3 with lines t "h^4"

plot "error_ABM.txt" using 1:2 with lines t "Error", "error_ABM.txt" using 1:3 with lines t "h^4"