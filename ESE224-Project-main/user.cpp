#include "user.h"
#include <iostream>

user::user()
{
	UserName = "None";
	Password = "None";
}
user::user(string u, string p)
{
	UserName = u;
	Password = p;
}
string user::getUserName()
{
	return UserName;
}
string user::getPassword()
{
	return Password;
}
void user::setUserName(string u)
{
	UserName = u;
}
void user::myInformation()
{
	cout << "Username: " << UserName << endl
		<< "Password: " << Password << endl;
}
void user::changePassword(string p)
{
	Password = p;
}
void user::operator = (user rhs)
{
	UserName = rhs.UserName;
	Password = rhs.Password;
}
bool user::operator > (user rhs)
{
	int i = 0;
	while (UserName[i] == rhs.UserName[i] && i < UserName.length() && i < rhs.getUserName().length())
		i++;

	if (UserName[i] < rhs.UserName[i])
		return true;
	else
		return false;
}
bool user::operator < (user rhs)
{
	int i = 0;
	while (UserName[i] == rhs.UserName[i] && i < UserName.length() && i < rhs.getUserName().length())
		i++;

	if (UserName[i] > rhs.UserName[i])
		return true;
	else
		return false;
}
bool user::operator == (const user& rhs)
{
	if (UserName == rhs.UserName)// && Password == rhs.Password)
		return true;
	else
		return false;
}
bool user::operator != (const user& rhs)
{
	if (UserName != rhs.UserName)// && Password == rhs.Password)
		return true;
	else
		return false;
}