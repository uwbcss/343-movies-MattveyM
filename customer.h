#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "transaction.h"
#include <string>
#include <vector>
using namespace std;

class Customer {
public:
  Customer(int id, const string &lastName, const string &firstName);
  ~Customer();

  int getId() const { return id; }
  string getLastName() const { return lastName; }
  string getFirstName() const { return firstName; }
  string getFullName() const { return firstName + " " + lastName; }

  void addTransaction(Transaction *transaction);
  void displayHistory() const;

private:
  int id;
  string lastName;
  string firstName;
  vector<Transaction *> history;
};

#endif