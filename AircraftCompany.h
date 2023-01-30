#ifndef AIRCRAFTCOMPANY_H
#define AIRCRAFTCOMPANY_H
#include "AircraftCompany.h"
#include "Aircraft.h"
#include <iostream>

using namespace std;


class AircraftCompany{
	public:
		std::string company_name;
		float multiplier;
		Aircraft aircraft[2];
		
		AircraftCompany();

};

#endif
