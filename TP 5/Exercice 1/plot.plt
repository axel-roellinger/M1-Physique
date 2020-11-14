set multiplot layout 3,1 rowsfirst

set key top rmargin

plot "graph.txt" using 1:2 with lines t "Euler 1", "graph.txt" using 1:3 with lines t "Euler 2", "graph.txt" using 1:4 with lines t "Analytical solution"

set logscale xy
set format x "10^{%T}"
set format y "10^{%T}"
plot "error_graph.txt" using 1:2 with lines t "Error advanced", "error_graph.txt" using 1:3 with lines t "Error delayed", "error_graph.txt" using 1:4 with lines t "h slope"

unset logscale xy
unset format x
unset format y
plot "stable_graph.txt" using 1:2 with lines t "K for advanced method", "stable_graph.txt" using 1:3 with lines t "K for delayed method"
