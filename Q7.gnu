#label title, x and y axis
set title 'Q7: 19th vs 20th Century Temperatures'
set xlabel 'Year'
set ylabel 'Average Temperature (°C)'
set grid

#DATA STORED IN FILE AS FOLLOWS - (last two digits of year | 19thcen temp | 20thcen temp)
#plot with 1:2 for 19th century and label legend
#plot w 1:3 for 20th century and label legend

plot '19th&20thcentury.txt' using 1:2 \
title "19th Century" with l, \
'19th&20thcentury.txt' using 1:3 \
title "20th Century" with l
