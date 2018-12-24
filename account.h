#include <iostream>
#include <string>
using namespace std;

class account {
    string name;
    string phone;
    string email;
    string aadhar;
    string accNo;
    double amt;
    double baseAccNo = 1000000000;

    public:
        account(string name, string phone, string email, string aadhar, double amt, string accNo) {
            this->name = name;
            this->phone = phone;
            this->email = email;
            this->aadhar = aadhar;
            this->amt = amt;
            this->accNo = accNo;
        }

        void printCurrentBalance() {
            cout << "\nCurrent Balance: " << this->amt << endl;
        }
        
};
