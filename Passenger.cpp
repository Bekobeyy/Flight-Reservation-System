#include "Passenger.h"
#include <iostream>
#include "Ticket.h"


Passenger::Passenger() {
    //Default constructor
	ticket_num=0;
}

Passenger::Passenger(string _passengerName, string _gender, string _dateOfBirth, string _emailAddress, string _telephoneNumber, string _idNumber) {
    passengerName = _passengerName;
    gender = _gender;
    dateOfBirth = _dateOfBirth;
    emailAddress = _emailAddress;
    telephoneNumber = _telephoneNumber;
    idNumber = _idNumber;
}

