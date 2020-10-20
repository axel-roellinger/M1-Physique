set key top rmargin

set xlabel "E"
set ylabel "D_{E}(E)"
set title "Plot of the function D_{E}(E)"
plot "fx.txt" with lines lw 2  t "D_{E}(E)", "ptsGood.txt" t "Good points" pt 7 ps 1 lt rgb "green", "ptsBad.txt" t "Bad points" pt 7 ps 1 lt rgb "red"  
