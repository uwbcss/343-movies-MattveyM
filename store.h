#ifndef STORE_H
#define STORE_H

#include "customer.h"
#include "hashtable.h"
#include "movie.h"
#include <set>
#include <vector>
using namespace std;

struct MovieCompare {
  bool operator()(const Movie *a, const Movie *b) const {
    if (a->getType() != b->getType()) {
      return a->getType() < b->getType();
    }
    return *a < *b;
  }
};

class Store {
public:
  Store();
  ~Store();

  bool loadMovies(const string &filename);
  bool loadCustomers(const string &filename);
  bool processCommands(const string &filename);

  void displayInventory() const;
  bool displayCustomerHistory(int customerId);
  bool borrowMovie(int customerId, char movieType, const string &criteria);
  bool returnMovie(int customerId, char movieType, const string &criteria);

private:
  set<Movie *, MovieCompare> movies;
  HashTable<int, Customer *> customers;

  static void registerFactories();
  Movie *findMovie(char type, const string &criteria);
  Customer *findCustomer(int id);
};

#endif