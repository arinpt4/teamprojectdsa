/*
Unit 1: Team Coordination - main(), integration, and testing
Name: Arin Thakkar
*/

#include <iostream>
#include "FileIO/FileIO.h"
#include "Screen Output/ScreenManager.h"
#include "Screen Output/Stack.h"

int main() {
    HashTable<Song>* hash = nullptr;
    BST bst;
    Stack undoStack;
    std::string inputFileName = "inputFile.txt";
    
    // 1. Load Data
    std::cout << "Loading system data...\n";
    readSongData(hash, bst, inputFileName);

    // 2. Launch the Menu Loop (from ScreenManager)
    if (hash != nullptr) {
        runMenu(*hash, bst, undoStack);
    } else {
        std::cout << "Failed to initialize the system. Exiting.\n";
    }

    // 3. Clean up
    delete hash;
    return 0;
}