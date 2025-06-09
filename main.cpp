/**
 * Driver for starting movie store tests
 */

#include "store.h"
#include <iostream>

using namespace std;

// forward declaration, implementation in store_test.cpp
void testAll();

int main() {
  testAll();

  // Final test with actual data files
  cout << "=====================================" << endl;
  cout << "Start testStoreFinal" << endl;

  Store store;

  // Load data files
  if (!store.loadMovies("data4movies.txt")) {
    cerr << "Failed to load movies" << endl;
    return 1;
  }

  if (!store.loadCustomers("data4customers.txt")) {
    cerr << "Failed to load customers" << endl;
    return 1;
  }

  // Process commands
  if (!store.processCommands("data4commands.txt")) {
    cerr << "Failed to process commands" << endl;
    return 1;
  }

  cout << "End testStoreFinal" << endl;
  cout << "=====================================" << endl;
  cout << "Done!" << endl;

  return 0;
}