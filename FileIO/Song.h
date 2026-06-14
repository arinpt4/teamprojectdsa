/*
Specification file for the Song class
Name: Thomas Lwin
*/

#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <string>

class Song {
public:
	// constructors
	Song();
	Song(std::string i, std::string n, std::string a, std::string l, int d);

	// setters
	void setID(std::string song_id) { _song_id = song_id; }
	void setSong_Name(std::string song_name) { _song_name = song_name; }
	void setArtist_Name(std::string artist_name) { _artist_name = artist_name; }
	void setLength(std::string length) { _length = length; }
	void setDate_Published(int date_published) { _date_published = date_published; }

	// getters
	std::string getID() const { return _song_id; }
	std::string getSong_Name() const { return _song_name; }
	std::string getArtist_Name() const { return _artist_name; }
	std::string getLength() const { return _length; }
	int getDate_Published() const { return _date_published; }

	// overloaded relational operators
	bool operator>(const Song &right) { return (_song_id > right._song_id); }
	bool operator<(const Song &right) { return (_song_id < right._song_id); }
	bool operator==(const Song &right) { return (_song_id == right._song_id); }

	friend std::ostream &operator<<(std::ostream &temp, const Song &tempSong);

	friend int key_to_index(const Song &song, int size);

private:
	std::string _song_id; // unique key
	std::string _song_name;
	std::string _artist_name;
	std::string _length;
	int _date_published;
};

int key_to_index(const Song &song, int size);

#endif
