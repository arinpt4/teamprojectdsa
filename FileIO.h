/*
Specification file for the File I/O class
Name: Thomas Lwin
*/

#ifndef FILEIO_H
#define FILEIO_H

#include <string>

#include "Song.h"
// #include HashTable.h
// #include BinarySearchTree.h

static const std::string saveFile = "saveData.txt";

bool allocateHash();

void readSongData(std::string inputFileName);
void saveSongData();
void reHashData(HashTable<Song> &hash, int lineCount);

// prime checks for hash table resizing
int nextPrime(int n);
bool isPrime(int n);