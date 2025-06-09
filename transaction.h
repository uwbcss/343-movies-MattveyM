#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

class Movie;
class Customer;

class Transaction {
public:
  Transaction(const string &type, Customer *customer, Movie *movie);
  virtual ~Transaction() = default;

  virtual string toString() const = 0;
  virtual bool execute() = 0;

  string getType() const { return type; }
  Customer *getCustomer() const { return customer; }
  Movie *getMovie() const { return movie; }

protected:
  string type;
  Customer *customer;
  Movie *movie;
};

class BorrowTransaction : public Transaction {
public:
  BorrowTransaction(Customer *customer, Movie *movie);
  string toString() const override;
  bool execute() override;
};

class ReturnTransaction : public Transaction {
public:
  ReturnTransaction(Customer *customer, Movie *movie);
  string toString() const override;
  bool execute() override;
};

#endif