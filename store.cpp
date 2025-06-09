#include "store.h"
#include "command.h"
#include "factory.h"
#include "transaction.h"
#include <fstream>
#include <iostream>
#include <sstream>

Store::Store() { registerFactories(); }

Store::~Store() {
  for (Movie *movie : movies) {
    delete movie;
  }

  // Clean up customers from hash table
  for (int i = 1000; i <= 9999; ++i) {
    Customer **customer = customers.find(i);
    if (customer != nullptr && *customer != nullptr) {
      delete *customer;
    }
  }
}

void Store::registerFactories() {
  MovieFactory &movieFactory = MovieFactory::getInstance();
  movieFactory.registerMovie('F', new Comedy());
  movieFactory.registerMovie('D', new Drama());
  movieFactory.registerMovie('C', new Classic());

  CommandFactory &commandFactory = CommandFactory::getInstance();
  commandFactory.registerCommand('I', new InventoryCommand());
  commandFactory.registerCommand('H', new HistoryCommand());
  commandFactory.registerCommand('B', new BorrowCommand());
  commandFactory.registerCommand('R', new ReturnCommand());
}

bool Store::loadMovies(const string &filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error opening movies file: " << filename << endl;
    return false;
  }

  string line;
  while (getline(file, line)) {
    if (line.empty()) {
      continue;
    }

    char movieType = line[0];
    Movie *movie = MovieFactory::getInstance().createMovie(movieType);

    if (movie != nullptr && movie->setData(line)) {
      movies.insert(movie);
    } else {
      delete movie;
      cout << "Unknown movie type: " << movieType
           << ", discarding line: " << line.substr(3) << endl;
    }
  }

  file.close();
  return true;
}

bool Store::loadCustomers(const string &filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error opening customers file: " << filename << endl;
    return false;
  }

  string line;
  while (getline(file, line)) {
    if (line.empty()) {
      continue;
    }

    stringstream ss(line);
    int id;
    string lastName;
    string firstName;

    ss >> id >> lastName >> firstName;
    Customer *customer = new Customer(id, lastName, firstName);
    customers.insert(id, customer);
  }

  file.close();
  return true;
}

bool Store::processCommands(const string &filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error opening commands file: " << filename << endl;
    return false;
  }

  string line;
  while (getline(file, line)) {
    if (line.empty()) {
      continue;
    }

    char commandType = line[0];
    Command *command = CommandFactory::getInstance().createCommand(commandType);

    if (command != nullptr && command->setData(line)) {
      command->execute(this);
      delete command;
    } else {
      delete command; // Safe to delete nullptr
      cout << "Unknown command type: " << commandType
           << ", discarding line: " << line.substr(1) << endl;
    }
  }

  file.close();
  return true;
}

void Store::displayInventory() const {
  cout << "==========================" << endl;

  // Display comedies first
  for (const Movie *movie : movies) {
    if (movie->getType() == 'F') {
      cout << movie->toString() << endl;
    }
  }

  // Display dramas
  for (const Movie *movie : movies) {
    if (movie->getType() == 'D') {
      cout << movie->toString() << endl;
    }
  }

  // Display classics
  for (const Movie *movie : movies) {
    if (movie->getType() == 'C') {
      cout << movie->toString() << endl;
    }
  }
}

bool Store::displayCustomerHistory(int customerId) {
  Customer **customerPtr = customers.find(customerId);
  if (customerPtr != nullptr && *customerPtr != nullptr) {
    cout << "==========================" << endl;
    (*customerPtr)->displayHistory();
    return true;
  }
  cout << "Customer ID " << customerId << " not found" << endl;
  return false;
}

Movie *Store::findMovie(char type, const string &criteria) {
  for (Movie *movie : movies) {
    if (movie->getType() == type && movie->matchesSearchCriteria(criteria)) {
      return movie;
    }
  }
  return nullptr;
}

Customer *Store::findCustomer(int id) {
  Customer **customerPtr = customers.find(id);
  return (customerPtr != nullptr && *customerPtr != nullptr) ? *customerPtr
                                                             : nullptr;
}

bool Store::borrowMovie(int customerId, char movieType,
                        const string &criteria) {
  // Check for valid movie type
  if (movieType != 'F' && movieType != 'D' && movieType != 'C') {
    cout << "Invalid movie type " << movieType
         << ", discarding line: " << criteria << endl;
    return false;
  }

  Customer *customer = findCustomer(customerId);
  if (customer == nullptr) {
    cout << "Invalid customer ID " << customerId
         << ", discarding line: " << criteria << endl;
    return false;
  }

  Movie *movie = findMovie(movieType, criteria);
  if (movie == nullptr) {
    cout << "Invalid movie " << criteria << " for customer "
         << customer->getFullName() << ", discarding line: " << endl;
    return false;
  }

  BorrowTransaction *transaction = new BorrowTransaction(customer, movie);
  bool success = transaction->execute();

  if (success) {
    customer->addTransaction(transaction);
  } else {
    delete transaction;
  }

  return success;
}

bool Store::returnMovie(int customerId, char movieType,
                        const string &criteria) {
  // Check for valid movie type
  if (movieType != 'F' && movieType != 'D' && movieType != 'C') {
    cout << "Invalid movie type " << movieType
         << ", discarding line: " << criteria << endl;
    return false;
  }

  Customer *customer = findCustomer(customerId);
  if (customer == nullptr) {
    cout << "Invalid customer ID " << customerId
         << ", discarding line: " << criteria << endl;
    return false;
  }

  Movie *movie = findMovie(movieType, criteria);
  if (movie == nullptr) {
    cout << "Invalid movie " << criteria << " for customer "
         << customer->getFullName() << ", discarding line: " << endl;
    return false;
  }

  ReturnTransaction *transaction = new ReturnTransaction(customer, movie);
  bool success = transaction->execute();

  if (success) {
    customer->addTransaction(transaction);
  } else {
    delete transaction;
  }

  return success;
}