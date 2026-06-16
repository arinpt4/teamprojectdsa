#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <cctype>
#include "HashNode.h"

template <class T>
class HashTable {
private:
HashNode<T>* table;
int size;
int count;

```
// Statistics
int totalCollisions;
int longestCollisionPath;
```

public:
// Constructor
HashTable(int s = 101) {
size = s;
count = 0;
totalCollisions = 0;
longestCollisionPath = 0;

```
    table = new HashNode<T>[size];
}

// Destructor
~HashTable() {
    delete[] table;
}

/*
 Insert using linear probing.
 Returns pointer to inserted item.
 Returns nullptr if duplicate or table full.
*/
T* insert(const T& item,
          int (*hashFunction)(const T&, int)) {

    if (count >= size) {
        return nullptr;
    }

    int index = hashFunction(item, size);
    int startIndex = index;
    int collisions = 0;

    do {
        // Empty slot or tombstone
        if (table[index].getOccupied() != 1) {

            table[index].setItem(item);

            count++;

            totalCollisions += collisions;

            if (collisions > longestCollisionPath) {
                longestCollisionPath = collisions;
            }

            return &(table[index].getItemRef());
        }

        // Duplicate key
        if (table[index].getItem() == item) {
            return nullptr;
        }

        collisions++;

        index = (index + 1) % size;

    } while (index != startIndex);

    return nullptr;
}

/*
 Search.
 Returns number of collisions.
 Returns -1 if not found.
*/
int search(const T& item,
           int (*hashFunction)(const T&, int),
           T& foundItem) const {

    int index = hashFunction(item, size);
    int startIndex = index;

    int collisions = 0;

    do {
        // Never occupied
        if (table[index].getOccupied() == 0) {
            return -1;
        }

        // Found
        if (table[index].getOccupied() == 1 &&
            table[index].getItem() == item) {

            foundItem = table[index].getItem();

            return collisions;
        }

        collisions++;

        index = (index + 1) % size;

    } while (index != startIndex);

    return -1;
}

/*
 Delete using tombstones.
*/
bool remove(const T& item,
            int (*hashFunction)(const T&, int)) {

    int index = hashFunction(item, size);
    int startIndex = index;

    do {
        if (table[index].getOccupied() == 0) {
            return false;
        }

        if (table[index].getOccupied() == 1 &&
            table[index].getItem() == item) {

            table[index].setOccupied(-1);

            count--;

            return true;
        }

        index = (index + 1) % size;

    } while (index != startIndex);

    return false;
}

// Getters
int getSize() const {
    return size;
}

int getCount() const {
    return count;
}

bool getOccupied(int index) const {

    if (index < 0 || index >= size) {
        return false;
    }

    return table[index].getOccupied() == 1;
}

T getItem(int index) const {
    return table[index].getItem();
}

// Statistics
double getLoadFactor() const {

    return (100.0 * count) / size;
}

int getTotalCollisions() const {

    return totalCollisions;
}

int getLongestCollisionPath() const {

    return longestCollisionPath;
}

void displayHashStats() const {

    std::cout << "\n--- Hash Table Statistics ---\n";

    std::cout << "Table Size: "
              << size << "\n";

    std::cout << "Records Stored: "
              << count << "\n";

    std::cout << "Load Factor: "
              << getLoadFactor()
              << "%\n";

    std::cout << "Total Collisions: "
              << totalCollisions
              << "\n";

    std::cout << "Longest Collision Path: "
              << longestCollisionPath
              << "\n";
}

/*
 Hidden option:
 Print entire hash table.
*/
void printHashTable() const {

    std::cout << "\n--- Hash Table ---\n";

    for (int i = 0; i < size; i++) {

        std::cout << i << ": ";

        if (table[i].getOccupied() == 1) {

            std::cout << table[i].getItem();

        }
        else if (table[i].getOccupied() == -1) {

            std::cout << "Deleted";

        }
        else {

            std::cout << "Empty";
        }

        std::cout << "\n";
    }
}
```

};

#endif
