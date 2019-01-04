#include <iostream>
#include <pqxx/pqxx>
#include <ctime>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <stdexcept>
#include "utils.hpp"
#include "createAcc.hpp"

using namespace pqxx;
using namespace std;



void createAccount() {
    pqxx::connection * C = new pqxx::connection("dbname = bank user = postgres password = 007 hostaddr = 127.0.0.1 port = 5432");

    string newAccNo = getAccountNewNo(C);

    string sql;
    string cnf;
    string name;
    string pin;
    string phone;
    string email;
    string aadhar;
    string amount;
    pqxx::work * W;
startCreate:
    system("clear");
    cout << "\nChawat eBanking System\n\n";
    cout << "New Account\n";
    cout << "Enter the required details\n";
    cout << "Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Pin (for login): ";
    cin >> pin;
    cout << "Phone: ";
    cin >> phone;
    cout << "Email: ";
    cin >> email;
    cout << "Aadhar: ";
    cin >> aadhar;
    cout << "Starting Amount: ";
    cin >> amount;

    cout << "\n\nPlease confirm the above details\nShall we proceed ? [Y/N]: ";
    cin >> cnf;
    if (!(cnf == "Y" || cnf == "y")) {
      fail:
        cout << "\nLet's try again\n";
        cout << "\nFlushing existing details... Please wait\n";
        usleep(5 * 1000000);
        goto startCreate;
    }
    cout << "\n\nCreating a new account for " << name << endl;

    cout << "Processing... Please wait\n";

    sql = "INSERT INTO accounts (accno, name, pin, phone, email, aadhar, amount) VALUES ('";
    sql += newAccNo +"','"+ name +"','"+ pin +"','"+ phone +"','"+ email +"','"+ aadhar +"'," + amount + ");";

    try {
      if (phone.length() != 10 || aadhar.length() != 12) {
          cout << "Invalid Details Provided\n";
          goto fail;
      }
      W = new pqxx::work(*C);
      W->exec(sql);
      W->commit();
    } catch (const std::exception &e) {
      cout << "\nSomething went wrong... Provided information might have been incorrent or in wrong format\n";
      cout << "\nHit Return or Enter to Try Again...\n\n";
      cin.ignore();
      while (cin.get() != '\n') {}
      goto fail;
    }

    free(W);

    string transID = genTransID();
    sql = "INSERT INTO transactions (transid, src, dst, timeDate, desp) VALUES ('" + transID + "','" + newAccNo + "','CASH','" + getCurrDateTime() + "'," + "'WITHDRAWN ₹ " + amount + " BY CASH');";

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
    cout << "\nChawat eBanking System\n\n" << endl;
    cout << "Account Creation Successful\n\n";
    cout << "Name: " << name << endl;
    cout << "Account No: " << newAccNo << endl;
    cout << "Phone: " << phone << endl;
    cout << "Email: " << email << endl;

    cout << "\n\nHit Return or Enter for Main Screen\n\n";
    cin.ignore();
    C->disconnect();
    delete(C);
    while (cin.get() != '\n') {}
}

string getAccountNewNo(pqxx::connection * C) {
  string sql = "SELECT MAX(accno) FROM accounts";
  nontransaction N(*C);
  result R(N.exec(sql));
  result::const_iterator c = R.begin();
  return to_string(c[0].as<int>() + 1);
}
