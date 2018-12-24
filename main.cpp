#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "account.h"
using namespace std;

void mainView();
void createAccount();
void accessAccount();
void loginAccount();
void dashboard();
void depositCash();
void withdrawCash();
void sendMoney();
void requestMoney();
void currentBalance();
void updateAccount();
void deleteAccount();

bool loginedIn;
int currSelection;

int main() {
    mainView();
    cin >> currSelection;

    switch (currSelection) {
        case 1:
            cout << "\nNew Account Creation\nProcessing... Please wait" << endl;
            usleep(1.25 * 1000000);
            createAccount();
            break;
        case 2:
            cout << "\nAccess Your Account\nProcessing... Please wait" << endl;
            usleep(1.25 * 1000000);
            accessAccount();
            break;
        case 3:
            cout << "\nUpdate Account Info\nProcessing... Please wait" << endl;
            usleep(1.25 * 1000000);
            updateAccount();
            break;
        case 4:
            cout << "\nAccount Deletion\nProcessing... Please wait" << endl;
            usleep(1.25 * 1000000);
            deleteAccount();
            break;
        default:
            cout << "\nPlease select a valid option" << endl;

    }

    return 0;
}

void mainView() {
    system("clear");
    cout << "\nChawat eBanking System\n\n" << endl;
    cout << "How can we help you?\n";
    cout << "1. Create a new account\n";
    cout << "2. Access your account\n";
    cout << "3. Update account info\n";
    cout << "4. Delete an existing account\n";

    cout << "\nPlease enter your choice: ";
}

void createAccount() {
    cout << "\nAccount Created\n";
}

void accessAccount() {
    if (!loginedIn) {
        loginAccount();
    } else {
        dashboard();
    }
}

void loginAccount() {
    system("clear");
    string accNo;
    int pin;
    cout << "\nChawat eBanking System\n\n";
    cout << "Login to your account\n\n";
    cout << "Account No: ";
    cin >> accNo;
    // account acc = getAccountDetails();
    // if (accNo) (Validation)
    // mark loginedIn -> true
    
    cout << "Enter Pin: ";
    cin >> pin;

    cout << "\nValidating\n";
    usleep(1.25 * 1000000);
    cout << "\nLogin Successful\n\n";
    usleep(1.25 * 1000000);
    // dashboard(acc);
    dashboard();
}

void dashboard() {
    system("clear");
    
    int action;

    cout << "\nChawat eBanking System\n\n";
    cout << "Hello " << "Name\n\n" << endl;
    cout << "1. Deposit Cash\n";
    cout << "2. Withdraw Cash\n";
    cout << "3. Send Money\n";
    cout << "4. Request Money\n";
    cout << "5. Check Current Balance\n";
    cout << "\nPlease enter your choice: ";
    cin >> action;

    switch(action) {
        case 1:
            depositCash();
        case 2:
            withdrawCash();
        case 3:
            sendMoney();
        case 4:
            requestMoney();
        case 5:
            currentBalance();   
    }    
}

void depositCash() {

}

void withdrawCash() {

}

void sendMoney() {

}

void requestMoney() {

}

void currentBalance() {
    
}

void updateAccount() {
    cout << "\nAccount Updated\n";
}

void deleteAccount() {
    cout << "\nAccount Deleted\n";
}