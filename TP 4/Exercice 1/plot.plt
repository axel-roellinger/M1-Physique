set multiplot layout 2,2 rowsfirst

set logscale xy

set key autotitle columnhead
set key top rmargin

iter = 12

set format x "10^{%T}"

set label 1 "Error on F, 1" at graph 0.5, 0.5
plot for [j=2:iter] "errorF1.txt" using 1:j with lines, "errorF1.txt" using 1:13 with lines t "h^2"


set label 1 "Error on F, 3" at graph 0.5, 0.5
plot for [j=2:iter] "errorF3.txt" using 1:j with lines, "errorF3.txt" using 1:13 with lines t "h^4"


set label 1 "Error on G, 1" at graph 0.5, 0.5
plot for [j=2:iter] "errorG1.txt" using 1:j with lines, "errorG1.txt" using 1:13 with lines t "h^2"


set label 1 "Error on G, 3" at graph 0.5, 0.5
plot for [j=2:iter] "errorG3.txt" using 1:j with lines, "errorG3.txt" using 1:13 with lines t "h^4"