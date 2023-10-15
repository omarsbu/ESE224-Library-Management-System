#pragma once
#include "reader.h"

using namespace std;

class teacher : public reader
{
public:
	teacher();

	teacher(string u, string p, vector<bookcopy> cb, list<bookcopy> cr);

	friend ostream& operator << (ostream& output, teacher& t);

	void request_new(bookcopy library[], int num_books);

	void delete_existing(bookcopy library[], int num_books);

};