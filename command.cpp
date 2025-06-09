#include "command.h"
#include "store.h"
#include <iostream>
#include <sstream>

Command::Command(const string &type) : type(type) {}

// InventoryCommand
InventoryCommand::InventoryCommand() : Command("I") {}

bool InventoryCommand::execute(Store *store) {
  store->displayInventory();
  return true;
}

bool InventoryCommand::setData(const string & /* line */) {
  return true; // Inventory command has no additional data
}

Command *InventoryCommand::create() const { return new InventoryCommand(); }

// HistoryCommand
HistoryCommand::HistoryCommand() : Command("H"), customerId(0) {}

bool HistoryCommand::execute(Store *store) {
  cout << "Debug: History for " << customerId << " ";
  return store->displayCustomerHistory(customerId);
}

bool HistoryCommand::setData(const string &line) {
  stringstream ss(line);
  string token;
  ss >> token >> customerId;
  return true;
}

Command *HistoryCommand::create() const { return new HistoryCommand(); }

// BorrowCommand
BorrowCommand::BorrowCommand()
    : Command("B"), customerId(0), mediaType('D'), movieType('F') {}

bool BorrowCommand::execute(Store *store) {
  if (mediaType != 'D') {
    cout << "Invalid media type " << mediaType << ", discarding line: " << endl;
    return false;
  }

  return store->borrowMovie(customerId, movieType, searchCriteria);
}

bool BorrowCommand::setData(const string &line) {
  stringstream ss(line);
  string token;

  ss >> token >> customerId >> mediaType >> movieType;

  getline(ss, searchCriteria);
  searchCriteria.erase(0, searchCriteria.find_first_not_of(" "));

  return true;
}

Command *BorrowCommand::create() const { return new BorrowCommand(); }

// ReturnCommand
ReturnCommand::ReturnCommand()
    : Command("R"), customerId(0), mediaType('D'), movieType('F') {}

bool ReturnCommand::execute(Store *store) {
  if (mediaType != 'D') {
    cout << "Invalid media type " << mediaType << ", discarding line: " << endl;
    return false;
  }

  return store->returnMovie(customerId, movieType, searchCriteria);
}

bool ReturnCommand::setData(const string &line) {
  stringstream ss(line);
  string token;

  ss >> token >> customerId >> mediaType >> movieType;

  getline(ss, searchCriteria);
  searchCriteria.erase(0, searchCriteria.find_first_not_of(" "));

  return true;
}

Command *ReturnCommand::create() const { return new ReturnCommand(); }