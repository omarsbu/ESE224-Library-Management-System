#include "teacher.h"

teacher::teacher()
{
	setUserName("None");
	changePassword("None");
	setmax_Copies(10);
	setmax_Borrow_Period(50);
}
teacher::teacher(string u, string p, vector<bookcopy> cb, list<bookcopy> cr)
{
	setmax_Copies(10);
	setmax_Borrow_Period(50);
	setUserName(u);
	changePassword(p);
	setcopies_borrowed(cb);
	setcopies_reserved(cr);
}

ostream& operator << (ostream& output, teacher& t)
{
	cout << "\nReader Type: Teacher" << endl;
	cout << "Username: " << t.getUserName() << endl;
	cout << "Password: " << t.getPassword() << endl;
	cout << "Copies Borrowed:\n";
	
	vector<bookcopy> temp = t.getcopies_borrowed();

	for (int i = 0; i < t.getmax_Copies(); i++)
	{

		if (temp[i].getTitle() != "None")
		cout << temp[i];
	}

	return cout;
}

