#include "FileIO.h"

#include <fstream>
#include <iostream>
#include <sstream>

bool allocateHash(std::string inputFileName) {
	std::ifstream ifs(saveFile);
	std::string line;
	int lineCount = 0;

	// if save file exists
	if (ifs.is_open()) {
		while (getline(ifs, line)) {
			if (!line.empty())
				++lineCount;
		}
		ifs.close();
	}
	
	ifs.clear();
	ifs.open(inputFileName);
	// if input file exists
	if (ifs.is_open()) {
		while (getline(ifs, line)) {
			if (!line.empty())
				++lineCount;
		}
		ifs.close();
	}
	
	if (lineCount > 0) {
		// if no existing hash table, create one. otherwise rehash if needed.
		if (!hash) {
			HashTable<Song> hash(nextPrime(lineCount * 2));
		} else {
			if (100.0 * (lineCount + hash.getCount()) / hash.getSize() > 0.75) {
				reHashData(hash, lineCount);
			}
		}
	}
	return false;
}

void readSongData(std::string inputFileName) {
	if (!allocateHash(inputFileName)) {
		std::cout << "No Data!" << "\n";
		return;
	}
	
	std::ifstream ifs(inputFileName);
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

		if (song_id.length() != 5) {
			// std::cout << "Invalid song ID: " << song_id << "\n";
			continue;
		}
		if (std::getline(temp, song_name, ';')) {
			temp >> std::ws;
		}
		if (std::getline(temp, artist_name, ';')) {
			temp >> std::ws;
		}
		if (std::getline(temp, length, ';')) {
			temp >> std::ws;
		}
		if (!(temp >> date_published)) {
			date_published = 0;
		}

		Song inputSong(song_id, song_name, artist_name, length, date_published);
		bst.insert(inputSong);
		hash.insert(inputSong);
	}

	ifs.close();
}

void saveSongData(HashTable<Song> &hash) {
	std::ofstream ofs(saveFile);
	if (!ofs.is_open()) {
		std::cout << "Error opening save file: " << saveFile << "\n";
		return;
	}

	for (int i = 0; i < hash.getSize(); i++) {
	
	}
	ofs.close();
}

void reHashData(HashTable<Song> &hash, int lineCount) {
	HashTable<Song> newHash(nextPrime((hash.getSize() + lineCount) * 2));
	for (int i = 0; i < hash.getSize(); i++) {
		if (!hash.isEmpty(i)) {
			for (const auto &song : hash.getBucket(i)) {
				newHash.insert(song);
			}
		}
	}
	hash = std::move(newHash);
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
