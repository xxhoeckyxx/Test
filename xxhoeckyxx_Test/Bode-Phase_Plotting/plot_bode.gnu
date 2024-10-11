set terminal pngcairo size 2500,1750
set output 'bode_plot.png'
set grid xtics mxtics 
set mxtics 10 
set logscale x 
set grid ytics mytics 
set mytics 5 
set grid

set multiplot layout 2,1 title 'Bode-Diagramm'

#Magnitude plot
set xlabel 'Frequency (rad/s)'
set xrange [1e-2:1e4]
set ylabel 'Magnitude (dB)'
plot 'magnitude.dat' with lines title 'Magnitude' lt rgb 'blue' lw 3

#Phase plot
set xlabel 'Frequency (rad/s)'
set xrange [1e-2:1e4]
set ylabel 'Phase (degrees)'
plot 'phase.dat' with lines title 'Phase' lt rgb 'green' lw 3
unset multiplot
