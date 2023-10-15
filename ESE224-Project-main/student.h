#pragma once
#include "reader.h"

using namespace std;

class student : public reader
{
public:
	student();

	student(string u, string p, vector<bookcopy> cb, list<bookcopy> cr);

    friend ostream& operator << (ostream& output, student& s);
};