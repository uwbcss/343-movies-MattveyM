#ifndef COMMAND_H
#define COMMAND_H

#include <string>
using namespace std;

class Store;

class Command {
public:
  explicit Command(const string &type);
  virtual ~Command() = default;

  virtual bool execute(Store *store) = 0;
  virtual bool setData(const string &line) = 0;
  virtual Command *create() const = 0;

  string getType() const { return type; }

protected:
  string type;
};

class InventoryCommand : public Command {
public:
  InventoryCommand();
  bool execute(Store *store) override;
  bool setData(const string &line) override;
  Command *create() const override;
};

class HistoryCommand : public Command {
public:
  HistoryCommand();
  bool execute(Store *store) override;
  bool setData(const string &line) override;
  Command *create() const override;

private:
  int customerId;
};

class BorrowCommand : public Command {
public:
  BorrowCommand();
  bool execute(Store *store) override;
  bool setData(const string &line) override;
  Command *create() const override;

private:
  int customerId;
  char mediaType;
  char movieType;
  string searchCriteria;
};

class ReturnCommand : public Command {
public:
  ReturnCommand();
  bool execute(Store *store) override;
  bool setData(const string &line) override;
  Command *create() const override;

private:
  int customerId;
  char mediaType;
  char movieType;
  string searchCriteria;
};

#endif
