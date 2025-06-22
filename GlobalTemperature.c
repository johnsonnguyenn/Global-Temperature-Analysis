#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
//WINTER TERM PROJECT
//ALL COMPUTATIONS IN THIS PROGRAM WILL BE DISPLAYED TO TWO SIGNIFICANT FIGURES

int main (void) {

	//declare and open all files that will be used throughout the project
	FILE *datafile;
	FILE *yearlytempfile;
	FILE *centurytempfile;
	FILE *landtempfile;
	FILE *landbarplotfile;
	FILE *uncertainityfile;
	FILE *oceantempfile;

	datafile = fopen("GlobalTemperatures.csv", "r");
	yearlytempfile = fopen("yearvstemp.txt", "w");
	centurytempfile = fopen("19th&20thcentury.txt", "w");
	landtempfile = fopen("landminmaxavg.txt", "w");
	landbarplotfile = fopen("landminmaxavgbar.txt", "w");
	uncertainityfile = fopen("avguncertainty.txt", "w");
	oceantempfile = fopen("avgoceantemp.txt", "w");
	
	//initialize general variables used for multiple questions
	//remainder of variables will be initialized per respective question
	char data[512];
	char *token;
	int year = 0;
	double temp = 0;
	


	//QUESTION #1: Calculate the yearly averages (1760-2015) through summing the monthly averages for each year
	//			   Display results to user
	
	double yearlyavg = 0;
	int monthcount = 0;
	double totaltempyear = 0;
	double hottestyearavg = -100000;
	double coldestyearavg = 100000;
	//arrays have 100 elements for 100 years
	double temp19cen[100] = {0};
	double temp20cen[100] = {0};
	double oceanyearlyavg = 0;
	double totaltempocean = 0;
	double oceanaverage = 0;
	int hotyear = 0;
	int coldyear = 0;

	printf("QUESTION #1 \n");
	printf("----------- \n");

	//loop through the file's data line by line - used constantly throughout the project
	while (fgets(data, 512, datafile)){ 
		//tokenize to get year and temp (comma since CSV file) , which is a function constantly used in this project
		token = strtok(data, ",");
		year = atoi(token);

		if (year > 1759){
			 token = strtok(NULL, ",");
			 temp = atof(token);
			 //continiously add temp to totaltemp for year varaible, and increment month count
			 totaltempyear += temp;
			 monthcount++; 
		 }
		 
		//once month count reaches 12 months, calculate that years average
		if (monthcount > 11){
			
			yearlyavg = totaltempyear/12;
			
			//QUESTION 7 DATA COLLECTED HERE - Store yearly average for 19th and 20th century
			//mod division for arrays to keep same x axis (00, 01, 02..)
			if (year > 1799 && year < 1900) {
				temp19cen[year % 100] = yearlyavg; 
			} else if (year >= 1900 && year < 2000) {
				temp20cen[year % 100] = yearlyavg;
			}
			
			//QUESTION 5 DATA COLLECTED HERE - Find hottest and coldest year 
			//keep setting a new low/high temp until lowest/highest are found
			if (yearlyavg > hottestyearavg){
				hottestyearavg = yearlyavg;
				hotyear = year;
			}
				
			if (yearlyavg < coldestyearavg){
				coldestyearavg = yearlyavg;
				coldyear = year;
			}
			
			//display to user average temperature, and reset variables to keep calculations accurate
			printf("The average temperature for year %d is: %.2lf degrees celsuis \n", year, yearlyavg);
			totaltempyear = 0;
			monthcount = 0;
			//QUESTION 6 DATA COLLECTED HERE - write year | average to file to later plot
			fprintf(yearlytempfile, "%d %.2lf \n", year, yearlyavg);
		}
	}

	//constantly close data file after each question to prepare for the following set of code
	fclose(datafile);
	
	//QUESTION 7: write to file year (in format of 00, 01, 02 | temp for 19th century at that position | temp for 20th century at that position)
	for (int i = 0; i <100; i++){
		if (temp19cen[i] != 0 && temp20cen[i] != 0){
			fprintf(centurytempfile, "%02d %.2lf %.2lf \n", i, temp19cen[i], temp20cen[i]);
		}
	}


	//QUESTION #2: Calculate the century average through adding up that century's yearly averages
	//			   Display to user - 4 centures therefore 4 results
	
	
	//arrays have 4 elements for 4 centures
	double centuryavg = 0;
	double totaltempcentury[4] = {0};
	int yearsincentury[4] = {0};
	int currentcentury = 0;

	printf("\n");
	printf("QUESTION #2 \n");
	printf("----------- \n");

	//after closing the file in previous question, reopen to analyze
	datafile = fopen("GlobalTemperatures.csv", "r");

	while (fgets(data, 512, datafile)){
		token = strtok(data, ",");
		year = atoi(token);

		//only from years 1760-2015
		if (year > 1759 && year <= 2015){
			token = strtok(NULL, ",");
			temp = atof(token);	 
			//use integer division - storing 18th cen as index 0, 19th cen as 1, and so on and so forth
			currentcentury = (year - 1700)/100;
			//store totaltemp for century in array (0-3)
			totaltempcentury[currentcentury] += temp;
			yearsincentury[currentcentury]++;
		 }
	}
	fclose(datafile);

	//finally, calculate the total average and display to user
	for (int i=0; i < 4; i++){
		centuryavg = totaltempcentury[i]/(double)yearsincentury[i];
		//(i+17) as our indexes are positions 0-3
		printf("The total average temperature for the %dth century is %.2lf degrees celsuis \n", (i+17), centuryavg);
	}


	//QUESTION #3: Calculate the MONTHLY average for each month for the data taken from 1900-2015
	//			   Display to user 12 results, one for each month

	
	//arrays have 12 elements for 12 months
	double totalpermonth[12] = {0};
	int totalcountmonth[12] = {0};
	int currentmonth = 0;
	double monthlyavg = 0;

	printf("\n");
	printf("QUESTION #3 \n");
	printf("----------- \n");

	datafile = fopen("GlobalTemperatures.csv", "r");

	while (fgets(data, 512, datafile)){
		token = strtok(data, ",");
		year = atoi(token);

		if (year >= 1900 && year <= 2015){
			//find only years from 1900-2015, then store the data for that respective month in an array
			token = strtok(NULL, ",");
			temp = atof(token);
			//similarly to previous questions, add temperature total 
			totalpermonth[currentmonth] += temp;
			totalcountmonth[currentmonth]++;
			currentmonth++;
			//reset current month so it doesnt exceed 12 months 
			
			if (currentmonth > 11){
				currentmonth = 0;
			}
		}
	}
	
	fclose(datafile);

	//loop from 1-12 and display monthly averages
	for (int i =1; i <= 12; i++){
		monthlyavg = (double)totalpermonth[i-1]/(double)totalcountmonth[i-1];
		printf("The total average temperature for month %d for years 1900-2015 is: %.2lf degrees celsuis \n", i, monthlyavg);
	}

	//QUESTION #4: Find hottest and coldest month temperature recorded from ALL DATA
	//			   Display to user the month and in which year it occured, as well as the temperature

	printf(" \n");
	printf("QUESTION #4 \n");
	printf("----------- \n");

	datafile = fopen("GlobalTemperatures.csv", "r");
	char hottestmonthname[20];
	char coldestmonthname[20];
	int month = 0;
	double hottesttemp = -100000;
	int hottestmonth = 0;
	int hottestyear = 0;
	double coldesttemp = 100000;
	int coldestmonth = 0;
	int coldestyear = 0;

	while (fgets(data, 512, datafile)){
		token = strtok(data, ",");
		year = atoi(token);
		token = strtok(NULL, ",");
		temp = atof(token);
		 
		 //cycle through all data, finding lowest/highest temps and their respective months and years
		if (temp < coldesttemp) {
			 coldesttemp = temp;
			 coldestmonth = month;
			 coldestyear = year;
		}
		if (temp > hottesttemp) {
			 hottesttemp = temp;
			 hottestmonth = month;
			 hottestyear = year;
		}
			 month++;
			 //reset month back to 0 after 12 has been reached
		if (month > 11){
			month = 0;	 
		}

	}
	fclose(datafile);


	//the next few lines simply convert hottest/coldest months to the actual month names (strings) to display
	if (hottestmonth == 1){
		  strncpy (hottestmonthname, "January", 19);
		  hottestmonthname[19] = '\0';
	 } else  if (hottestmonth == 2){
		  strncpy (hottestmonthname, "February", 19);
		  hottestmonthname[19] = '\0';
	 } else  if (hottestmonth == 3){
		  strncpy (hottestmonthname, "March", 19);
		  hottestmonthname[19] = '\0';
	 } else  if (hottestmonth == 4){
		  strncpy (hottestmonthname, "April", 19);
		  hottestmonthname[19] = '\0';
	 } else  if (hottestmonth == 5){
		  strncpy (hottestmonthname, "May", 19);
		  hottestmonthname[19] = '\0';
	 } else  if (hottestmonth == 6){
		  strncpy (hottestmonthname, "June", 19);
		  hottestmonthname[19] = '\0';
	 } else  if (hottestmonth == 7){
		  strncpy (hottestmonthname, "July", 19);
		  hottestmonthname[19] = '\0';
	 } else  if (hottestmonth == 8){
		  strncpy (hottestmonthname, "August", 19);
		  hottestmonthname[19] = '\0';
	 } else  if (hottestmonth == 9){
		  strncpy (hottestmonthname, "September", 19);
		  hottestmonthname[19] = '\0';
	 } else  if (hottestmonth == 10){
		  strncpy (hottestmonthname, "October", 19);
		  hottestmonthname[19] = '\0';
	 } else  if (hottestmonth == 11){
		  strncpy (hottestmonthname, "November", 19);
		  hottestmonthname[19] = '\0';
	 } else  if (hottestmonth == 12){
		  strncpy (hottestmonthname, "December", 19);
		  hottestmonthname[19] = '\0';
	 }
	 
	if (coldestmonth == 1){
		 strncpy (coldestmonthname, "January", 19);
		 coldestmonthname[19] = '\0';
	 } else  if (coldestmonth == 2){
		 strncpy (coldestmonthname, "February", 19);
		 coldestmonthname[19] = '\0';
	 } else  if (coldestmonth == 3){
		 strncpy (coldestmonthname, "March", 19);
		 coldestmonthname[19] = '\0';
	 } else  if (coldestmonth == 4){
		 strncpy (coldestmonthname, "April", 19);
		 coldestmonthname[19] = '\0';
	 } else  if (coldestmonth == 5){
		 strncpy (coldestmonthname, "May", 19);
		 coldestmonthname[19] = '\0';
	 } else  if (coldestmonth == 6){
		 strncpy (coldestmonthname, "June", 19);
		 coldestmonthname[19] = '\0';
	 } else  if (coldestmonth == 7){
		 strncpy (coldestmonthname, "July", 19);
		 coldestmonthname[19] = '\0';
	 } else  if (coldestmonth == 8){
		 strncpy (coldestmonthname, "August", 19);
		 coldestmonthname[19] = '\0';
	 } else  if (coldestmonth == 9){
		 strncpy (coldestmonthname, "September", 19);
		 coldestmonthname[19] = '\0';
	 } else  if (coldestmonth == 10){
		 strncpy (coldestmonthname, "October", 19);
		 coldestmonthname[19] = '\0';
	 } else  if (coldestmonth == 11){
		 strncpy (coldestmonthname, "November", 19);
		 coldestmonthname[19] = '\0';
	 } else  if (coldestmonth == 12){
		 strncpy (coldestmonthname, "December", 19);
		 coldestmonthname[19] = '\0';
	 }

	//display to user hottest/coldest months with temperatures
	printf("The hottest temperature ever recorded was on %s %d at: %.2lf degrees celsuis \n", hottestmonthname, hottestyear, hottesttemp);
	printf("The coldest temperature ever recorded was on %s %d at: %.2lf degrees celsuis \n", coldestmonthname, coldestyear, coldesttemp);


	//QUESTION #5: Calculate hottest and coldest year based on data collected from Q1
	//			   Display to user

	printf(" \n");
	printf("QUESTION #5 \n");
	printf("----------- \n");

	//since data was already collected and stored in varaibles, simply display
	printf("The hottest year based off the average temperature per year was: %d (at %.2lf degrees celsuis) \n", hotyear, hottestyearavg);
	printf("The coldest year based off the average temperature per year was: %d (at %.2lf degrees celsuis) \n", coldyear, coldestyearavg);

	//QUESTION #6: Write to a file and graph year vs temp already collected in Q1's code
	
	//QUESTION #7: Write to a file and graph 19th vs 20th century on same figure already collected in Q1's code

	//QUESTION #8: Write to a file the data of min/avg/max land temeratures (1850-2015) and graph the 3 lines on the same plot

	double totaltempyearaverage = 0;
	double totaltempyearmin = 0;
	double totaltempyearmax = 0;
	double tempaverage = 0;
	double tempmin = 0;
	double tempmax = 0;
	double yearavg = 0;
	double yearmin = 0;
	double yearmax = 0;
	//51 for 19th century as 51 years, remaining centuries have 100 each
	double temp19cenlow[51] = {0};
	double temp19cenavg[51] = {0};
	double temp19cenhigh[51] = {0};
	double temp20cenlow[100] = {0};
	double temp20cenavg[100] = {0};
	double temp20cenhigh[100] = {0};
	double temp21cenlow[100] = {0};
	double temp21cenavg[100] = {0};
	double temp21cenhigh[100] = {0};
	double total19cenlow = 0;
	double total20cenlow = 0;
	double total21cenlow = 0;
	double totall9cenavg = 0;
	double total20cenavg = 0;
	double total21cenavg = 0;
	double totall9cenhigh = 0;
	double total20cenhigh = 0;
	double total21cenhigh = 0;
	double tempaverageuncertainity = 0;	
	datafile = fopen("GlobalTemperatures.csv", "r");

	while (fgets(data, 512, datafile)){
		token = strtok(data, ",");
		year = atoi(token);



		//collect data only from 1850 and beyond
		if (year > 1849){
			//continiously tokenize to get min,max, and average temps
			 token = strtok(NULL, ",");
			 tempaverage = atof(token);
			 totaltempyearaverage += tempaverage;
			 token = strtok(NULL, ",");
			 token = strtok(NULL, ",");
			 tempmax = atof(token);
			 totaltempyearmax += tempmax;
			 token = strtok(NULL, ",");
			 token = strtok(NULL, ",");
			 tempmin = atof(token);
			 totaltempyearmin += tempmin;
			 monthcount++;
		 }
		 
		 //similarly to previous questions, divide by 12 when end of yearis reached
		if (monthcount > 11){
			
			yearavg = totaltempyearaverage/12;
			yearmax = totaltempyearmax/12;
			yearmin = totaltempyearmin/12;

			//store each temperature in its respective array based off century condition
			if (year > 1849 && year < 1900){
				int index = year - 1850;
				temp19cenlow[index] += yearmin;
				temp19cenavg[index] += yearavg;
				temp19cenhigh[index] += yearmax;
			} else if (year >= 1900 && year < 2000){
				int index = year - 1900;
				temp20cenlow[index] += yearmin;
				temp20cenavg[index] += yearavg;
				temp20cenhigh[index] += yearmax;
			} else if (year >= 2000 && year <= 2015){
				int index = year - 2000;
				temp21cenlow[index] += yearmin;
				temp21cenavg[index] += yearavg;
				temp21cenhigh[index] += yearmax;
			}
			//finally, write to the file the year's temperatures and reset variables
			fprintf(landtempfile, "%d %.2lf %.2lf %.2lf \n", year, yearavg, yearmax, yearmin);
			totaltempyearaverage = 0;
			totaltempyearmax = 0;
			totaltempyearmin = 0;
			monthcount = 0;
			}
		
	}
	fclose(datafile);
	
	//QUESTION 9: Write to a file that will then create 3 bar plots, one for min, avg and max temps
	//			  Use data for 19th, 20th and 21st century to have 3 bars within each of those subplots
	
	//calculate the averages:
	//50 years for 19th century
	//100 years for 20th century
	//16 years for 21st century
	
	
	for (int i = 0; i < 50; i++) {
		total19cenlow += temp19cenlow[i];
		totall9cenavg += temp19cenavg[i];
		totall9cenhigh += temp19cenhigh[i];
	}

	for (int i = 0; i < 100; i++) {
		total20cenlow += temp20cenlow[i];
		total20cenavg += temp20cenavg[i];
		total20cenhigh += temp20cenhigh[i];
	}

	for (int i = 0; i < 16; i++) {
		total21cenlow += temp21cenlow[i];
		total21cenavg += temp21cenavg[i];
		total21cenhigh += temp21cenhigh[i];
	}
	
	//divide to get the average

	total19cenlow /= 50;
	totall9cenavg /= 50;
	totall9cenhigh /= 50;

	total20cenlow /= 100;
	total20cenavg /= 100;
	total20cenhigh /= 100;

	total21cenlow /= 16;
	total21cenavg /= 16;
	total21cenhigh /= 16;

	//print to file to later graph
	fprintf(landbarplotfile, "%.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf", total19cenlow, total20cenlow, total21cenlow, totall9cenavg, total20cenavg, total21cenavg, totall9cenhigh, total20cenhigh, total21cenhigh);

	//QUESTION 10: Write to a file the average monthly temperature from years 2000-2015 as well as the uncertainities assossiated with said months
	//			   The uncertainty values will be treated as error bar values when plotting
	
	
	datafile = fopen("GlobalTemperatures.csv", "r");
	monthcount = 1;
	 
	 while (fgets(data, 512, datafile)){
		token = strtok(data, ",");
		year = atoi(token);

		//considering years after 1999
		if (year >= 2000){
			 token = strtok(NULL, ",");
			 tempaverage = atof(token);
			 //tokenize for uncertainity as well
			 token = strtok(NULL, ",");
			 tempaverageuncertainity = atof(token);
			 //print to file
			 fprintf(uncertainityfile, "%d-%02d %.2lf %.2lf \n", year, monthcount, tempaverage, tempaverageuncertainity);
			 monthcount++;
			 if (monthcount > 12){
				 monthcount = 1; 
			}
		 }
	}
	fclose(datafile);

	//QUESTION 11: Write to a file which will then create both the yearly average temperatures in a plot, as well as the land and ocean temperatures
	//			   Both lines are to be displayed on the same plot
	
	datafile = fopen("GlobalTemperatures.csv", "r");
	monthcount = 0;
	totaltempyear = 0;
	totaltempocean = 0;
	
	while (fgets(data, 512, datafile)){
		token = strtok(data, ",");
		year = atoi(token);

		if (year >= 1850 && year < 2016){
			token = strtok(NULL, ",");
			tempaverage = atof(token);
			totaltempyear += tempaverage;
			//tokenize until oceanaverage is reached
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			token = strtok(NULL, ",");
			oceanaverage = atof(token);
			totaltempocean += oceanaverage;
			monthcount++;		
		}
		
		if (monthcount > 11){	
			//calculate the land&ocean average the same way as the yearly average
			yearlyavg = totaltempyear/12;
			oceanyearlyavg = totaltempocean/12;
			fprintf(oceantempfile, "%d %.2lf %.2lf \n", year, yearlyavg, oceanyearlyavg);
			//reset all variables
			totaltempyear = 0;
			totaltempocean = 0;
			monthcount = 0;
		}
	}

return (0);

}
