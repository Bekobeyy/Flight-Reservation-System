#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <vector>

#include "AircraftCompany.h"
#include "Aircraft.h"

using namespace std;

class Aircraft{
	public:
		int vip_seat,business_seat,economy_seat,date_constant,fullness,occupied_seats_number,filled,i; 		// date constant is help to how many aircraft's seats will be fill
		int *occupied_seats;																					// if the date constant near to 0 nearly all seats filled
		Aircraft();																									// if the date constant near to 7 nearly all seats unfilled 
		
		vector<int> all_filled_seats;
		Seat_filler(int seat_num,int seat_constant,int vip,int buss);
		
		print_Seats();
		
		~Aircraft();
		
};

#endif
