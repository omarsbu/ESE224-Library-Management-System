#include "student.h"

student::student()
{
	setUserName("None");
	changePassword("None");
	setmax_Copies(5);
	setmax_Borrow_Period(30);
}
student::student(string u, string p, vector<bookcopy> cb, list<bookcopy> cr)
{
	setmax_Copies(5);
	setmax_Borrow_Period(30);
	setUserName(u);
	changePassword(p);
	setcopies_borrowed(cb);
	setcopies_reserved(cr);
}
ostream& operator << (ostream& output, student& s)
{
	cout << "\nReader Type: Student" << endl;
	cout << "Username: " << s.getUserName() << endl;
	cout << "Password: " << s.getPassword() << endl;
	cout << "Copies Borrowed:\n";

	vector<bookcopy> temp = s.getcopies_borrowed();

	for (int i = 0; i < s.getmax_Copies(); i++)
	{

		if (temp[i].getTitle() != "None")
		cout << temp[i];
	}

	return cout;
}
