#ifndef BOOKCOPY_H
#define BOOKCOPY_H
#include "book.h"
using namespace std;

class bookcopy : public book
{
private:
	int ID;

	string Reader_Name;

	string Reserver_Name;

	book bookptr;		//reference to book 

	int Reserve_Date;

	int Start_Date;

	int Expiration_Date;

	int times_borrowed;
public:
	bookcopy();

	bookcopy(int id, string red, string res, book b, int rd, int sd, int ed, int tb);

	int getID();

	string getReader_Name();

	string getReserver_Name();

	book getBook();		//get book referenced by copy

	int getReserve_Date();

	int getStart_Date();

	int getExpiration_Date();

	int getTimes_Borrowed();

	void setID(int id);

	void setReader_Name(string red);

	void setReserver_Name(string res);

	void setBook(book b);		//assign book to copy

	void setReserve_Date(int rd);

	void setStart_Date(int sd);

	void setExpiration_Date(int ed);

	void incTimesBorrowed();

	void setTimesBorrowed(int n);

	friend ostream& operator << (ostream& output, const bookcopy& copy);

	friend istream& operator >> (istream& input, bookcopy& copy);

	void operator = (bookcopy rhs);

	//return 1 if copies are of same ID, 0 otherwise
	bool operator == (bookcopy rhs) const;

	//return 0 if copies are of same ID, 1 otherwise
	bool operator != (bookcopy rhs) const;

	bool operator > (const bookcopy& rhs) const;

	bool operator < (const bookcopy& rhs) const;
};
#endif