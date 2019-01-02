#include <iostream>
#include <pqxx/pqxx>
#include <assert.h>
using namespace pqxx;
using namespace std;

bool loginedIn;

void loginAccount();
void dashboard(string, string);
void depositCash(string, string);
void withdrawCash();
void sendMoney();
void requestMoney();
void currentBalance();
void getTransHistory();
void logout();
string genTransID();


void loginAccount() {
    pqxx::connection * C = new pqxx::connection("dbname = bank user = postgres password = 007 hostaddr = 127.0.0.1 port = 5432");
startLogin:
    string sql;

    system("clear");
    string accNo;
    string pin;
    cout << "\nChawat eBanking System\n\n";
    cout << "Login to your account\n\n";
    cout << "Account No: ";

    cin >> accNo;
    cout << "Enter Pin: ";
    cin >> pin;

    sql = "SELECT EXISTS(SELECT * FROM accounts WHERE accno='" + accNo + "');";
    nontransaction N(*C);
    result R(N.exec(sql));
    result::const_iterator c = R.begin();

    if (c[0].as<bool>() == false) {
      goto fail;
    }

    sql = "SELECT * FROM accounts WHERE accno='" + accNo + "';";
    R = N.exec(sql);
    c = R.begin();

    cout << "\nValidating\n";
    usleep(1 * 1000000);

    if (pin == c[2].as<string>()) {
        loginedIn = true;
        cout << "\nLogin Successful\n\n";
        usleep(1.25 * 1000000);
    } else {
      fail:
        cout << "\nAccount No/Pin incorrect\n";
        cout << "Hit enter to try again...";
        cin.ignore();
        while (cin.get() != '\n') {}
        goto startLogin;
    }
    C->disconnect();
    delete(C);
    dashboard(accNo, c[1].as<string>());
}

void dashboard(string accno, string name) {
startDashboard:
    system("clear");

    int action;

    cout << "\nChawat eBanking System\n\n";
    cout << "Hello " << name << "\n\n" << endl;
    cout << "1. Deposit Cash\n";
    cout << "2. Withdraw Cash\n";
    cout << "3. Send Money\n";
    cout << "4. Check Current Balance\n";
    cout << "5. Get Transaction History\n";
    cout << "6. Logout\n";
    cout << "\nPlease enter your choice: ";

    cin >> action;

    switch(action) {
        case 1:
            depositCash(accno, name);
            break;
        case 2:
            withdrawCash();
            break;
        case 3:
            sendMoney();
            break;
        case 4:
            currentBalance();
            break;
        case 5:
            getTransHistory();
            break;
        case 6:
            logout();
            break;
        default:
            cout << "\nInvalid Choice\n";
            cout << "Refreshing in 2 seconds\n";
            usleep(2 * 1000000);
            dashboard(accno, name);
    }
}

void depositCash(string accno, string name) {
    pqxx::connection * C = new pqxx::connection("dbname = bank user = postgres password = 007 hostaddr = 127.0.0.1 port = 5432");
startDeposit:
    string cash;
    // char end;
    string sql;

    system("clear");
    cout << "\nChawat eBanking System\n\n";
    currentBalance();
    cout << "\nPlease enter the amount for deposition: ₹ ";

    cin >> cash;
    cin.ignore();
    // Some thing with DB
    cout << "\nProcessing... Please wait\n" << endl;

    work W(*C);
    sql = "UPDATE accounts SET amount = amount + " + cash + " WHERE accno = '" + accno + "';";

    try {
      W.exec(sql);
      W.commit();
    } catch(const std::exception &e) {
      cout << "Something went wrong... \n";
      cin.ignore();
      cout << "\nEnter enter to try again...";
      while (cin.get() != '\n') {}
      goto startDeposit;
    }

    usleep(1.25 * 1000000);
    system("clear");
    cout << "\nChawat eBanking System\n\n";
    cout << "Name: " << name << " | " << "Account No: " << accno << endl << endl;
    cout << "₹" << cash << " deposited successfully\n";
    // cout << "Your transaction id: " << genTransID() << endl;

    cout << "\n\nHit Return or Enter for Main Screen\n\n";
    C->disconnect();
    delete(C);

    while (cin.get() != '\n') {}
    dashboard(accno, name);

}
//
void withdrawCash() {
//
}
//
void sendMoney() {
//
}
//
void requestMoney() {
//
}
//
void currentBalance() {
//     cout << "Your Balance: ₹" << "10000" << endl;
}
//
void getTransHistory() {
//     // system("clear");
//     // cout << "\nChawat eBanking System\n\n";
//     // cout << "Fetching Details... Please wait";
//     // string sql;
//     // try {
//     //     sql = "SELECT * FROM transactions";
//     //     nontransaction N(C);
//     //     result R(N.exec(sql));
//     //     int i = 1;
//     //     usleep(1.25 * 1000000);
//     //
//     //     system("clear");
//     //     cout << "\nChawat eBanking System\n\n";
//     //
//     //
//     //     for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
//     //         cout << " -- -- -- -- -- " << i << " -- -- -- -- -- ";
//     //         cout << "Transaction ID = " << c[0].as<string>() << endl;
//     //         cout << "Source Account = " << c[1].as<string>() << endl;
//     //         cout << "Dest. Account = " << c[2].as<string>() << endl;
//     //         cout << "Amount = " << c[3].as<float>() << endl;
//     //         cout << "Desp. = " << c[4].as<string>() << endl;
//     //         cout << " -- -- -- -- -- -- -- -- -- -- \n";
//     //         i++;
//     //     }
//     //     cout << "Operation done successfully" << endl;
//     //     C.disconnect ();
//     // } catch(const std::exception &e) {
//     //     cout << "DB Read Failed\n";
//     // }
}
//
void logout() {
    loginedIn = false;
    // mainView();
    return;
}
