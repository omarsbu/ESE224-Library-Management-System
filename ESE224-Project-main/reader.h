#pragma once
#include <list>
#include <vector>
#include <string>
#include "user.h"
#include "bookcopy.h"
#include "binarytree.h"
using namespace std;

class reader : public user
{
private:

	int num_penalties;

	list<bookcopy> copies_reserved;

	vector<bookcopy> copies_borrowed;		//pointer to base of array, might change to list

protected:

	int max_copies;

	int max_borrow_period;

public:
	reader();

	reader(string u, string p, int mc, int mbp, int penalties, vector<bookcopy> cb, list<bookcopy> cr);

	virtual int getmax_Copies();

	virtual int getmax_Borrow_Period();

	virtual string getuser_type();

	vector<bookcopy> getcopies_borrowed();		//might change return type to bookcopy

	list<bookcopy> getcopies_reserved();		//might change return type to bookcopy 

	bookcopy getcopy_borrowed();

	bookcopy getcopy_reserved();

	void setmax_Copies(int mc);

	void setmax_Borrow_Period(int mbp);

	void setcopies_borrowed(vector<bookcopy> cb);

	void setcopies_reserved(list<bookcopy> cr);

	void setcopy_borrowed(bookcopy cp);

	void setcopy_reserved(bookcopy cr);

	virtual void SearchBook(BinaryTree<bookcopy> library, BinaryTree<book> catelog, char method);

//	virtual bookcopy bSearchID(BinaryTree<bookcopy> library, int value);

	int sortBookCopies(bookcopy a, bookcopy b);

	virtual void BorrowBook(BinaryTree<bookcopy> library, BinaryTree<book> catelog, int id, clock_t time, user u);

	virtual void ReturnBook(BinaryTree<bookcopy> library, BinaryTree<book> catelog, int id, clock_t time);

	virtual void RenewBook(BinaryTree<bookcopy> library, clock_t time);

	virtual void ReserveBook(BinaryTree<bookcopy> library, BinaryTree<book> catelog, long long int isbn, clock_t time, user u);

	virtual void CancelReservation(bookcopy b, clock_t time);

//	virtual void feelingLucky(BinaryTree<bookcopy> library, BinaryTree<book> catelog);

	friend ostream& operator << (ostream& output, reader reader);

	friend istream& operator >> (istream& input, reader& reader);

	void operator = (reader rhs);

};