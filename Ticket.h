#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include <vector>

class Ticket
{
	public:
	std::string where_from,where_from_airport,to_where,to_where_airport;
	float ticket_price;
	int vip_ticket,bus_ticket,eco_ticket,vip_child,bus_child,eco_child,hour,minute,day,month,year;
	std::vector<int> purchased_seat_num;
	Ticket();
};

#endif
