/*
    ScreenManager.cpp
    Implementation of the Unit 4 Screen Output functions.
    Name: Aarush Muralinathan
*/

#include <iostream>
#include <string>
#include <cctype> // Required for the toupper() function
#include "ScreenManager.h"
#include "../Song.h"
#include "../FileIO/FileIO.h"
#include "../Hash/HashTable.h"
using namespace std;

// SEARCH MANAGER

void searchManager(HashTable<Song>& table) {
    string searchKey;
    cout << "\nEnter the Song ID to search for: ";
    cin >> searchKey;

    // The Hash Table search requires a Song object, so we make a dummy one with the ID
    Song dummySong(searchKey, "", "", "", 0);
    Song foundSong; 
    
    // Call the Hash Table's search function
    int collisions = table.search(dummySong, key_to_index, foundSong);

    if (collisions != -1) {
        cout << "\nFound: " << foundSong.getSong_Name() << "; "
             << foundSong.getArtist_Name() << "; "
             << foundSong.getLength() << "; "
             << foundSong.getDate_Published() << "\n";
        cout << "(Collisions during search: " << collisions << ")\n";
    } else {
        cout << "\nSong ID not found.\n";
    }
}

// DISPLAY MANAGER

void displaySortedData(BST& bst) {
    cout << "\n--- All Songs Sorted by ID ---\n";
    // The BST's inOrder traversal prints the keys in alphabetical order
    bst.displaySorted(); 
    cout << "------------------------------\n";
}

void displayIndentedTree(BST& bst) {
    cout << "\n--- Indented Binary Search Tree ---\n";
    // This is the hidden 'T' option
    bst.displayTreeShape();
    cout << "-----------------------------------\n";
}


// DELETE MANAGER

void deleteManager(HashTable<Song>& table, BST& bst, Stack& undoStack) {
    string deleteKey;
    cout << "\nEnter the Song ID to delete: ";
    cin >> deleteKey;

    // Use a dummy song to search
    Song dummySong(deleteKey, "", "", "", 0);
    Song foundSong;

    // First, check if the song exists in the Hash Table
    if (table.search(dummySong, key_to_index, foundSong) != -1) {
        // 1. Push the song onto the undo stack before deleting
        undoStack.push(foundSong);

        // 2. Remove from Hash Table
        table.remove(foundSong, key_to_index);

        // 3. Remove from BST
        bst.remove(deleteKey);

        cout << "\nSuccessfully deleted: " << foundSong.getSong_Name() << "\n";
        cout << "(You can press 'U' to undo this deletion.)\n";
    } else {
        cout << "\nSong ID not found. Deletion failed.\n";
    }
}


// UNDO DELETE MANAGER

void undoDeleteManager(Stack& undoStack, HashTable<Song>& table, BST& bst) {
    // Check if the stack is empty (happens if no deletes occurred OR if saved to file)
    if (undoStack.isEmpty()) {
        cout << "\nCannot undo! The undo stack is empty.\n";
        cout << "(Note: After saving to file, undo-delete is not possible).\n";
        return;
    }

    // Pop ONLY the most recently deleted song off the stack
    Song restoredSong = undoStack.pop();

    // Re-insert the full song object into the Hash Table
    Song* restoredPtr = table.insert(restoredSong, key_to_index);

    // Re-insert just the string ID key into the Binary Search Tree
    if (restoredPtr != nullptr) {
        bst.insert(restoredSong.getID(), restoredPtr);
    }

    cout << "\nSuccessfully restored the most recently deleted song: " 
         << restoredSong.getSong_Name() << "\n";
}

// MAIN MENU LOOP

void runMenu(HashTable<Song>& table, BST& bst, Stack& undoStack) {
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
                table.printHashTable();
                break;
            case 'D':
                deleteManager(table, bst, undoStack);
                break;
            case 'U':
                undoDeleteManager(undoStack, table, bst);
                break;
            case 'F': {
                cout << "\nSaving data to file...\n";
                // Call the actual save function from FileIO
                saveSongData(table);
                // CRITICAL INSTRUCTION: Clean out the stack upon saving
                undoStack.clear();
                cout << "Data saved successfully.\n";
                cout << "*** The undo stack has been cleared. Undo is no longer possible. ***\n";
                break;
            }
            case 'Q':
                keepRunning = false;
                break;
            default:
                cout << "\nInvalid option. Please try again.\n";
        }
    }
}