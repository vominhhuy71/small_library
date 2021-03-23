#include <iostream>
#include "Book.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void writeDb(vector<Book>& books) {
	ofstream myfile("./books.txt");
	if (myfile.is_open())
	{
		for (size_t i = 0; i < books.size(); i++)
		{
			string Available = (books[i].getAvailable() ? "true" : "false");
			string line = "(" + to_string(books[i].getId()) + ",\"" + books[i].getName() + "\",\"" + books[i].getAuthor() + "\"," + Available + ")";
			myfile << line << endl;
		}
		myfile.close();
	}
}

Book parse_line(string line) {
	enum parse_state_t {
		PARSE_IDLE,
		PARSE_ID,
		PARSE_NAME,
		PARSE_NAME_CONTENT,
		PARSE_AUTHOR,
		PARSE_AUTHOR_CONTENT,
		PARSE_AVAILABLE,
		PARSE_END
	};
	string id = "";
	string name = "";
	string author = "";
	parse_state_t state = PARSE_IDLE;
	string available = "";
	for (size_t i = 0; i < line.length(); i++)
	{
		switch (state) {
		case PARSE_IDLE:
			if (line[i] == '(') {
				state = PARSE_ID;
			}
			break;
		case PARSE_ID:
			if (line[i] == ',') {
				state = PARSE_NAME;
			}
			else
			{
				id += line[i];
			}
			break;
		case PARSE_NAME:
			if (line[i] == '\"') {
				state = PARSE_NAME_CONTENT;
			}
			break;
		case PARSE_NAME_CONTENT:
			if (line[i] == '\"') {
				state = PARSE_AUTHOR;
			}
			else {
				name += line[i];
			}
			break;
		case PARSE_AUTHOR:
			if (line[i] == '\"') {
				state = PARSE_AUTHOR_CONTENT;
			}
			break;
		case PARSE_AUTHOR_CONTENT:
			if (line[i] == '\"') {
				state = PARSE_AVAILABLE;
			}
			else {
				author += line[i];
			}
			break;
		case PARSE_AVAILABLE:
			if (line[i] == ')') {
				state = PARSE_END;
			}
			else if (line[i] == ',') {

			}
			else {
				available += line[i];
			}
			break;
		case PARSE_END:
			break;
		default:
			break;
		}
		
	}
	bool Avaialbe = (available == "true" ? true : false);
	int Id = stoi(id);
	return Book(Id ,name, author, Avaialbe);
}

void menu() {
	cout << "Actions:" << endl;
	cout << "1. List all" << endl;
	cout << "2. Borrow a book" << endl;
	cout << "3. Return a book" << endl;
	cout << "4. Quit" << endl;
	cout << "Your action: ";
}

void listAll(vector<Book> & books) {
	for (size_t i = 0; i < books.size(); i++)
	{
		cout << books[i].getBook() << endl;
	}
}

void borrowBook(vector<Book>& books){
	int id;
	cout << "Enter the id of the book: " ;
	cin >> id;
	Book book;
	int pos = string::npos;
	for (size_t i = 0; i < books.size(); i++)
	{
		if (books[i].getId() == id) {
			book = books[i];
			pos = i;
		}
	}
	if (!book.getAvailable()) {
		cout << "Book is not available right now!" << endl;
	}
	else {
		book.setAvailable(false);
		books[pos] = book;
		cout << "Successfully borrowed!" << endl;
		writeDb(books);
	}
	
}

void returnBook(vector<Book>& books){
	int id;
	cout << "Enter the id of the book: ";
	cin >> id;
	Book book;
	int pos = string::npos;
	for (size_t i = 0; i < books.size(); i++)
	{
		if (books[i].getId() == id) {
			book = books[i];
			pos = i;
		}
	}
	if (pos == string::npos) {
		cout << "Invalid Id!" << endl;
		return;
	}
	if (book.getAvailable()) {
		cout << "The book is already here!" << endl;
	}
	else {
		book.setAvailable(true);
		books[pos] = book;
		cout << "Successfully returned!" << endl;
		writeDb(books);
	}
}

void execute(int choice, vector<Book>& books) {
	switch (choice) {
	case 1:
		listAll(books);
		break;
	case 2:
		borrowBook(books);
		break;
	case 3:
		returnBook(books);
		break;
	}
}

vector<Book> loadDb() {
	ifstream db("./books.txt");
	string line;
	vector<Book> books;
	if (db.is_open()) {
		while (getline(db, line))
		{
			//cout << line << endl;
			Book book = parse_line(line);
			books.emplace_back(book);
		}
	}
	return books;
}

int main(int argc, char* argv[]) {
	vector<Book> books;
	int choice = 0;
	while (true) {
		books = loadDb();
		menu();
		cin >> choice;
		if (choice == 4) break;
		execute(choice, books);
	}

	return 0;
}