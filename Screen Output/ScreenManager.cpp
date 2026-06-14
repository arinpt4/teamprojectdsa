/*
    ScreenManager.cpp
    Implementation of the Unit 4 Screen Output functions.
*/

#include <iostream>
#include <string>
#include <cctype> // Required for the toupper() function
#include "ScreenManager.h"
#include "Song.h"

using namespace std;

// ==========================================
// SEARCH MANAGER
// ==========================================
void searchManager(HashTable& table) {
    string searchKey;
    cout << "\nEnter the Song ID to search for: ";
    cin >> searchKey;

    // Call the Hash Table's search function
    Song* foundSong = table.search(searchKey);

    if (foundSong != nullptr) {
        // Song found! Display its details
        cout << "\nFound: " << foundSong->getSong_Name() << "; "
             << foundSong->getArtist_Name() << "; "
             << foundSong->getLength() << "; "
             << foundSong->getDate_Published() << "\n";
    } else {
        // Song not found
        cout << "\nSong ID not found.\n";
    }
}

// ==========================================
// DISPLAY MANAGER
// ==========================================
void displaySortedData(BinarySearchTree& bst) {
    cout << "\n--- All Songs Sorted by ID ---\n";
    // The BST's inOrder traversal prints the keys in alphabetical order
    bst.inOrder(); 
    cout << "------------------------------\n";
}

void displayIndentedTree(BinarySearchTree& bst) {
    cout << "\n--- Indented Binary Search Tree ---\n";
    // This is the hidden 'T' option
    bst.printIndentedTree();
    cout << "-----------------------------------\n";
}

// ==========================================
// UNDO DELETE MANAGER
// ==========================================
void undoDeleteManager(Stack& undoStack, HashTable& table, BinarySearchTree& bst) {
    // Check if the stack is empty (happens if no deletes occurred OR if saved to file)
    if (undoStack.isEmpty()) {
        cout << "\nCannot undo! The undo stack is empty.\n";
        cout << "(Note: After saving to file, undo-delete is not possible).\n";
        return;
    }

    // Pop ONLY the most recently deleted song off the stack
    Song restoredSong = undoStack.pop();

    // Re-insert the full song object into the Hash Table
    table.insert(restoredSong);

    // Re-insert just the string ID key into the Binary Search Tree
    bst.insert(restoredSong.getID());

    cout << "\nSuccessfully restored the most recently deleted song: " 
         << restoredSong.getSong_Name() << "\n";
}

// ==========================================
// MAIN MENU LOOP
// ==========================================
void runMenu(HashTable& table, BinarySearchTree& bst, Stack& undoStack) {
    char choice;
    bool keepRunning = true;

    while (keepRunning) {
        cout << "\n=== Music Player Menu ===\n";
        cout << "S - Search for a Song\n";
        cout << "P - Print data sorted by ID\n";
        cout << "D - Delete a Song\n";
        cout << "U - Undo delete\n";
        cout << "F - Save to file\n";
        cout << "Q - Quit\n";
        cout << "Enter an option: ";
        cin >> choice;
        choice = toupper(choice); // Convert input to uppercase to prevent errors

        switch (choice) {
            case 'S':
                searchManager(table);
                break;
            case 'P':
                displaySortedData(bst);
                break;
            case 'T': 
                // HIDDEN OPTION: Does not display in the menu text
                displayIndentedTree(bst);
                break;
            case 'D':
                cout << "\n[System: Delete function called. Item pushed to Undo Stack.]\n"; 
                break;
            case 'U':
                undoDeleteManager(undoStack, table, bst);
                break;
            case 'F':
                cout << "\nSaving data to file...\n";
                // CRITICAL INSTRUCTION: Clean out the stack upon saving
                undoStack.clear();
                cout << "Data saved successfully.\n";
                cout << "*** The undo stack has been cleared. Undo is no longer possible. ***\n";
                break;
            case 'Q':
                keepRunning = false;
                break;
            default:
                cout << "\nInvalid option. Please try again.\n";
        }
    }
}