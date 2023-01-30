#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <bits/stdc++.h>

#include "AircraftCompany.h"
#include "Aircraft.h"
#include "City.h"
#include "Passenger.h"
#include "HourAndMinute.h"
#include "Ticket.h"
#include "Payment.h"


// we assumed that fligth ticket base is Ankara and date is 01.01.2022


int main(){
	
	ifstream cities_file("cities.txt");
	
	if( !cities_file.is_open()){									// if the file does not read
		cerr << "\n ! ! ! txt file does not read ! ! !";
		system("PAUSE");
		return 1;														// exit from program
	}
	
	int i,distance,passenger_num=-1;
	int day,month,time,date_constant,return_day,return_month;
	int seat_num_in_vip=0,seat_num_in_bus=0,seat_num_in_eco=0,child_in_vip=0,child_in_bus=0,child_in_eco=0;
	int x=-999,go_city,y,selection,buy_seats,company,choosable_seat_num,a,b,collision,return_ticket=0;
	
	float ticket_discount,price;
	
	string city_name,airport_name;
	string passenger_name, gender, date_of_birth, email_address, telephone_number, id_number,passenger_id;
    string credit_card_number, credit_card_CVC, credit_card_date, credit_card_name;
    
    vector <int> chosen_seats;
	
	
	HourAndMinute *hour_and_minute;	

	AircraftCompany aircraft_company[2];
	
	aircraft_company[0].multiplier=0.7;aircraft_company[0].company_name="Turk Haya Yollari";
	aircraft_company[1].multiplier=0.65;aircraft_company[1].company_name="Pegasus";
									
	Passenger passenger[10];
	Payment payment[10];
	
	City city[11];
	
	for( i=0 ; cities_file>>city_name>>airport_name>>distance ; i++){									//read from file for city info
			city[i].city=city_name;city[i].airport=airport_name;city[i].distance=distance;			
	}						
																			
    

	
	//************************************************************************************************************************************************
	
	cout << " Welcome To The Fligth Reservation System \n------------------------------------------";
	
	
	do{
		switch(x){
			case 1:
				
				price = 0;					// every run starts 0
				return_ticket=0;
											city_selection:;
						
				system("CLS");						// clean the console
				
				cout << "\n International flights are transferred from Istanbul.\n";
				for( i=0 ; i<11 ; i++ ){																// print cities
					cout << setw(3) << right << setfill(' ') << i+1 << " - " << setw(18) << left << setfill(' ') << city[i].city << "  " << city[i].airport << endl;
				}
					
				cout << "\n Where do you want to go ?\n -> ";
				
				do{
					cin >> go_city;
					
					if(go_city<1 || 11<go_city)
						cerr << "\n ! You entered out of range. Try again -> ";
					
				}while(go_city<1 || 11<go_city);
	
	
				cout << "\n\n You will go from Ankara (ESB) to " << city[go_city-1].city << ' '<<'(' << city[go_city-1].airport <<")\n\n" ;
				
											RETURN_TICKET:;
				
											date_selection:;
																						
				
				
				if(return_ticket==1){																	// return ticket
					cout << "\n Enter DAY & MONTH ("<<day+1<<'.'<<month<<'.'<<"2022-30.06.2022) ->";
					cin >> return_day >> return_month;
					
					while( (return_day<1 || 30<return_day) && (return_month<1 || 6<return_month)){
						
						if(return_day<1 || 30<return_day){
							cerr << "\n ! Day is out of range. Try again -> ";
							cin >> return_day;
						}
						
						if(return_month<1 || 6<return_month){
							cerr << "\n ! Month is out of range. Try again -> ";
							cin >> return_month;
						}
						
					}
					
					if(return_month<month){
						do{
							cerr << "\n ! Return-ticket month cannot be lower than going ticket. Try again -> ";
							cin >> return_month;
						}while(return_month<month);
					}
					if(month==return_month){
						if(return_day<=day){
							do{
								cerr << "\n ! Return-ticket day cannot be lower than or equal to going ticket. Try again -> ";
								cin >> return_day;
								
							}while(return_day<=day);
						}
					
					}
					
					day=return_day;
					month=return_month;
					
				}
						
				else{																	// going ticket
					
					cout << " Enter DAY & MONTH (01.01.2022-30.06.2022) -> ";
					cin >> day >> month;
					
					while( (day<1 || 30<day) && (month<1 || 6<month)){
						
						if(day<1 || 30<day){
							cerr << "\n ! Day is out of range. Try again -> ";
							cin >> day;
						}
						
						if(month<1 || 6<month){
							cerr << "\n ! Month is out of range. Try again -> ";
							cin >> month;
						}
						
					}
				}
				
				
				
				
				cout << "\n Pick a time :\n";
												
				hour_and_minute = new HourAndMinute();					// changes the time on each ticket purchase
				
											time_selection:;
											
				
				for( i=0 ; i<3 ; ++i ){										// prints times
					cout << " " << i+1 << " - " << setw(2) << right << setfill('0') << hour_and_minute->hour[i] << ":" << setw(2) << setfill('0') << hour_and_minute->minute[i] << endl;
				}
				cout << " -> ";
				
				do{
					cin >> time;
					
					if(time<1||3<time)
						cerr << "\n ! Out of range. Try again -> ";
				}while(time<1||3<time);
				
				if(time==1)					{y=0;}										// y is chosen aircraft type
				else if(time==2 || time==3) {y=1;}
				
				
				
				if(month==1 && (0<day && day<=7)){							// There is a discount in the price of the flight according to the day, month and time of the day.
					aircraft_company->aircraft[y].date_constant=1;
					if(time==1)
						ticket_discount=0.95;
					else
						ticket_discount=1.0;
				}
				else if(month==1 && (7<day && day<=14)){
					aircraft_company->aircraft[y].date_constant=2;
					if(time==1)
						ticket_discount=0.9;
					else
						ticket_discount=0.95;
				}
				else if(month==1 && (14<day && day<=31)){
					aircraft_company->aircraft[y].date_constant=3;
					if(time==1)
						ticket_discount=0.85;
					else
						ticket_discount=0.9;
				}
				else if(month==2){
					aircraft_company->aircraft[y].date_constant=4;
					if(time==1)
						ticket_discount=0.85;
					else
						ticket_discount=0.9;
				}
				else if(month==3 || month ==4){
					aircraft_company->aircraft[y].date_constant=5;
					if(time==1)
						ticket_discount=0.85;
					else
						ticket_discount=0.9;
				}
				else if(month==5 || month == 6){
					aircraft_company->aircraft[y].date_constant=6;
					if(time==1)
						ticket_discount=0.8;
					else
						ticket_discount=0.85;
				}
				
				company_selection:;
				
				cout << "\n Ticket prices :"			// it just print econmy ticket price but, bussines ticket is 1.5 times economy , vip ticket is 2 times economy
				<< "\n 1 - " << aircraft_company[0].company_name << " - " << aircraft_company[0].multiplier*city[go_city-1].distance*ticket_discount << " (economy)."
				<< "\n 2 - " << aircraft_company[1].company_name << " - " << aircraft_company[1].multiplier*city[go_city-1].distance*ticket_discount << " (economy)."
				<< "\n Choose a company -> ";
				
				do{
					cin >> company;
					
					if(company<1||2<company)
						cerr << "\n ! Out of range. Try again -> ";
				}while(company<1||2<company);
				
				
				system("CLS");

				cout << " \n Do you want to go back?"
				<< "\n Return to the city selection, press 1"
				<< "\n Return to the date selection, press 2"
				<< "\n Return to the time selection, press 3"
				<< "\n Return to the company selection, press 4"
				<< "\n NO. press any number else"
				<< "\n -> ";
				
				cin >> selection;
				
				system("CLS");
				
				if(selection==1){
					goto city_selection;
				}
				else if(selection==2) {
					goto date_selection;
				}
				else if(selection==3) {
					goto time_selection;
				}
				else if(selection==4) {
					goto company_selection;
				}
				
				system("CLS");
				
				aircraft_company->aircraft[y].print_Seats();				// prints filled seats in class function
				
				chosen_seats.clear();									// clear the vector
				
				cout << "\n How many seats do you want to buy -> ";
				
				choosable_seat_num = aircraft_company->aircraft[y].vip_seat + aircraft_company->aircraft[y].business_seat + aircraft_company->aircraft[y].economy_seat
				 - aircraft_company->aircraft[y].all_filled_seats.size();				// its calculating how many seat is available
				 
				 
					do{
						cin >> buy_seats;
						if(choosable_seat_num<buy_seats)		cerr << "\n You cannot buy that much seat. Try again(max "<< choosable_seat_num <<" ) -> ";
						else if(buy_seats<1)					cerr << "\n At least you have to buy 1 seat. Try again -> ";				
						
					}while(buy_seats<1 || choosable_seat_num<buy_seats);	
					
					
				cout << "\n\n Choose seats -> ";
				
				for( i=0 ; i<buy_seats ; ++i ){
					cin>>a;
					chosen_seats.push_back(a);
				}
				
				sort(chosen_seats.begin(),chosen_seats.end());
				
				Collision:;			// if had a collision in second for loop check again
				
				collision=0;
				
				sort(chosen_seats.begin(),chosen_seats.end());
				
				for( i=0 ; i<buy_seats ; i++){							// if choose same seat
					for(  b=0 ; b<i ; b++){
						if(chosen_seats[i]==chosen_seats[b]){
							cerr << "\n Seat number of : " << chosen_seats[i] << " entered more than one. Please change -> ";
							cin >> a;
							chosen_seats[i] = a;
							i--;
							collision=1;
						}
					}
				}
				
				
				for( i=0 ; i<aircraft_company->aircraft[y].all_filled_seats.size() ; i++ ){
					for( a=0 ; a<buy_seats ; a++ ){
						if(chosen_seats[a]==aircraft_company->aircraft[y].all_filled_seats[i]){
							cerr << "\n seat number of " << chosen_seats[a] << " alread bought. Please change -> ";
							cin >> chosen_seats[a];
							i--;
							collision=1;
						}
					}
				}
				
				if(collision==1){				// if choose already choosen seat in the bought seats loop, reruns the checking codes again
					goto Collision;
				}
				
				sort(chosen_seats.begin(),chosen_seats.end());				// auto sort 
				
				cout << "\n How many children? (children must be accompanied by at least one adult):";
				
				seat_num_in_vip=0,seat_num_in_bus=0,seat_num_in_eco=0;
				child_in_vip=0,child_in_bus=0,child_in_eco=0;
				
				for(i=0 ; i<chosen_seats.size() ; i++){
					if(chosen_seats[i]<=aircraft_company->aircraft[y].vip_seat)
						seat_num_in_vip++;
					else if(chosen_seats[i] <= aircraft_company->aircraft[y].business_seat+aircraft_company->aircraft[y].vip_seat)
						seat_num_in_bus++;
					else								// if between, sum of business and vip seat num, and total seat
						seat_num_in_eco++;
						
				}
				
				a=0;
				
				while(a==0){						// children must be accompanied by at least 1 adult
					try{							// if the number of tickets is 1 or 0, it passes as there can be no children.
						a=1;						// or number of children is equal to or higher than number of adult, prints error
						if(1<seat_num_in_vip){
							cout << "\n How many children in vip -> ";
							cin >> child_in_vip;
							if(child_in_vip<0)
								throw 0;
							else if(seat_num_in_vip<=child_in_vip)
								throw 1;
						}
						else		cout << "\n There are not enough seats for a child in vip seats.\n";
						
						if(1<seat_num_in_bus){
							cout << "\n How many children in bussines -> ";
							cin >> child_in_bus;
							if(child_in_bus<0)
								throw 0;
							else if(seat_num_in_bus<=child_in_bus)
								throw 1;
						}
						else		cout << "\n There are not enough seats for a child in bussines seats.\n";
						
						if(1<seat_num_in_eco){
							cout << "\n How many children in economy -> ";
							cin >> child_in_eco;
							if(child_in_eco<0)
								throw 0;
							else if(seat_num_in_eco<=child_in_eco)
								throw 1;
						}
						else		cout << "\n There are not enough seats for a child in bussines economy.\n";
						
						
					}
					catch(int &error){
						if(error==0)
							cerr << "\n ! ! ! Children number does not lower than zero. Try again at the begining.\n";
							
						else if(error==1)
							cerr << "\n ! ! ! The number of children cannot exceed the number of seats and at least one adult is required."
							"\n That is, there must be at most one less number of children from the number of seats purchased."
							"\n Try again at the begining.\n";
							
							a=0;
					}
					
				}
				
				price=0;
														// calculating price
				price += (seat_num_in_vip-child_in_vip) * aircraft_company[y].multiplier * city[go_city-1].distance * ticket_discount * 2.0;
				price += (child_in_vip) 				* aircraft_company[y].multiplier * city[go_city-1].distance * ticket_discount * 2.0 * 0.9;
				price += (seat_num_in_bus-child_in_bus) * aircraft_company[y].multiplier * city[go_city-1].distance * ticket_discount * 1.5;
				price += (child_in_bus) 				* aircraft_company[y].multiplier * city[go_city-1].distance * ticket_discount * 1.5 * 0.9;
				price += (seat_num_in_eco-child_in_eco) * aircraft_company[y].multiplier * city[go_city-1].distance * ticket_discount * 1.0;
				price += (child_in_eco) 				* aircraft_company[y].multiplier * city[go_city-1].distance * ticket_discount * 1.0 * 0.9;
				
				system("CLS");
				
				cout << "\n Your Ticket price : " << price << "\n Do you want to buy ?\n 1 - Yes\n 2 - Go back and change something\n Otherwise - No\n -> ";
				cin >> selection;
				
				if(selection==1){					// getting passenger info
					
					cin.ignore();
					if(return_ticket==0){
					    for(i=0; i<1; i++) {
					        cout << "Please enter the customer(s) information:" << endl;
					        cout << "Please enter the " << i+1 << ". passengers name: ";
					        getline(cin, passenger_name);
					        cout << "Please enter the " << i+1 << ". passengers gender: ";
					        cin >> gender;
					        cout << "Please enter the " << i+1 << ". passengers birth date: ";
					        cin >> date_of_birth;
					        cout << "Please enter the " << i+1 << ". passengers email address: ";
					        cin >> email_address;
					        cout << "Please enter the " << i+1 << ". passengers telephone number(10 digits): ";
					        cin >> telephone_number;
					        while(telephone_number.size() != 10) {
					            cout << "Telephone number should be 10 digits please enter your telephone number again!: ";
					            cin >> telephone_number;
					        }
					        cout << "Please enter the " << i+1 << ". passengers ID number(11 digits): ";
					        cin >> id_number;
					        while(id_number.size() != 11) {
					            cout << "ID number should be 11 digits please enter your telephone number again!: ";
					            cin >> id_number;
					        }
					        
					        passenger[ passenger_num ].dateOfBirth		=date_of_birth;
					        passenger[ passenger_num ].emailAddress		=email_address;
					        passenger[ passenger_num ].gender			=gender;
					        passenger[ passenger_num ].idNumber			=id_number;
					        passenger[ passenger_num ].passengerName	=passenger_name;
					        passenger[ passenger_num ].telephoneNumber	=telephone_number;
					
					    }
					
						cin.ignore();
					    cout << "-----------------Payment-----------------" << endl;
					    cout << "Please enter the credit cards holders name: ";
					    getline(cin, credit_card_name);
					    cout << "Please enter the card number(16 digits): ";
					    cin >> credit_card_number;
					    while(credit_card_number.size() != 16) {
					        cout << "Card number should be 16 digits please enter your card number again!: ";
					        cin >> credit_card_number;
					    }
					    cout << "Please enter the credit card CVC(3 digits): ";
					    cin >> credit_card_CVC;
					    while(credit_card_CVC.size() != 3) {
					        cout << "CVC should be 3 digits please enter your CVC again!: ";
					        cin >> credit_card_CVC;
					    }
					    cout << "Please enter the credit expiration date:(DD.MM.YYYY)(10 digits): ";
					    cin >> credit_card_date;
					    while(credit_card_date.size() != 10) {
					        cout << "Expiration date should be 10 digits please enter the expiration date again!: ";
					        cin >> credit_card_date;
					    }
						
					    payment[passenger_num].creditCardCVC		=credit_card_CVC;
					    payment[passenger_num].creditCardDate		=credit_card_date;
					    payment[passenger_num].creditCardName		=credit_card_name;
					    payment[passenger_num].creditCardNumber		=credit_card_number;
					
					}											// yes I know there are lots of assign but otherwise I cannot handle with this sorry, -Ahmet
					
					
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].where_from				="Ankara";
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].where_from_airport		="ESB";
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].to_where				=city[go_city-1].city;
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].to_where_airport		=city[go_city-1].airport;
					if(return_ticket==1){
						passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].where_from			=city[go_city-1].city;
						passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].where_from_airport	=city[go_city-1].airport;
						passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].to_where			="Ankara";
						passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].to_where_airport	="ESB";
					}
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].ticket_price			=price;
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].vip_ticket				=seat_num_in_vip-child_in_vip;
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].bus_ticket				=seat_num_in_bus-child_in_bus;
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].eco_ticket				=seat_num_in_eco-child_in_eco;
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].vip_child				=child_in_vip;
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].bus_child				=child_in_bus;
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].eco_child				=child_in_eco;
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].purchased_seat_num		=chosen_seats;
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].day					=day;
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].month					=month;
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].year					=2022;
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].minute					=hour_and_minute->minute[time-1];
					passenger[ passenger_num ].ticket[ passenger[passenger_num].ticket_num ].hour					=hour_and_minute->hour[time-1];
					
					
					passenger[ passenger_num ].ticket_num++;
					
			
			
					if(return_ticket==0){
						cout << "\n Would you like to buy a return ticket?"
						"\n 1 - Yes"
						"\n Otherwise - No "
						"\n -> ";
						cin >> return_ticket;
						if(return_ticket==1){
							system("CLS");
							goto RETURN_TICKET;
						}
					}
					
					
					
				}
				
				else if(selection==2){
					cout << " \n Do you want to go back?"
					<< "\n Return to the city selection, press 1"
					<< "\n Return to the date selection, press 2"
					<< "\n Return to the time selection, press 3"
					<< "\n Return to the company selection, press 4"
					<< "\n NO. press any number else"
					<< "\n -> ";
					
					cin >> selection;
					system("CLS");
					
					if(selection==1){
						goto city_selection;
					}
					else if(selection==2) {
						goto date_selection;
					}
					else if(selection==3) {
						goto time_selection;
					}
					else if(selection==4) {
						goto company_selection;
					}
				}
				
				x=-998;		// go to menu
				delete hour_and_minute;
				
				break;
				
				 
	//*****************************************************************************************************
				 
				case 2:
					cout << "\n Enter your ID please : ";							
			        cin >> passenger_id;
			        while(passenger_id.size()!=11) {
			            cout << "ID number should be 11 digits please enter your telephone number again!: ";
			            cin >> passenger_id;
			        }
			        
			        y=0;
			        
			        for( i=0 ; i<=passenger_num ; i++){
			        	if(passenger_id==passenger[i].idNumber){
			        		for(a=0;a<passenger[i].ticket_num;a++){
			        			
			        			y=1;							//user found
								
								cout << "\n Dear " <<passenger[ i ].passengerName << " your ticket is : \n\n"				// prints ticket infos
								<<" From : "											<<passenger[ i ].ticket[ a ].where_from
								<< " ("													<<passenger[ i ].ticket[ a ].where_from_airport<<")"
								<<"  to : "												<<passenger[ i ].ticket[ a ].to_where
								<< " ("													<<passenger[ i ].ticket[ a ].to_where_airport<<")"
								<<"\n Price : "											<<passenger[ i ].ticket[ a ].ticket_price
								<<"\n Fligth date(D.M.Y) : "							<<passenger[ i ].ticket[ a ].day<<'.'<<passenger[ i ].ticket[ a ].month<<'.'<<passenger[ i ].ticket[ a ].year
								<<"\n Fligth time : "<<setw(2) << right << setfill('0') <<passenger[ i ].ticket[ a ].hour << ":" << setw(2) << setfill('0') << passenger[ i ].ticket[ a ].minute
								<<"\n\n Number of adult ticket in vip : " 				<<passenger[ i ].ticket[ a ].vip_ticket
								<<"  \n Number of child ticket in vip : " 				<<passenger[ i ].ticket[ a ].vip_child
								<<"  \n Number of adult ticket in bussiness : " 		<<passenger[ i ].ticket[ a ].bus_ticket
								<<"  \n Number of child ticket in bussiness : " 		<<passenger[ i ].ticket[ a ].bus_child
								<<"  \n Number of adult ticket in economy : " 			<<passenger[ i ].ticket[ a ].eco_ticket
								<<"  \n Number of child ticket in economy : " 			<<passenger[ i ].ticket[ a ].eco_child
								<<"\n Your seat numbers :  ";
								
								
								for(b=0;b<passenger[ i ].ticket[ a ].purchased_seat_num.size() ; b++)			//prints bought seats
									cout<<passenger[ i ].ticket[ a ].purchased_seat_num[b]<<"  ";
									
								cout<<endl <<endl;
							} 
						}
					}
					
					if(y==0)					// if ýd's don't match
						cout << "\n User not found !\n\n";
					
					system("PAUSE");
					system("CLS");
					
					x=-998;						// go to menu
					
			default:							// menu (if user enter out of range print menu again
				if(x!=-999)						// if first run don't clear console
					system("CLS");
				cout << "\n 1 - Buy Ticket"
				<< "\n 2 - Check ticket"
				<< "\n 0 - Exit "
				<< "\n -> ";
				cin >> x;
				
				if(x==1)
					passenger_num++;
					
				
				if(x==0){
					cout << " \n\n BYE ! \n\n";
					system("PAUSE");
				}
				break;
		}
		
		
	}while(x!=0);
	
	
	cout << "\n\n\nEnd\n\n";
	
	return 0;
}



