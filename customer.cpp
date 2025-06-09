#include "customer.h"
#include "transaction.h"
#include <iostream>
using namespace std;

Customer::Customer(int id, const string &lastName, const string &firstName)
    : id(id), lastName(lastName), firstName(firstName) {}

Customer::~Customer() {
  for (Transaction *trans : history) {
    delete trans;
  }
}

void Customer::addTransaction(Transaction *transaction) {
  history.push_back(transaction);
}

void Customer::displayHistory() const {
  cout << "History for " << id << " " << lastName << " " << firstName << ":"
       << endl;
  if (history.empty()) {
    cout << "No history for " << lastName << " " << firstName << endl;
    return;
  }

  for (const Transaction *trans : history) {
    cout << trans->toString() << endl;
  }
}
