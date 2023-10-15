#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "user.h"

using namespace std;

class book
{
private:
	long long int ISBN;

	string Title;

	string Author;

	string Category;

	list<user> Reserver_List;

	int nbr_copies;		//number of copies the book has

	vector<int> copyIDs;		//pointer to base of array containing IDs of all copies of book

	int Favor;

public:
	book();

	book(long long int isbn, string title, string author, string category, vector<int> ids, list<user> res_list, int favor);

	long long int getISBN();

	string getTitle();

	string getAuthor();

	string getCategory();

	user getReserver();			//return user at end of list, might add additional argument like iterator to search for reservers

	list<user> getReserverList();

	int getnbrCopies();

	vector<int> getIDs();		//returns an array containing IDs of all copies

	int getFavor();

	void setISBN(long long int isbn);

	void setTitle(string title);

	void setAuthor(string author);

	void setCategory(string category);

	void setReserver(user r);		//insert user to already existing list

	void setnbrCopies(int num_copies);

	void setID(int id, int i);		//change ID of copy[i]

	void setFavor(int f);

	friend ostream& operator << (ostream& output, const book& book);

	friend istream& operator >> (istream& input, book& book);

	//return 1 if lhs book title comes before rhs book title alphabetically, 0 otherwise
	bool isGreator_Alphabetical(const book& lhs, const book& rhs);

	//return 1 if lhs book title comes after rhs book title alphabetically, 0 otherwise
	bool isLess_Alphabetical(const book& lhs, const book& rhs);

	//return 1 if same book , 0 otherwise
	bool isSame(const book& lhs, const book& rhs);

	friend ostream& operator << (ostream& output, const book& book);

	friend istream& operator >> (istream& input, book& book);

	void operator = (book rhs);

	//return 1 if same ISBN , 0 otherwise
	bool operator == (book rhs) const;

	//return 0 if same ISBN , 1 otherwise
	bool operator != (book rhs) const;

	//return 1 if lhs book ISBN is greater than rhs book ISBN, 0 otherwise
	bool operator > (book rhs) const;

	//return 1 if lhs book ISBN is less than rhs book ISBN, 0 otherwise
	bool operator < (book rhs) const;
};
#endif