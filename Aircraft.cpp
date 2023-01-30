#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <bits/stdc++.h>

#include "AircraftCompany.h"
#include "Aircraft.h"



using namespace std;

Aircraft::Aircraft(){
	date_constant=1;		// default
	
}

Aircraft::Seat_filler(int seat_num,int seat_constant,int vip,int buss){
	
	fullness=seat_num/(date_constant+1);										//fullness like a constant for max filled seat
	occupied_seats_number = rand()%fullness+(seat_num/(seat_constant*date_constant));			// choose random number and add some number (for always be a filled seat
	occupied_seats=new int[occupied_seats_number];							//memory alloc
	
	for( i=0 ; i<occupied_seats_number ; ++i){								// randomly choose number for filled seats
		occupied_seats[i] = rand()%seat_num+1+vip+buss;
		for( int x=0; x<i ; x++){
			if(occupied_seats[i]==occupied_seats[x])						// if already filled try again
			i--;
		}
	}
	
	
}

Aircraft::~Aircraft(){/*
	delete[] occupied_seats;
	cout << "deleted";*/
}

Aircraft::print_Seats(){
	
	all_filled_seats.clear();				// clear the vector before write the new data
	
	Seat_filler(vip_seat,4,0,0);			
	
	cout << "\n ****** VIP Seats ******\n ";
	
	for( i=1 ; i<vip_seat+1 ; ++i ){			//prints the seat numbers
		cout << i;
		filled=0;
		for(int x=0 ; x<occupied_seats_number ; x++){		// if the seat filled print *
			if(occupied_seats[x]==i){
			cout << "*";
			filled=1;
			}
		}
		if(filled==0)				// if does not * character after the number, print space // it just for order
			cout<<" ";
		if(i<10)					// for the outputs are regular
			cout<<" ";
		if(i%4==0)					// next seat row
			cout <<"\n ";
		else if(i%2==0)				// to reveal the corridor
			cout << "      ";
		else						// space between seats
			cout<<"  ";
		
	}
	
	for( i=0 ; i<occupied_seats_number ; i++){					// gather all filled seats 
		all_filled_seats.push_back(occupied_seats[i]);
	}
	
	delete[] occupied_seats;				// deleting dynamic memory
	
	Seat_filler(business_seat,3,vip_seat,0);
	
	cout << "\n *** Business Seats ****\n ";
	for( i=1+vip_seat ; i<business_seat+1+vip_seat ; ++i ){		
		cout << i;
		filled=0;
		for(int x=0 ; x<occupied_seats_number ; x++){		
			if(occupied_seats[x]==i){
			cout << "*";
			filled=1;
			}
		}
		if(filled==0)
			cout<<" ";
		if(i<10)
			cout<<" ";
		if(i%4==0)
			cout <<"\n ";
		else if(i%2==0)
			cout << "      ";
		else
			cout<<"  ";
	}
	
	for( i=0 ; i<occupied_seats_number ; i++){			// gather all filled seats 
		all_filled_seats.push_back(occupied_seats[i]);
	}
	
	delete[] occupied_seats;
	
	Seat_filler(economy_seat,2,vip_seat,business_seat);
	
	cout << "\n *** Economy Seats *****\n ";
	
	for( i=1+vip_seat+business_seat ; i<economy_seat+1+vip_seat+business_seat ; ++i ){			
		cout << i;
		filled=0;
		for(int x=0 ; x<occupied_seats_number ; x++){	
			if(occupied_seats[x]==i){
			cout << "*";
			filled=1;
			}
		}
		if(filled==0)
			cout<<" ";
		if(i<10)
			cout<<" ";
		if(i%4==0)
			cout <<"\n ";
		else if(i%2==0)
			cout << "      ";
		else
			cout<<"  ";
	}
	for( i=0 ; i<occupied_seats_number ; i++){				// gather all filled seats 
		all_filled_seats.push_back(occupied_seats[i]);
	}
	
	sort(all_filled_seats.begin(),all_filled_seats.end());		// auto sort fort the vector
	
	
	
	
	delete[] occupied_seats;
	
}







