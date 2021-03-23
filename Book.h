#pragma once
#include <string>
#include <iostream>

using namespace std;

class Book
{
private:
	int id;
	string name;
	string author;
	bool available;

public:

	Book(){
		id = 0;
		name = "";
		author = "";
		available = false;
	}

	Book(int Id,string Name, string Author, bool Available)
	{
		id = Id,
		name = Name;
		author = Author;
		available = Available;
	}

	bool getAvailable();

	void setAvailable(bool Available);

	string getBook();
	
	string getName();

	string getAuthor();

	int getId();
};

