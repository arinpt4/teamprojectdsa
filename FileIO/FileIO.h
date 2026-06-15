/*
Specification file for the File I/O class
Name: Thomas Lwin
*/

#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include "../Song.h"
#include "../Hash/HashTable.h"
#include "../BST/BST.h"

static const std::string saveFile = "saveData.txt";

bool allocateHash(HashTable<Song>*& hash, BST &bst, std::string inputFileName);
int countLines(std::string fileName);

void readSongData(HashTable<Song>*& hash, BST &bst, std::string inputFileName);
bool loadFromFile(HashTable<Song>*& hash, BST &bst, std::string fileName);
void saveSongData(HashTable<Song>& hash);
void reHashData(HashTable<Song>*& hash, BST &bst, int lineCount);

// prime checks for hash table resizing
int nextPrime(int n);
bool isPrime(int n);

#endif
