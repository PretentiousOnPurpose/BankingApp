#include <iostream>
#include <pqxx/pqxx>
#include <ctime>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "utils.hpp"
#include "accessAcc.hpp"

using namespace pqxx;
using namespace std;

bool loginedIn;


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
    if (loginedIn) {
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
                  withdrawCash(accno, name);
                  break;
              case 3:
                  sendMoney();
                  break;
              case 4:
                  currentBalance(accno, name);
                  break;
              case 5:
                  getTransHistory(accno, name);
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
    } else {
      loginAccount();
    }
}

void depositCash(string accno, string name) {
    pqxx::connection * C = new pqxx::connection("dbname = bank user = postgres password = 007 hostaddr = 127.0.0.1 port = 5432");
startDeposit:
    string amount;
    string sql;
    string transID;

    system("clear");
    cout << "\nChawat eBanking System\n\n";
    cout << "\nPlease enter the amount for deposition: ₹ ";

    cin >> amount;
    cout << "\nProcessing... Please wait\n" << endl;

    pqxx::work * W = new pqxx::work(*C);
    sql = "UPDATE accounts SET amount = amount + " + amount + " WHERE accno = '" + accno + "';";

    try {
      W->exec(sql);
      W->commit();
    } catch(const std::exception &e) {
      cout << "Something went wrong... \n";
      cin.ignore();
      cout << "\nEnter enter to try again...";
      while (cin.get() != '\n') {}
      goto startDeposit;
    }

    free(W);

    transID = genTransID();
    sql = "INSERT INTO transactions (transid, src, dst, timeDate, desp) VALUES ('" + transID + "', 'CASH', '" + accno + "','" + getCurrDateTime() + "'," + "'DEPOSITED ₹ " + amount + " BY CASH');";
    W = new pqxx::work(*C);
    try {
      W->exec(sql);
      W->commit();
    } catch(const std::exception &e) {
      cout << "Something went wrong while processing transaction...\n";
      cout << "Transaction couldn't be registered, however the amount has deposited successfully\n";
      cout << "Registering the issue for further investigation...\n";
      usleep(10 * 1000000);
    }

    delete(W);

    usleep(1.25 * 1000000);
    system("clear");
    cout << "\nChawat eBanking System\n\n";
    cout << "Name: " << name << " | " << "Account No: " << accno << endl << endl;
    cout << "₹" << amount << " deposited successfully\n";
    cout << "Your transaction id: " << transID << endl;

    C->disconnect();
    delete(C);
    backToDashboard(accno, name);
}
//
void withdrawCash(string accno, string name) {
    pqxx::connection * C = new pqxx::connection("dbname = bank user = postgres password = 007 hostaddr = 127.0.0.1 port = 5432");
startDeposit:
    string amount;
    string sql;
    string transID;

    system("clear");
    cout << "\nChawat eBanking System\n\n";
    cout << "\nPlease enter the amount for withdrawl: ₹ ";

    cin >> amount;
    cout << "\nProcessing... Please wait\n" << endl;

    sql = "SELECT amount FROM accounts WHERE accno = '" + accno + "';";
    pqxx::nontransaction * N = new pqxx::nontransaction(*C);
    result R(N->exec(sql));
    delete(N);

    result::const_iterator c = R.begin();

    pqxx::work * W = new pqxx::work(*C);
    sql = "UPDATE accounts SET amount = amount - " + amount + " WHERE accno = '" + accno + "';";

    if (c[0].as<double>() >= atof(amount.c_str())) {
        try {
          W->exec(sql);
          W->commit();
        } catch(const std::exception &e) {
          cout << "Something went wrong... \n";
          cin.ignore();
          cout << "\nEnter enter to try again...";
          while (cin.get() != '\n') {}
          goto startDeposit;
        }
    } else {
        cout << "Processing failed due to insufficient funds...\n";
        cin.ignore();
        cout << "\nEnter enter to try again...";
        while (cin.get() != '\n') {}
    }

    free(W);

    transID = genTransID();
    sql = "INSERT INTO transactions (transid, src, dst, timeDate, desp) VALUES ('" + transID + "','" + accno + "','CASH','" + getCurrDateTime() + "'," + "'WITHDRAWN ₹ " + amount + " BY CASH');";
    W = new pqxx::work(*C);
    try {
      W->exec(sql);
      W->commit();
    } catch(const std::exception &e) {
      cout << "Something went wrong while processing transaction...\n";
      cout << "Transaction couldn't be registered, however the amount has withdrawn successfully\n";
      cout << "Registering the issue for further investigation...\n";
      usleep(10 * 1000000);
    }

    delete(W);

    usleep(1.25 * 1000000);
    system("clear");
    cout << "\nChawat eBanking System\n\n";
    cout << "Name: " << name << " | " << "Account No: " << accno << endl << endl;
    cout << "₹" << amount << " withdrawn successfully\n";
    cout << "Your transaction id: " << transID << endl;

    C->disconnect();
    delete(C);
    backToDashboard(accno, name);
}
//
void sendMoney() {

}

void currentBalance(string accno, string name) {
    string sql = "SELECT amount FROM accounts WHERE accno = '" + accno + "';";
    pqxx::connection * C = new pqxx::connection("dbname = bank user = postgres password = 007 hostaddr = 127.0.0.1 port = 5432");
    pqxx::nontransaction * N = new pqxx::nontransaction(*C);
    result R(N->exec(sql));
    result::const_iterator c = R.begin();

    system("clear");
    cout << "\nChawat eBanking System\n\n";
    cout << "Name: " << name << " | " << "Account No: " << accno << endl << endl;
    cout << "Your Balance: ₹ " << c[0] << endl;

    C->disconnect();
    delete(C);
    backToDashboard(accno, name);
}
//
void getTransHistory(string accno, string name) {
    pqxx::connection * C = new pqxx::connection("dbname = bank user = postgres password = 007 hostaddr = 127.0.0.1 port = 5432");
    pqxx::nontransaction * N = new pqxx::nontransaction(*C);
    int i = 1;
    string sql;

    system("clear");
    cout << "\nChawat eBanking System\n\n";
    cout << "Fetching Details... Please wait\n";
    sql = "SELECT * FROM transactions";

    result R(N->exec(sql));
    delete(N);

    usleep(1.5 * 1000000);

    system("clear");
    cout << "\nChawat eBanking System\n\n";
    cout << "Name: " << name << " | " << "Account No: " << accno << endl;
    cout << "Your Transactions\n\n";
    try {
        for (result::const_iterator c = R.begin(); c != R.end(); ++c, i++) {
            cout << " -- -- -- -- -- " << i << " -- -- -- -- -- \n";
            cout << "Transaction ID = " << c[0].as<string>() << endl;
            cout << "Source Account = " << c[1].as<string>() << endl;
            cout << "Dest. Account = " << c[2].as<string>() << endl;
            cout << "Date = " << c[3].as<string>() << endl;
            cout << "Desp. = " << c[4].as<string>() << endl;
            cout << " -- -- -- -- - END - -- -- -- -- \n\n";
        }
    } catch (const std::exception &e) {
        cout << "No Transactions Found.\n";
    }

    C->disconnect();
    delete(C);
    backToDashboard(accno, name);
}
//
void logout() {
    loginedIn = false;
    return;
}

void backToDashboard(string accno, string name) {
    cout << "\nHit Return or Enter for Dashboard\n\n";
    cin.ignore();
    while (cin.get() != '\n') {}
    dashboard(accno, name);
}
