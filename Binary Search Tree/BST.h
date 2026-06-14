// Title: Unit 2 - BST Algorithms Header
/*
    Unit 2: Binary Search Tree Algorithms (Your Design - Huey)
    Header file: Contains the structure and function declarations.
*/

#pragma once
#include "Song.h"
#include <string>

// Option 3 Node Structure: Key + Pointer to Hash Table data
struct TreeNode {
    std::string song_id;
    Song* song_ptr;
    TreeNode* left;
    TreeNode* right;

    // Node constructor
    TreeNode(std::string id, Song* ptr) : song_id(id), song_ptr(ptr), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    // Helper functions (hidden from the rest of the program)
    bool caseInsensitiveLess(const std::string& a, const std::string& b) const;
    bool caseInsensitiveEqual(const std::string& a, const std::string& b) const;
    
    void insertNode(TreeNode*& node, const std::string& id, Song* ptr);
    TreeNode* findMin(TreeNode* node);
    void deleteNode(TreeNode*& node, const std::string& id);
    
    void printInOrder(TreeNode* node) const;
    void printIndented(TreeNode* node, int level) const;
    void destroyTree(TreeNode* node);

public:
    // Constructor and Destructor
    BST();
    ~BST();

    // Public interface for the rest of the program to use
    void insert(const std::string& id, Song* ptr);
    void remove(const std::string& id);
    void displaySorted() const;
    void displayTreeShape() const;
};