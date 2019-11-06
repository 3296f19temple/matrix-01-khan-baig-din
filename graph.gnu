set terminal png size 800,600 
set output 'out.png'

set xlabel 'Matrix Size'
set ylabel 'Time (Seconds)'
set title 'Matrix multiplication speed on Wolfgang Cluster'
plot "data.txt" using 1:2 title 'MPI' with linespoints
