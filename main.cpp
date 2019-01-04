// Author: Chawat
// To Compile: g++ main.cpp utils.cpp accessAcc.cpp createAcc.cpp -lpqxx -lpq -o a.out

#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "utils.hpp"
#include "createAcc.hpp"
#include "accessAcc.hpp"
using namespace std;
using namespace pqxx;

void mainView(); // DONE
void createAcc(); // DONE
void accessAccount();
void deleteAccount();

int currSelection;

int main() {
    mainView();

    return 0;
}

void mainView() {
    pqxx::connection * C = new pqxx::connection("dbname = bank user = postgres password = 007 hostaddr = 127.0.0.1 port = 5432");

    try {
      if (C->is_open()) {}
    } catch(const std::exception &e) {
      system("clear");
      cout << "DATABASE CONNECTION ERROR\n";
      exit(0);
    }
    C->disconnect();
    delete(C);
    run:

        system("clear");
        cout << "\nChawat eBanking System\n\n" << endl;
        cout << "How can we help you?\n";
        cout << "1. Create a new account\n";
        cout << "2. Access your account\n";
        cout << "3. Delete an existing account\n";
        cout << "4. Exit\n";

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
                cout << "\nAccount Deletion\nProcessing... Please wait" << endl;
                usleep(1.25 * 1000000);
                deleteAccount();
                break;
            case 4:
                system("clear");
                cout << "\nChawat eBanking System\n\n" << endl;
                cout << "Thank You\n";
                exit(0);
                break;
            default:
                cout << "\nPlease select a valid option" << endl;
                goto choice;
        }
}

void createAcc() {
  createAccount();
  mainView();
}

void accessAccount() {
  loginAccount();
  mainView();
}

void deleteAccount() {
      string accno;
      string pin;
      string cnf;
      string sql;

      system("clear");
      cout << "\nChawat eBanking System\n\n" << endl;
      cout << "Account Deletion\n" << endl;
      cout << "Enter your Account No: ";
      cin >> accno;
      cout << "Enter your pin: ";
      cin >> pin;

      cout << "\n\nAccount deletion is irreversible, shall we proceed ? [Y/N]: ";
      cin >> cnf;
      cout << "\n\nProcessing request... Please Wait\n";
      if (!(cnf == "Y" || cnf == "y")) {
          cout << "\nProcess Aborted.\n";
          cout << "Redirecting to Main Menu\n";
          usleep(5 * 1000000);
      } else {
          pqxx::connection * C = new pqxx::connection("dbname = bank user = postgres password = 007 hostaddr = 127.0.0.1 port = 5432");
          sql = "SELECT pin FROM accounts WHERE accno = '" + accno + "';";
          pqxx::nontransaction * N = new pqxx::nontransaction(*C);
          result R(N->exec(sql));
          result::const_iterator c = R.begin();
          delete(N);

          if (c[0].as<string>() == pin) {
              pqxx::work * W = new pqxx::work(*C);
              sql = "UPDATE accounts SET pin = 'DELETED' WHERE accno = '" + accno + "';";
              W->exec(sql);
              W->commit();
              usleep(1.25 * 1000000);
              cout << "Account deleted successfully\n";
              cin.ignore();
              delete(W);
              cout << "\n\nHit Return or Enter for Main Screen\n\n";
              while (cin.get() != '\n') {}

          } else {
              cout << "Provided information is incorrect / Internal server issue\nPlease try later\n";
              cin.ignore();
              cout << "\n\nHit Return or Enter for Main Screen\n\n";
              while (cin.get() != '\n') {}
          }
          C->disconnect();
          delete(C);
      }
      mainView();
}
