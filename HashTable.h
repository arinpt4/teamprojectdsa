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

public:
    HashTable(int s = 101) {
        size = s;
        count = 0;
        table = new HashNode<T>[size];
    }

    ~HashTable() {
        delete[] table;
    }

    bool insert(const T& item, int (*hashFunction)(const T&, int)) {
        if (count >= size) {
            return false;
        }

        int index = hashFunction(item, size);
        int startIndex = index;

        do {
            if (table[index].getOccupied() != 1) {
                table[index].setItem(item);
                count++;
                return true;
            }

            if (table[index].getItem() == item) {
                return false;
            }

            index = (index + 1) % size;

        } while (index != startIndex);

        return false;
    }

    int search(const T& item, int (*hashFunction)(const T&, int), T& foundItem) const {
        int index = hashFunction(item, size);
        int startIndex = index;
        int collisions = 0;

        do {
            if (table[index].getOccupied() == 0) {
                return -1;
            }

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

    bool remove(const T& item, int (*hashFunction)(const T&, int)) {
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

    double getLoadFactor() const {
        return 100.0 * count / size;
    }

    void printHashTable() const {
        std::cout << "\n--- Hash Table ---\n";

        for (int i = 0; i < size; i++) {
            std::cout << i << ": ";

            if (table[i].getOccupied() == 1) {
                std::cout << table[i].getItem();
            } else if (table[i].getOccupied() == -1) {
                std::cout << "Deleted";
            } else {
                std::cout << "Empty";
            }

            std::cout << "\n";
        }
    }
};

#endif
