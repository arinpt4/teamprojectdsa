// ---------------------------------------------------------
// Name: Huey 
// Class: CIS 22C
// Description: Implementation file for the Binary Search Tree
// containing the actual code logic and recursive algorithms 
// for Unit 2 (BST Algorithms).
// ---------------------------------------------------------

#include "BST.h"
#include <iostream>
#include <algorithm>

// Initializes an empty Binary Search Tree.
BST::BST() : root(nullptr) {}

// Safely destroys the tree to prevent memory leaks.
BST::~BST() { 
    destroyTree(root); 
}

// Compares two strings alphabetically ignoring case. Returns true if 'a' < 'b'.
bool BST::caseInsensitiveLess(const std::string& a, const std::string& b) const {
    std::string lowerA = a, lowerB = b;
    std::transform(lowerA.begin(), lowerA.end(), lowerA.begin(), ::tolower);
    std::transform(lowerB.begin(), lowerB.end(), lowerB.begin(), ::tolower);
    return lowerA < lowerB;
}

// Compares two strings alphabetically ignoring case. Returns true if 'a' == 'b'.
bool BST::caseInsensitiveEqual(const std::string& a, const std::string& b) const {
    std::string lowerA = a, lowerB = b;
    std::transform(lowerA.begin(), lowerA.end(), lowerA.begin(), ::tolower);
    std::transform(lowerB.begin(), lowerB.end(), lowerB.begin(), ::tolower);
    return lowerA == lowerB;
}

// Private recursive helper to insert a new node into the BST.
void BST::insertNode(TreeNode*& node, const std::string& id, Song* ptr) {
    if (!node) {
        node = new TreeNode(id, ptr);
        return;
    }
    if (caseInsensitiveLess(id, node->song_id)) {
        insertNode(node->left, id, ptr);
    } else if (caseInsensitiveLess(node->song_id, id)) {
        insertNode(node->right, id, ptr);
    }
}

// Private helper that finds the node with the minimum value (leftmost node) in a subtree.
TreeNode* BST::findMin(TreeNode* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Private recursive helper to safely remove a node from the BST.
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

// Private recursive helper to print the tree in alphabetical order.
void BST::printInOrder(TreeNode* node) const {
    if (node) {
        printInOrder(node->left);
        std::cout << "- " << node->song_id << " : " << node->song_ptr->getSong_Name() 
                  << " by " << node->song_ptr->getArtist_Name() << "\n";
        printInOrder(node->right);
    }
}

// Private recursive helper to print the tree structure visually.
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

// Private recursive helper to safely delete all nodes using Post-Order traversal.
void BST::destroyTree(TreeNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Public interface to insert a new song into the BST.
void BST::insert(const std::string& id, Song* ptr) {
    insertNode(root, id, ptr);
}

// Public interface to remove a song from the BST by ID.
void BST::remove(const std::string& id) {
    deleteNode(root, id);
}

// Public interface to print all songs alphabetically.
void BST::displaySorted() const {
    if (!root) {
        std::cout << "Tree is empty.\n";
    } else {
        printInOrder(root);
    }
}

// Public interface to print the internal shape of the tree.
void BST::displayTreeShape() const {
    if (!root) {
        std::cout << "Tree is empty.\n";
    } else {
        printIndented(root, 0);
    }
}

// Public interface to completely empty the current tree.
void BST::clear() {
    destroyTree(root);
    root = nullptr;
}