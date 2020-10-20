#General instructions

set multiplot layout 2,2 rowsfirst						#Enable multi-plotting
set label 1 enhanced font 'Verdana, 6.5' 					#Change size of labels for convenience
set label 2 enhanced font 'Verdana Bold, 5.5'
set label 3 enhanced font 'Verdana Bold, 7'
set xtics enhanced font 'Verdana, 5'
set ytics enhanced font 'Verdana, 5'


iter = 11												#Max row index to use for plotting - used for clarity of the curves

set key autotitle columnhead 							#Use values of alpha present in the first line of each document

set key enhanced font 'Verdana, 5'
set key title "alpha" enhanced font 'Verdana, 5' 		#label name
set key top rmargin

set label 2 'Loop cycle' at graph 0.4, -0.05


#Per-graph instructions


set label 1 'Evolution of a with varying alpha' at graph 0.17, 1.07	
set label 3 'a' at graph -0.15, 0.5							#I had to put custom locations to labels for convenience too
plot for [j=2:iter] "a_val.txt" using 1:j with lines 	#Ignoring 1st because it would display N(N)



set label 1 'Evolution of b with varying alpha' at graph 0.164, 1.07
set label 3 'b' at graph -0.15, 0.5
plot for [j=2:iter] "b_val.txt" using 1:j with lines 



set label 1 'Evolution of c with varying alpha' at graph 0.17, 1.07
set label 3 'c' at graph -0.15, 0.5
plot for [j=2:iter] "c_val.txt" using 1:j with lines 


set label 1 'Evolution of the sum with varying alpha' at graph 0.07, 1.07
set label 3 'Sum' at graph -0.23, 0.5
plot for [j=2:iter] "sum_val.txt" using 1:j with lines 