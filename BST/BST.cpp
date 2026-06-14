// Title: Unit 2 - BST Algorithms Implementation
/*
    Unit 2: Binary Search Tree Algorithms (Your Design - Huey)
    Implementation file: Contains the actual code logic for the BST.
*/

#include "BST.h"
#include <iostream>
#include <algorithm>

// Constructor
BST::BST() : root(nullptr) {}

// Destructor
BST::~BST() { 
    destroyTree(root); 
}

// ---------------------------------------------------------
// Private Helper Methods
// ---------------------------------------------------------

bool BST::caseInsensitiveLess(const std::string& a, const std::string& b) const {
    std::string lowerA = a, lowerB = b;
    std::transform(lowerA.begin(), lowerA.end(), lowerA.begin(), ::tolower);
    std::transform(lowerB.begin(), lowerB.end(), lowerB.begin(), ::tolower);
    return lowerA < lowerB;
}

bool BST::caseInsensitiveEqual(const std::string& a, const std::string& b) const {
    std::string lowerA = a, lowerB = b;
    std::transform(lowerA.begin(), lowerA.end(), lowerA.begin(), ::tolower);
    std::transform(lowerB.begin(), lowerB.end(), lowerB.begin(), ::tolower);
    return lowerA == lowerB;
}

void BST::insertNode(TreeNode*& node, const std::string& id, Song* ptr) {
    if (!node) {
        node = new TreeNode(id, ptr);
        return;
    }
    // Compare using case-insensitive logic
    if (caseInsensitiveLess(id, node->song_id)) {
        insertNode(node->left, id, ptr);
    } else if (caseInsensitiveLess(node->song_id, id)) {
        insertNode(node->right, id, ptr);
    }
}

TreeNode* BST::findMin(TreeNode* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void BST::deleteNode(TreeNode*& node, const std::string& id) {
    if (!node) return;

    if (caseInsensitiveLess(id, node->song_id)) {
        deleteNode(node->left, id);
    } else if (caseInsensitiveLess(node->song_id, id)) {
        deleteNode(node->right, id);
    } else {
        // Node found! Handle deletion cases
        if (!node->left) {
            TreeNode* temp = node->right;
            delete node;
            node = temp;
        } else if (!node->right) {
            TreeNode* temp = node->left;
            delete node;
            node = temp;
        } else {
            // Two children: Get inorder successor (smallest in right subtree)
            TreeNode* temp = findMin(node->right);
            node->song_id = temp->song_id;
            node->song_ptr = temp->song_ptr;
            deleteNode(node->right, temp->song_id);
        }
    }
}

void BST::printInOrder(TreeNode* node) const {
    if (node) {
        printInOrder(node->left);
        std::cout << "- " << node->song_id << " : " << node->song_ptr->getSong_Name() 
                  << " by " << node->song_ptr->getArtist_Name() << "\n";
        printInOrder(node->right);
    }
}

void BST::printIndented(TreeNode* node, int level) const {
    if (node) {
        printIndented(node->right, level + 1);
        for (int i = 0; i < level; i++) {
            std::cout << "        ";
        }
        std::cout << node->song_id << "\n";
        printIndented(node->left, level + 1);
    }
}

void BST::destroyTree(TreeNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// ---------------------------------------------------------
// Public Methods (Called by SystemManagers and main.cpp)
// ---------------------------------------------------------

void BST::insert(const std::string& id, Song* ptr) {
    insertNode(root, id, ptr);
}

void BST::remove(const std::string& id) {
    deleteNode(root, id);
}

void BST::displaySorted() const {
    if (!root) {
        std::cout << "Tree is empty.\n";
    } else {
        printInOrder(root);
    }
}

void BST::displayTreeShape() const {
    if (!root) {
        std::cout << "Tree is empty.\n";
    } else {
        printIndented(root, 0);
    }
}