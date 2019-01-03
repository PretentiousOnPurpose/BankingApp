#ifndef ACCESSACC_H
#define ACCESSACC_H

#include <string>
using namespace std;


void loginAccount();
void dashboard(string, string);
void depositCash(string, string);
void withdrawCash(string, string);
void sendMoney();
void currentBalance(string, string);
void getTransHistory(string, string);
void logout();
void backToDashboard(string, string);

#endif
