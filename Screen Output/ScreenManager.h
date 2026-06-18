/*
    ScreenManager.h
    Unit 4: Screen Output - Handles user menus, searching, display, and undo operations.
    Name: Aarush Muralinathan
*/

#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "../Hash/HashTable.h"
#include "../BST/BST.h"
#include "Stack.h" 
#include "../Song.h"


// Function Prototypes

// Asks user for songs details and inserts song into BST and Hash Table
void insertManager(HashTable<Song>& table, BST& bst);

// Prompts user for a key and searches the Hash Table
void searchManager(HashTable<Song>& table);

// Displays all songs sorted by ID using the BST
void displaySortedData(BST& bst);

// Displays the BST structure as an indented tree (Hidden Option)
void hiddenOptionsManager(BST& bst, HashTable<Song>& table);

// Prompts user for a key and deletes it from the system
void deleteManager(HashTable<Song>& table, BST& bst, Stack& undoStack);

// Prints statistics for hash table
void statsManager(HashTable<Song>& table); 

// Reverses the most recent delete operation
void undoDeleteManager(Stack& undoStack, HashTable<Song>& table, BST& bst);

// The main loop that runs the user interface
void runMenu(HashTable<Song>& table, BST& bst, Stack& undoStack);

#endif 
 