/*
    ScreenManager.h
    Unit 4: Screen Output - Handles user menus, searching, display, and undo operations.
*/

#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "HashTable.h"
#include "BinarySearchTree.h"
#include "Stack.h"

// ==========================================
// Function Prototypes
// ==========================================

// Prompts user for a key and searches the Hash Table
void searchManager(HashTable& table);

// Displays all songs sorted by ID using the BST
void displaySortedData(BinarySearchTree& bst);

// Displays the BST structure as an indented tree (Hidden Option)
void displayIndentedTree(BinarySearchTree& bst);

// Reverses the most recent delete operation
void undoDeleteManager(Stack& undoStack, HashTable& table, BinarySearchTree& bst);

// The main loop that runs the user interface
void runMenu(HashTable& table, BinarySearchTree& bst, Stack& undoStack);

#endif 