#include <iostream>
#include <pqxx/pqxx>
using namespace pqxx;
using namespace std;

string getAccountNewNo(pqxx::connection *);

void createAccount(pqxx::connection * C) {
    string newAccNo = getAccountNewNo(C);

    string sql;

    string cnf;
    string name;
    string pin;
    string phone;
    string email;
    string aadhar;
    string amount;

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
        cout << "\n\nLet's try again\n";
        cout << "\nFlushing existing details... Please wait\n";
        usleep(5 * 1000000);
        createAccount(C);
    }
    cout << "\n\nCreating a new account for " << name << endl;

    cout << "Processing... Please wait\n";

    sql = "INSERT INTO accounts (accno, name, pin, phone, email, aadhar, amount) VALUES ('";
    sql += newAccNo +"','"+ name +"','"+ pin +"','"+ phone +"','"+ email +"','"+ aadhar +"'," + amount + ");";
    work W(*C);
    try {
      W.exec(sql);
      W.commit();
    } catch (const std::exception &e) {
      cout << "\nSomething went wrong... Provided information might have been incorrent or in wrong format\nPlease try again\n";
      cout << "\n\nHit Return or Enter for Main Screen\n\n";
      cin.ignore();
      while (cin.get() != '\n') {}
      return;
    }
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
    while (cin.get() != '\n') {}
}

string getAccountNewNo(pqxx::connection * C) {
  string sql = "SELECT COUNT(*) FROM accounts";
  nontransaction N(*C);
  result R(N.exec(sql));
  result::const_iterator c = R.begin();
  return to_string(1000000000 + c[0].as<int>() + 1);
}
