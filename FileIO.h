/*
Specification file for the File I/O class
Name: Thomas Lwin
*/

#ifndef FILEIO_H
#define FILEIO_H

#include <functional>
#include <string>

#include "Song.h"
// #include HashTable.h
// #include BinarySearchTree.h

static const std::string saveFile = "saveData.txt";

bool allocateHash(HashTable<Song>*& hash, BinarySearchTree<std::string> &bst, std::string inputFileName);
int countLines(std::string fileName);

void readSongData(HashTable<Song>*& hash, BinarySearchTree<std::string> &bst, std::string inputFileName);
bool loadFromFile(HashTable<Song>*& hash, BinarySearchTree<std::string> &bst, std::string fileName);
void saveSongData(HashTable<Song>*& hash);
void reHashData(HashTable<Song>*& hash, BinarySearchTree<std::string>& bst, int lineCount);

// prime checks for hash table resizing
int nextPrime(int n);
bool isPrime(int n);