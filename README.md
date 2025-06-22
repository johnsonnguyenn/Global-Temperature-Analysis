# Global Temperature Analysis Project 

## Summary

This is a comprehensive climate data analysis tool coded in C, which calculates:

- Hottest/coldest months and years
- Yearly and monthly average temperatures
- Land vs. Ocean temperature comparisons
- Temperature uncertainty analysis with error bars

This analysis tool reads and processes historical land and ocean temperature data from **1750 to 2015**, sourced from a CSV file. Results are visualized via **GNUPlot**.

All calculations and graphs are accurate, clear, and statistically supported insights into historical changes in climate and trends, understanding the progression and trend of global warming. 

---

## Requirements

- GCC Compiler ('gcc')
- GNUPlot ('gnuplot')
- Standard C Libraries: `stdio.h`, `stdlib.h`, `string.h`, `ctype.h`, `math.h`, `stdbool.h`

---

## Compilation

To compile the project:

gcc -o climate_analyzer main.c 
