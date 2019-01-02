#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "account.h"
#include "createAcc.h"
#include "accessAcc.h"
using namespace std;
using namespace pqxx;

void mainView(); // DONE
void createAcc(); // DONE
void accessAccount();
void updateAccount();
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
}

void createAcc() {
  createAccount();
  mainView();
}

void accessAccount() {
  loginAccount();
  mainView();
}


void updateAccount() {
    cout << "\nAccount Updated\n";
}

void deleteAccount() {
    cout << "\nAccount Deleted\n";
}
