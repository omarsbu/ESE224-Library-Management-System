#include "bookcopy.h"
using namespace std;

bookcopy::bookcopy()
{
	ID = 0;
	Reader_Name = "None";
	Reserver_Name = "None";
	bookptr = book::book();
	Reserve_Date = 0;
	Start_Date = 0;
	Expiration_Date = 0;
	times_borrowed = 0;
}
bookcopy::bookcopy(int id, string red, string res, book b, int rd, int sd, int ed, int tb)
{
	ID = id;
	Reader_Name = red;
	Reserver_Name = res;
	Reserve_Date = rd;
	bookptr = b;
	Start_Date = sd;
	Expiration_Date = ed;
	times_borrowed = tb;
}
int bookcopy::getID()
{
	return ID;
}
string bookcopy::getReader_Name()
{
	return Reader_Name;
}
string bookcopy::getReserver_Name()
{
	return Reserver_Name;
}
book bookcopy::getBook()
{
	return (bookptr);
}
int bookcopy::getReserve_Date()
{
	return Reserve_Date;
}
int bookcopy::getStart_Date()
{
	return Start_Date;
}
int bookcopy::getExpiration_Date()
{
	return Expiration_Date;
}
int bookcopy::getTimes_Borrowed()
{
	return times_borrowed;
}
void bookcopy::setID(int id)
{
	ID = id;
}
void bookcopy::setReader_Name(string red)
{
	Reader_Name = red;
}
void bookcopy::setReserver_Name(string res)
{
	Reserver_Name = res;
}
void bookcopy::setBook(book b)
{
	bookptr = b;
}
void bookcopy::setReserve_Date(int rd)
{
	Reserve_Date = rd;
}
void bookcopy::setStart_Date(int start_date)
{
	Start_Date = start_date;
}
void bookcopy::setExpiration_Date(int expiration_date)
{
	Expiration_Date = expiration_date;
}
void bookcopy::incTimesBorrowed()
{
	times_borrowed++;
}
void bookcopy::setTimesBorrowed(int n)
{
	times_borrowed = n;
}

ostream& operator << (ostream& ouput, const bookcopy& copy)
{
	cout << copy.bookptr;
	cout << "ID: " << copy.ID << endl;
	cout << "Reader Name: " << copy.Reader_Name << endl;
	cout << "Reserver Name: " << copy.Reserver_Name << endl;
	cout << "Reserve Date: " << copy.Reserver_Name << endl;
	cout << "Start Date: " << copy.Start_Date << endl;
	cout << "Expiration Date: " << copy.Expiration_Date << endl;
	cout << "Borrowed: " << copy.times_borrowed << " times" << endl;

	return cout;
}
istream& operator >> (istream& input, bookcopy& copy)
{
	cin >> (copy.bookptr) >> copy.ID >> copy.Reader_Name >> copy.Reserver_Name >> copy.Reserve_Date
		>> copy.Start_Date >> copy.Expiration_Date;

	return cin;
}
void bookcopy::operator = (bookcopy rhs)
{
	bookptr = rhs.bookptr;
	ID = rhs.ID;
	Reader_Name = rhs.Reader_Name;
	Reserver_Name = rhs.Reserver_Name;
	Reserve_Date = rhs.Reserve_Date;
	Start_Date = rhs.Start_Date;
	Expiration_Date = rhs.Expiration_Date;
	times_borrowed = rhs.times_borrowed;
}
bool bookcopy::operator == (bookcopy rhs) const
{
	return (ID == rhs.ID);
}
bool bookcopy::operator != (bookcopy rhs) const
{
	return (ID != rhs.ID);
}
bool bookcopy::operator > (const bookcopy& rhs) const
{
	if (ID > rhs.ID)
		return true;
	else
		return false;
}
bool bookcopy::operator < (const bookcopy& rhs) const
{
	if (ID < rhs.ID)
		return true;
	else
		return false;
}