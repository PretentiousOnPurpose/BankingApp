#ifndef CREATEACC_H
#define CREATEACC_H

#include <string>
#include <pqxx/pqxx>
using namespace std;

string getAccountNewNo(pqxx::connection *);
void createAccount();

#endif
