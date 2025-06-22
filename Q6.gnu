#label title, x and y axis
set title 'Q6: Yearly Average Temperatures (1760-2015) '
set xlabel 'Year'
set ylabel 'Average Temperature (°C)'
set grid


#plot year | temp and label legend as temperature
plot 'yearvstemp.txt' using 1:2 \
title "Temperature" with l, \
