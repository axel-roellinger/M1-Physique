set multiplot layout 2,1 rowsfirst
set key top rmargin
set xtics
set ytics

set arrow 1 from 0,0 to 1,0 nohead dashtype 2 linecolor rgb "black"

plot "plotF.txt" using 1:2 with lines linecolor rgb 'blue' t "f(x)",\
	 "plotG.txt" using 1:2 with lines linecolor rgb 'red' t "g(x)",\
	 "zerosF.txt" using 1:(-1) with impulses dashtype 2 linecolor rgb 'blue' t "",\
	 "zerosG.txt" using 1:(-1) with impulses dashtype 2 linecolor rgb 'red' t "",\
	 "zerosF.txt" using 1:(1) with impulses dashtype 2 linecolor rgb 'blue' t "",\
	 "zerosG.txt" using 1:(1) with impulses dashtype 2 linecolor rgb 'red' t ""