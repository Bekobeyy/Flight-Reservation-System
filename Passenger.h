#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <string>
#include <vector>

#include "Ticket.h"

using namespace std;

class Passenger {
public:
    string passengerName, gender, dateOfBirth, emailAddress, telephoneNumber, idNumber;
	int ticket_num;
    Passenger();
    Passenger(string _passengerName, string _gender, string _dateOfBirth, string _emailAddress, string _telephoneNumber, string _idNumber);
    
	Ticket ticket[10];		// I tried to do as a vector but I could not handle with that sorry :( -Ahmet
};

#endif
