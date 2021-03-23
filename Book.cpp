#include "Book.h"

string Book::getBook() {
	string Available = (available ? "true" : "false");
	return "Id: "+to_string(id)+", Name: " + name + ", Author: " + author + ", Available: " + Available;
}

int Book::getId() {
	return id;
}

string Book::getName() {
	return name;
}

string Book::getAuthor() { 
	return author; 
}

bool Book::getAvailable() {
	return available;
}

void Book::setAvailable(bool Available) {
	available = Available;
}

