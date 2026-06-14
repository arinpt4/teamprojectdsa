//just a temp for fileIO functions
#include "FileIO.h"

int main() {
	HashTable<Song>* hash = nullptr;
	BinarySearchTree<std::string> bst;
	std::string inputFileName = "inputFile.txt";
	readSongData(hash, bst, inputFileName);

	delete hash;
	return 0;
}