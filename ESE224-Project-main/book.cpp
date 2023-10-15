#include "book.h"
using namespace std;

book::book()
{
	ISBN = 0;
	Title = "None";
	Author = "None";
	Category = "None";
	nbr_copies = 0;
	copyIDs.resize(0);
	Reserver_List.resize(0);
	Favor = 0;
}
book::book(long long int isbn, string title, string author, string category, vector<int> ids, list<user> res_list, int favor)
{
	ISBN = isbn;
	Title = title;
	Author = author;
	Category = category;
	nbr_copies = ids.size();
	copyIDs = ids;
	Reserver_List = res_list;
	Favor = favor;
}
long long int book::getISBN()
{
	return ISBN;
}
string book::getTitle()
{
	return Title;
}
string book::getAuthor()
{
	return Author;
}
string book::getCategory()
{
	return Category;
}
int book::getnbrCopies()
{
	return nbr_copies;
}
vector<int> book::getIDs()
{
	return copyIDs;
}
user book::getReserver()
{
	list<user>::iterator iter = Reserver_List.end();
	--iter;

	return (*iter);
}
list<user> book::getReserverList()
{
	return Reserver_List;
}
int book::getFavor()
{
	return Favor;
}
void book::setISBN(long long int isbn)
{
	ISBN = isbn;
}
void book::setTitle(string title)
{
	Title = title;
}
void book::setAuthor(string author)
{
	Author = author;
}
void book::setCategory(string category)
{
	Category = category;
}
void book::setnbrCopies(int num_copies)
{
	nbr_copies = num_copies;
	copyIDs.resize(num_copies);
}
void book::setID(int id, int i)
{
	copyIDs[i] = id;
}
void book::setReserver(user r)
{
	Reserver_List.push_back(r);
}
void book::setFavor(int f)
{
	Favor = f;
}
ostream& operator << (ostream& ouput, const book& book)
{
	cout << "Title: " << book.Title << endl;
	cout << "Author: " << book.Author << endl;
	cout << "ISBN: " << book.ISBN << endl;
	cout << "Category: " << book.Category << endl;
	cout << "Favor: " << book.Favor << endl;

	return cout;
}
istream& operator >> (istream& input, book& book)
{
	int numcpys;
	cin >> book.ISBN >> book.Title >> book.Author >> book.Category
		>> numcpys;
	book.setnbrCopies(numcpys);

	for (int i = 0; i < book.nbr_copies; i++)
		cin >> book.copyIDs[i];

	return cin;
}
void book::operator = (book rhs)
{
	Title = rhs.Title;
	ISBN = rhs.ISBN;
	Author = rhs.Author;
	Category = rhs.Category;
	nbr_copies = rhs.nbr_copies;
	copyIDs.resize(nbr_copies);
	for (int i = 0; i < nbr_copies; i++)
		copyIDs[i] = rhs.copyIDs[i];
	Reserver_List = rhs.Reserver_List;
	Favor = rhs.Favor;
}
bool book::operator == (book rhs) const
{
	if (ISBN == rhs.ISBN)
		return true;
	else
		return false;
}
bool book::operator != (book rhs) const
{
	if (ISBN != rhs.ISBN)
		return true;
	else
		return false;
}
bool book::operator > (book rhs) const
{
	if (ISBN > rhs.ISBN)
		return true;
	else
		return false;
}
bool book::operator < (book rhs) const
{
	if (ISBN < rhs.ISBN)
		return true;
	else
		return false;
}
bool book::isGreator_Alphabetical(const book& lhs, const book& rhs)
{
	int i = 0;
	while (lhs.Title[i] == rhs.Title[i] && i < lhs.Title.length() && i < rhs.Title.length())
		i++;

	if (lhs.Title[i] < rhs.Title[i])
		return true;
	else
		return false;
}
bool book::isLess_Alphabetical(const book& lhs, const book& rhs)
{
	int i = 0;
	while (lhs.Title[i] == rhs.Title[i] && i < lhs.Title.length() && i < rhs.Title.length())
		i++;

	if (lhs.Title[i] > rhs.Title[i])
		return true;
	else
		return false;
}

bool book::isSame(const book& lhs, const book& rhs)
{
	if (lhs.Title == rhs.Title && lhs.ISBN == rhs.ISBN
		&& lhs.Author == rhs.Author && lhs.Category == rhs.Category)
		return true;
	else
		return false;
}