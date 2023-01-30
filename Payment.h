#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

using namespace std;

class Payment {
public:
    Payment();
    Payment(string _creditCardName, string _creditCardNumber, string _creditCardCVC, string _creditCardDate);

    string creditCardNumber, creditCardCVC, creditCardDate, creditCardName;
};

#endif
