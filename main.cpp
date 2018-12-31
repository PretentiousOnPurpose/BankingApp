#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <ios>
#include <limits>
#include <cstdlib>
#include <unistd.h>
#include "account.h"
#include "createAcc.h"
using namespace std;
using namespace pqxx;

void mainView(); // DONE
void createAcc(); // DONE
void accessAccount();
void loginAccount();
void dashboard();
void depositCash();
void withdrawCash();
void sendMoney();
void requestMoney();
void currentBalance();
void getTransHistory();
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
  pqxx::connection * C = new pqxx::connection("dbname = bank user = postgres password = 007 hostaddr = 127.0.0.1 port = 5432");
  try {
    if (C->is_open()) {
        system("clear");
        cout << "\nChawat eBanking System\n\n" << endl;
        cout << "How can we help you?\n";
        cout << "1. Create a new account\n";
        cout << "2. Access your account\n";
        cout << "3. Update account info\n";
        cout << "4. Delete an existing account\n";
        cout << "5. Exit\n";

        choice:
            cout << "\nPlease enter your choice: ";

        cin >> currSelection;

        switch (currSelection) {
            case 1:
                cout << "\nNew Account Creation\nProcessing... Please wait" << endl;
                usleep(1.25 * 1000000);
                createAcc();
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
            case 5:
                system("clear");
                cout << "\nChawat eBanking System\n\n" << endl;
                cout << "Thank You\n";
                exit(0);
                break;
            default:
                cout << "\nPlease select a valid option" << endl;
                goto choice;
        }
        C->disconnect();
    } else {
      throw "DATABASE ERROR";
    }
  } catch (const std::exception &e) {
    system("clear");
    cout << "\nDATABASE CONN ERROR\n";
    exit(0);
  }
}

void createAcc() {
  createAccount();
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
    cout << "6. Get Transaction History\n";
    cout << "7. Logout\n";
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
            getTransHistory();
            break;
        case 7:
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

void getTransHistory() {
    // system("clear");
    // cout << "\nChawat eBanking System\n\n";
    // cout << "Fetching Details... Please wait";
    // string sql;
    // try {
    //     sql = "SELECT * FROM transactions";
    //     nontransaction N(C);
    //     result R(N.exec(sql));
    //     int i = 1;
    //     usleep(1.25 * 1000000);
    //
    //     system("clear");
    //     cout << "\nChawat eBanking System\n\n";
    //
    //
    //     for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
    //         cout << " -- -- -- -- -- " << i << " -- -- -- -- -- ";
    //         cout << "Transaction ID = " << c[0].as<string>() << endl;
    //         cout << "Source Account = " << c[1].as<string>() << endl;
    //         cout << "Dest. Account = " << c[2].as<string>() << endl;
    //         cout << "Amount = " << c[3].as<float>() << endl;
    //         cout << "Desp. = " << c[4].as<string>() << endl;
    //         cout << " -- -- -- -- -- -- -- -- -- -- \n";
    //         i++;
    //     }
    //     cout << "Operation done successfully" << endl;
    //     C.disconnect ();
    // } catch(const std::exception &e) {
    //     cout << "DB Read Failed\n";
    // }
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
