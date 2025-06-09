#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <list>
#include <vector>
using namespace std;

template <typename K, typename V> class HashTable {
private:
  struct Entry {
    K key;
    V value;
    Entry(const K &k, const V &v) : key(k), value(v) {}
  };

  vector<list<Entry>> table;
  int capacity;
  int size;

  int hash(const K &key) const { return key % capacity; }

public:
  explicit HashTable(int cap = 101) : capacity(cap), size(0) {
    table.resize(capacity);
  }

  void insert(const K &key, const V &value) {
    int index = hash(key);

    // Check if key already exists
    for (auto &entry : table[index]) {
      if (entry.key == key) {
        entry.value = value;
        return;
      }
    }

    // Add new entry
    table[index].emplace_back(key, value);
    size++;
  }

  V *find(const K &key) {
    int index = hash(key);
    for (auto &entry : table[index]) {
      if (entry.key == key) {
        return &entry.value;
      }
    }
    return nullptr;
  }

  bool contains(const K &key) const { return find(key) != nullptr; }

  int getSize() const { return size; }
};

#endif
