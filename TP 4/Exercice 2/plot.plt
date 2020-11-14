set multiplot layout 2,1 rowsfirst

set key top rmargin

set yrange[-5:10]
set xrange[0:pi]

set arrow 1 from pi/2,-5 to pi/2,10 nohead

plot "plot.txt" using 1:2 with lines t "f(x)", \
	 "plot.txt" using 1:3 with lines t "g(x)"

#set logscale xy

plot "plot_final.txt" using 1:2 with lines t "df/dx, .1 % precision", \
	 "plot_final.txt" using 1:3 with lines t "dg/dx, .1 % precision"

set arrow 1 from pi/2,-5 to pi/2,10 nohead