#include "HourAndMinute.h"

HourAndMinute::HourAndMinute(){
	
	srand(time(NULL));
	
	for( i=0 ; i<3 ; ++i ){
		
		if(i==0){
			hour[i]= rand()%3+3;
			minute[i]=rand()%60;
		}
		else if(i==1){
			hour[i]= rand()%3+12;
			minute[i]=rand()%60;
		}
		else if(i==2){
			hour[i]= rand()%3+16;
			minute[i]=rand()%60;
		}
	}
	
	
	
}
