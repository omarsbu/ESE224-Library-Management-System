#pragma once
#include <string>
using namespace std;

class user
{
private:
	string UserName;

	string Password;

public:
	user();

	user(string u, string p);

	virtual string getUserName();

	virtual string getPassword();

	virtual void setUserName(string u);

	virtual void myInformation();

	virtual void changePassword(string p);

//	 friend ostream& operator << (ostream& output, const user& user);

//	 friend istream& operator >> (istream& input, user& user);

	virtual bool operator == (const user& rhs);

	virtual bool operator != (const user& rhs);

	void operator = (user rhs);

	bool operator > (user rhs);

	bool operator < (user rhs);
};