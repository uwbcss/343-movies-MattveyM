#include "transaction.h"
#include "customer.h"
#include "movie.h"
#include <iostream>

Transaction::Transaction(const string &type, Customer *customer, Movie *movie)
    : type(type), customer(customer), movie(movie) {}

// BorrowTransaction
BorrowTransaction::BorrowTransaction(Customer *customer, Movie *movie)
    : Transaction("Borrow", customer, movie) {}

string BorrowTransaction::toString() const {
  return type + " " + customer->getFullName() + " " + movie->getTitle();
}

bool BorrowTransaction::execute() {
  if (movie->borrowMovie()) {
    cout << "Debug: Borrow " << customer->getId() << " "
         << customer->getFullName() << " " << movie->toString() << endl;
    return true;
  }
  cout << "==========================" << endl;
  cout << customer->getFullName() << " could NOT borrow " << movie->getTitle()
       << ", out of stock: " << endl;
  cout << "==========================" << endl;
  cout << "Failed to execute command: Borrow " << customer->getFullName() << " "
       << movie->getTitle() << endl;
  return false;
}

// ReturnTransaction
ReturnTransaction::ReturnTransaction(Customer *customer, Movie *movie)
    : Transaction("Return", customer, movie) {}

string ReturnTransaction::toString() const {
  return type + " " + customer->getFullName() + " " + movie->getTitle();
}

bool ReturnTransaction::execute() {
  movie->returnMovie();
  cout << "Debug: Return " << customer->getId() << " "
       << customer->getFullName() << " " << movie->toString() << endl;
  return true;
}