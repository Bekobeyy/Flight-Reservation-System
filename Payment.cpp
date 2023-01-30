#include "Payment.h"



using namespace std;


Payment::Payment() {
    //Default Constructor
}

Payment::Payment(string _creditCardName, string _creditCardNumber, string _creditCardCVC, string _creditCardDate) {

    creditCardName = _creditCardName;
    creditCardNumber = _creditCardNumber;
    creditCardCVC = _creditCardCVC;
    creditCardDate = _creditCardDate;
}
