#include "../includes_usr/fileIO.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{
	books.clear();

	ifstream myfile;
	myfile.open(filename);
	string line;

	if(!myfile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	while(getline(myfile,line)){
		istringstream lineStream(line);
		string space;
		vector<string> tempVector;
		book tempBook;

		while (getline(lineStream, space,',')){
			tempVector.push_back(space);
		}

		tempBook.book_id= stoi(tempVector[0]);
		tempBook.title=tempVector[1];
		tempBook.author = tempVector[2];
		tempBook.state = (book_checkout_state) stoi(tempVector[3]);
		tempBook.loaned_to_patron_id = stoi(tempVector[4]);
		books.push_back(tempBook);
	}

	if (books.empty()){
		myfile.close();
		return NO_BOOKS_IN_LIBRARY;
	}

	myfile.close();
	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	ofstream myfile;
	myfile.open(filename);

	if (!myfile.is_open()){
		 return COULD_NOT_OPEN_FILE;
	}
	if(books.size() == 0){
		myfile.close();
		return NO_BOOKS_IN_LIBRARY;
	}
	std::vector<book>::iterator it;
	for (it = books.begin(); it != books.end(); it++){
		 myfile << (*it).book_id <<"," << (*it).title << "," << (*it).author << "," << (*it).state << "," << (*it).loaned_to_patron_id;
		 myfile << endl;
	}
	myfile.close();
	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	patrons.clear();

	ifstream myfile;
	myfile.open(filename);

	if(!myfile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	string line;


	while(getline(myfile,line)){
		istringstream lineStream(line);
		string space;
		vector<string> tempVector;
		patron tempPatron;

		while (getline(lineStream, space,',')){
			tempVector.push_back(space);
		}

		tempPatron.patron_id= stoi(tempVector[0]);
		tempPatron.name = tempVector[1];
		tempPatron.number_books_checked_out = stoi(tempVector[2]);
		patrons.push_back(tempPatron);
	}

	if (patrons.empty()){
		myfile.close();
		return NO_PATRONS_IN_LIBRARY;
	}


	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	ofstream myfile;
	myfile.open(filename);

	if (!myfile.is_open()){
		 return COULD_NOT_OPEN_FILE;
	}
	if(patrons.size() == 0){
		myfile.close();
		return NO_BOOKS_IN_LIBRARY;
	}

	std::vector<patron>::iterator it;
	for (it = patrons.begin(); it != patrons.end(); it++){
		 myfile << (*it).patron_id << "," << (*it).name << "," << (*it).number_books_checked_out ;
		 myfile << endl;

	}
	myfile.close();
	return SUCCESS;
}

