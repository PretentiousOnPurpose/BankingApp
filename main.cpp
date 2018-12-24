#include <iostream>
#include <string>
#include <ios>  
#include <limits>  
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
void logout();
void updateAccount();
void deleteAccount();


bool loginedIn;
int currSelection;

int main() {
    mainView();

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
}

void createAccount() {
    string cnf;
    string name;
    int pin;
    string phone;
    string email;
    string aadhar;
    double amt;
    
    system("clear");
    cout << "\nChawat eBanking System\n\n";
    cout << "New Account\n";
    cout << "Enter the required details\n";
    cout << "Name: ";
    cin.ignore();
    getline (cin, name);
    cout << "Pin (for login): ";
    cin >> pin;
    cout << "Phone: ";
    cin >> phone;
    cout << "Email: ";
    cin >> email;
    cout << "Aadhar: ";
    cin >> aadhar;
    cout << "Starting Amount: ";
    cin >> amt;

    cout << "\n\nPlease confirm the above details\nShall we proceed ? [Y/N]: ";
    cin >> cnf;
    if (!(cnf == "Y" || cnf == "y")) {
        cout << "\n\nLet's try again\n";
        cout << "\nFlushing existing details... Please wait\n";
        usleep(2 * 1000000);
        createAccount();
    }
    cout << "\n\nCreating a new account for " << name << endl;
    cout << "Processing... Please wait\n";
    cout << "\nAccount Creation Successful\n";
    cout << "\nRedirecting to Main Menu... Please wait\n";
    usleep(2 * 1000000);
    mainView();
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
    loginedIn = true;
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
    cout << "6. Logout\n";
    cout << "\nPlease enter your choice: ";
    
    cin >> action;

    switch(action) {
        case 1:
            depositCash();
            break;
        case 2:
            withdrawCash();
            break;
        case 3:
            sendMoney();
            break;
        case 4:
            requestMoney();
            break;
        case 5:
            currentBalance();   
            break;
        case 6:
            logout();
            break;
        default:
            cout << "\nInvalid Choice\n";
            cout << "Refreshing in 2 seconds\n";
            dashboard();
    }    
}

void depositCash() {
    double cash;
    char end;

    system("clear");
    cout << "\nChawat eBanking System\n\n";
    currentBalance();
    cout << "\nPlease enter the amount for deposition: ₹";
    
    
    cin >> cash;
    cin.ignore();
    // Some thing with DB
    cout << "\nProcessing... Please wait\n" << endl;
    usleep(1.25 * 1000000);
    system("clear");
    cout << "\nChawat eBanking System\n\n";
    cout << "Cash deposited successfully\n\n";
    cout << "Your transaction id: A862JT9112\n";
    currentBalance();


    cout << "\n\nHit Return or Enter for Main Screen\n\n";

    while (cin.get() != '\n') {
        
    }
    
    dashboard();

}

void withdrawCash() {

}

void sendMoney() {

}

void requestMoney() {

}

void currentBalance() {
    cout << "Your Balance: ₹" << "10000" << endl;
}

void logout() {
    loginedIn = false;
    mainView();
}

void updateAccount() {
    cout << "\nAccount Updated\n";
}

void deleteAccount() {
    cout << "\nAccount Deleted\n";
}
