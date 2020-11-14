set key top rmargin
set xtics
set ytics

set arrow 1 from 0,0 to 1,0 nohead dashtype 2 linecolor rgb "black"

plot "plot.txt" using 1:2 with lines linecolor rgb 'blue' t "f(x)",\
	 "plot.txt" using 1:3 with lines linecolor rgb 'red' t "g(x)",\
	 "extremaF.txt" using 1:(-1) with impulses dashtype 2 linecolor rgb 'blue' t "",\
	 "extremaG.txt" using 1:(-1) with impulses dashtype 2 linecolor rgb 'red' t "",\
	 "extremaF.txt" using 1:(1) with impulses dashtype 2 linecolor rgb 'blue' t "",\
	 "extremaG.txt" using 1:(1) with impulses dashtype 2 linecolor rgb 'red' t ""