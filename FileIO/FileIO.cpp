#include "FileIO.h"

#include <fstream>
#include <iostream>
#include <sstream>

bool allocateHash(HashTable<Song>*& hash, BinarySearchTree<std::string> &bst, std::string inputFileName) {

	int lineCount = 0;

	lineCount += countLines(saveFile);
	lineCount += countLines(inputFileName);
	
	if (lineCount > 0) {
		// if no existing hash table, create one. otherwise rehash if needed.
		if (!hash) {
			hash = new HashTable<Song>(nextPrime(lineCount * 2));
		} else {
			if (100.0 * (lineCount + hash->getCount()) / hash->getSize() > 75.0)
				reHashData(hash, bst, lineCount);
		}
		return true;
	}
	return false;
}

int countLines(std::string fileName) {
	std::ifstream ifs(fileName);
	std::string line;
	int lineCount = 0;

	if (ifs.is_open()) {
		while (getline(ifs, line)) {
			if (!line.empty())
				++lineCount;
		}
		ifs.close();
	}
	return lineCount;
}

void readSongData(HashTable<Song>*& hash, BinarySearchTree<std::string> &bst, std::string inputFileName) {
	if (!allocateHash(hash, bst, inputFileName)) {
		std::cout << "No Data!" << "\n";
		return;
	}
	loadFromFile(hash, bst, inputFileName);
	loadFromFile(hash, bst, saveFile);
}

// need to fix - when rehashing, inserts to bst again, so creates duplicates. unless bst checks for duplicates.
bool loadFromFile(HashTable<Song>*& hash, BinarySearchTree<std::string> &bst, std::string fileName) {	
	std::ifstream ifs(fileName);

	if (!ifs.is_open())
		return false;

	// example string format: "NwoUe; just forget; Force of Nature; 3:55; 2004"
	std::string line;
	while (getline(ifs, line)) {
		if (line.empty())
			continue;

		std::string song_id, song_name, artist_name, length;
		int date_published = 0;

		std::stringstream temp(line);

		std::getline(temp, song_id, ';');
		temp >> std::ws;

		if (song_id.length() != 5) continue;
		if (std::getline(temp, song_name, ';')) temp >> std::ws;
		if (std::getline(temp, artist_name, ';')) temp >> std::ws;
		if (std::getline(temp, length, ';')) temp >> std::ws; 
		if (!(temp >> date_published)) date_published = 0;

		Song inputSong(song_id, song_name, artist_name, length, date_published);
		hash->insert(inputSong, key_to_index);
		bst.insert(inputSong.getID());
	}
	ifs.close();
	return true;
}

void saveSongData(HashTable<Song>*& hash) {
	std::ofstream ofs(saveFile);
	if (!ofs.is_open()) {
		std::cout << "Error opening save file: " << saveFile << "\n";
		return;
	}

	for (int i = 0; i < hash->getSize(); i++) {
		if (hash->getOccupied(i)) {
			ofs << hash->getItem(i) << "\n";
		}
	}
	ofs.close();
}

void reHashData(HashTable<Song>*& hash, BinarySearchTree<std::string>& bst, int lineCount) {
	saveSongData(hash);
	delete hash;
	hash = new HashTable<Song>(nextPrime(countLines(saveFile) * 2));
	loadFromFile(hash, bst, saveFile);
}

int nextPrime(int num) {
	while (!isPrime(num))
		num++;
	return num;
}

bool isPrime(int num) {
	if (num < 4)
		return true; // 3 is prime and 1 is less than min hash size
	if (num % 2 == 0)
		return false; // even numbers
	for (int i = 3; i * i <= num; i += 2) {
		if (num % i == 0)
			return false;
	}
	return true;
}
