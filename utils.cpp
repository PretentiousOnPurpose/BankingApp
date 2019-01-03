#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include "utils.hpp"
using namespace std;

string genTransID() {
  time_t rawtime;
  struct tm * timeinfo;
  char transID[80];

  time (&rawtime);
  timeinfo = localtime (&rawtime);

  strftime (transID,80,"%y%m%d%H%M%S",timeinfo);
  return transID;
}

string getCurrDateTime() {
  time_t rawtime;
  struct tm * timeinfo;
  char currDate[80];

  time (&rawtime);
  timeinfo = localtime (&rawtime);

  strftime (currDate,80,"%d-%m-%y %H:%M:%S",timeinfo);
  return currDate;
}
