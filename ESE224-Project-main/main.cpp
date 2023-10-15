#include "book.h"
#include "bookcopy.h"
#include "student.h"
#include "teacher.h"
#include "librarian.h"
#include "binarytree.h"
#include <list>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Catelog of books in the library
BinaryTree<book> catelog;

// Copies in the library
BinaryTree<bookcopy> library;

// Users in the library data base
BinaryTree<user> users;

// Readers in the library data base, can determine if student or teacher by the reader's max copies and max borrow period
BinaryTree<reader> readers;

// Students in the library data base
BinaryTree<student> students;

// Teachers in the library data base
BinaryTree<teacher> teachers;

// Librarians in the library data base
BinaryTree<librarian> librarians;

// Usernames in the library database
list<string> usernames;

bool userAuthentication(user& User);

bool isStudent(user& User);

bool isTeacher(user& User);

bool isLibrarian(user& User);

void Studentmenu(student& S, clock_t time);

void Teachermenu(teacher& T, clock_t time);

void Librarianmenu(librarian& L, clock_t time);

bool searchUser(BinaryTree<user>::iterator iter, user& target);


int main()
{
	ifstream datain1, datain2, datain3;
	user temp;

	string username, password;

	int user_type = 0;

	datain1.open("student.txt");
	if (datain1.fail())
	{
		cerr << "Error: File \"student.txt\" cannot be opened.";
		exit(1);
	}

	datain2.open("book.txt");
	if (datain2.fail())
	{
		cerr << "Error: File \"book.txt\" cannot be opened.";
		exit(1);
	}

	datain3.open("copy.txt");
	if (datain2.fail())
	{
		cerr << "Error: File \"copy.txt\" cannot be opened.";
		exit(1);
	}

	// Read information from student.txt
	while (datain1 >> user_type >> username >> password)
	{
		if (user_type == 0)
		{
			student* new_Student = new student;
			new_Student->setUserName(username);
			new_Student->changePassword(password);

			// store in user trees
			users.insert(*new_Student);
			readers.insert(*new_Student);
			students.insert(*new_Student);
		}
		else if (user_type == 1)
		{
			teacher* new_Teacher = new teacher;
			new_Teacher->setUserName(username);
			new_Teacher->changePassword(password);

			// store in user trees
			users.insert(*new_Teacher);
			readers.insert(*new_Teacher);
			teachers.insert(*new_Teacher);
		}
		else if (user_type == 2)
		{
			librarian* new_Librarian = new librarian;
			new_Librarian->setUserName(username);
			new_Librarian->changePassword(password);

			// store in user trees
			users.insert(*new_Librarian);
			librarians.insert(*new_Librarian);
		}
		else
		{
			cout << "Error: User Type not supported";
			exit(1);
		}

		// Store usernames in doubly linkedlist
		usernames.push_back(username);
	}

	long long int isbn;
	string title, author, category;

	// Read information from book.txt
	while (datain2 >> isbn >> title >> author >> category)
	{
		// Create new book
		book* new_Book = new book;
		// Assign properties to book
		new_Book->setISBN(isbn);
		new_Book->setTitle(title);
		new_Book->setAuthor(author);
		new_Book->setCategory(category);
		// Insert book into binarysearch tree
		catelog.insert(*new_Book);
	}

	int id, i;

	// Read infromation from copy.txt
	while (datain3 >> isbn >> id)
	{
		// Temporary book to toggle Binary Tree Node
		book* temp = new book;
		temp->setISBN(isbn);

		// Check if book with ISBN is in catelog
		if (catelog.search(*temp))
		{
			// Target Node's data will be replaced with temp
			// Find location of book in catelog binary tree
			*temp = catelog.findTarget(*temp)->getData();
			// Increment number of copies book has 
			temp->setnbrCopies(temp->getnbrCopies() + 1);
			// Insert copy ID into book's copy array
			temp->setID(id, temp->getnbrCopies() - 1);
		}
		else
		{
			cout << "Error: Copy does not belong in this library!";
			exit(1);
		}

		// Temporary Node to toggle Binary Tree Node
		Node<book>* temp_node = new Node<book>;
		temp_node = catelog.findTarget(*temp);
		// Store book data in temporary Node 
		temp_node->setData(*temp);

		// Insert copy into binary search tree
		bookcopy* new_Copy = new bookcopy;
		new_Copy->setBook(temp_node->getData());
		new_Copy->setID(id);
		library.insert(*new_Copy);

		delete temp;
	}

	/* User Authentication */
	user User;
	cout << "Please enter your username: ";
	cin >> username;
	cout << "Please enter your password: ";
	cin >> password;
	cout << endl;

	User.setUserName(username);
	User.changePassword(password);

	if (userAuthentication(User))
	{
		cout << "-------------------------------------------------" << endl;

		cout << "-		Welcome to My Library!		-" << endl;

		cout << "-------------------------------------------------" << endl;
	}
	else

	{
		cout << "Incorrect Username or Password";
		exit(1);
	}

	if (isStudent(User))
	{
		student S;
		S.setUserName(User.getUserName());
		S.changePassword(User.getPassword());

		Studentmenu(S, clock());
	}
	else if (isTeacher(User))
	{
		teacher T;
		T.setUserName(User.getUserName());
		T.changePassword(User.getPassword());

		Teachermenu(T, clock());
	}
	else if (isLibrarian(User))
	{
		librarian L;
		L.setUserName(User.getUserName());
		L.changePassword(User.getPassword());

		Librarianmenu(L, clock());
	}

	return 0;
}

bool userAuthentication(user& User)
{
	return searchUser(users.getRoot(), User);

}
bool isStudent(user& User)
{
	student* tempStudent = new student;
	tempStudent->setUserName(User.getUserName());;
	tempStudent->changePassword(User.getPassword());
	bool temp = students.search(*tempStudent);
	delete tempStudent;
	return temp;
}
bool isTeacher(user& User)
{
	teacher* tempTeacher = new teacher;
	tempTeacher->setUserName(User.getUserName());;
	tempTeacher->changePassword(User.getPassword());
	bool temp = teachers.search(*tempTeacher);
	delete tempTeacher;
	return temp;
}
bool isLibrarian(user& User)
{
	librarian* tempLibrarian = new librarian;
	tempLibrarian->setUserName(User.getUserName());;
	tempLibrarian->changePassword(User.getPassword());
	bool temp = librarians.search(*tempLibrarian);
	delete tempLibrarian;
	return temp;
}

void Studentmenu(student& S, clock_t time)
{
	int option;
	char method;
	int return_id, borrow_id;
	long long int reserve_isbn;
	string password;
	//Display menu to user to select options
	cout << "\nWelcome back, " << S.getUserName() << endl;
	cout << "\nStudent Options: " << endl;
	cout << "\t1 -- Search for Book" << endl;
	cout << "\t2 -- Borrow Book" << endl;
	cout << "\t3 -- Return Book" << endl;
	cout << "\t4 -- Renew Book" << endl;
	cout << "\t5 -- Reserve Book" << endl;
	cout << "\t6 -- Cancel Book" << endl;
	cout << "\t7 -- My Information" << endl;
	cout << "\t8 -- Change Password" << endl;
//	cout << "\t9 -- I'm Feeling Lucky" << endl;
	cout << "\t0 -- Log Out" << endl;
	cout << "\tPlease enter an option: ";
	cin >> option;
	while (option != 0)
	{
		if (option == 1)
		{
			cout << "Search by ISBN, title, category, or ID?" << endl;
			cout << "(a) ISBN\n(b) Title\n(c) Category\n(d) ID\n(e) Exit\nEnter an option: ";
			cin >> method;
			S.SearchBook(library, catelog, method);
		}
		else if (option == 2)
		{
			cout << "Enter the ID of the book you would like to borrow: ";
			cin >> borrow_id;
			S.BorrowBook(library, catelog, borrow_id, time, S);
		}
		else if (option == 3)
		{
			cout << "Enter the ID of the book you would like to return: ";
			cin >> return_id;
			S.ReturnBook(library, catelog, return_id, time);
		}
		else if (option == 4)
		{
			S.RenewBook(library, time);
		}
		else if (option == 5)
		{
			cout << "Enter the ISBN of the book you would like to reserve: ";
			cin >> reserve_isbn;
			S.ReserveBook(library, catelog, reserve_isbn, time, S);
		}
		else if (option == 6)
		{
			list<bookcopy> cr = S.getcopies_reserved();
			int index;
			vector<bookcopy> bc;
			for (list<bookcopy>::iterator it = cr.begin(); it != cr.end(); ++it)
			{
				bc.push_back(*it);
				cout << *it;
			}
			cout << "Please list the number of the book you wish to have your reservation canceled for: ";
			cin >> index;
			S.CancelReservation(bc[index - 1], time);
		}
		else if (option == 7)
		{
			S.myInformation();
		}
		else if (option == 8)
		{
			cout << "Please enter your new password: ";
			cin >> password;
			S.changePassword(password);
		}
/*		else if (option == 9)
		{
			S.feelingLucky(library, catelog);
		}
*/		cout << endl;
		cout << "\nTeacher Options: " << endl;
		cout << "\t1 -- Search for Book" << endl;
		cout << "\t2 -- Borrow Book" << endl;
		cout << "\t3 -- Return Book" << endl;
		cout << "\t4 -- Renew Book" << endl;
		cout << "\t5 -- Reserve Book" << endl;
		cout << "\t6 -- Cancel Book" << endl;
		cout << "\t7 -- My Information" << endl;
		cout << "\t8 -- Change Password" << endl;
//		cout << "\t9 -- I'm Feeling Lucky" << endl;
		cout << "\t0 -- Log Out" << endl;
		cout << "\tPlease enter an option: ";
		cin >> option;
	}
	cout << "Logging Out" << endl;
}
void Teachermenu(teacher& T, clock_t time)
{
	int option;
	char method;
	int return_id, borrow_id;
	long long int reserve_isbn;
	string password;
	//Display menu to user to select options
	cout << "\nWelcome back, " << T.getUserName() << endl;
	cout << "\nTeacher Options: " << endl;
	cout << "\t1 -- Search for Book" << endl;
	cout << "\t2 -- Borrow Book" << endl;
	cout << "\t3 -- Return Book" << endl;
	cout << "\t4 -- Renew Book" << endl;
	cout << "\t5 -- Reserve Book" << endl;
	cout << "\t6 -- Cancel Book" << endl;
	cout << "\t7 -- My Information" << endl;
	cout << "\t8 -- Change Password" << endl;
//	cout << "\t9 -- I'm Feeling Lucky" << endl;
	cout << "\t0 -- Log Out" << endl;
	cout << "\tPlease enter an option: ";
	cin >> option;
	while (option != 0)
	{
		if (option == 1)
		{
			cout << "Search by ISBN, title, category, or ID?" << endl;
			cout << "(a) ISBN\n(b) Title\n(c) Category\n(d) ID\n(e) Exit\nEnter an option: ";
			cin >> method;
			T.SearchBook(library, catelog, method);
		}
		else if (option == 2)
		{
			cout << "Enter the ID of the book you would like to borrow: ";
			cin >> borrow_id;
			T.BorrowBook(library, catelog, borrow_id, time, T);
		}
		else if (option == 3)
		{
			cout << "Enter the ID of the book you would like to return: ";
			cin >> return_id;
			T.ReturnBook(library, catelog, return_id, time);
		}
		else if (option == 4)
		{
			T.RenewBook(library, time);
		}
		else if (option == 5)
		{
			cout << "Enter the ISBN of the book you would like to reserve: ";
			cin >> reserve_isbn;
			T.ReserveBook(library, catelog, reserve_isbn, time, T);
		}
		else if (option == 6)
		{
			list<bookcopy> cr = T.getcopies_reserved();
			int index;
			vector<bookcopy> bc;
			for (list<bookcopy>::iterator it = cr.begin(); it != cr.end(); ++it)
			{
				bc.push_back(*it);
				cout << *it;
			}
			cout << "Please list the number of the book you wish to have your reservation canceled for: ";
			cin >> index;
			T.CancelReservation(bc[index - 1], time);
		}
		else if (option == 7)
		{
			T.myInformation();
		}
		else if (option == 8)
		{
			cout << "Please enter your new password: ";
			cin >> password;
			T.changePassword(password);
		}
/*		else if (option == 9)
		{
			T.feelingLucky(library, catelog);
		}
*/		cout << endl;
		cout << "\nTeacher Options: " << endl;
		cout << "\t1 -- Search for Book" << endl;
		cout << "\t2 -- Borrow Book" << endl;
		cout << "\t3 -- Return Book" << endl;
		cout << "\t4 -- Renew Book" << endl;
		cout << "\t5 -- Reserve Book" << endl;
		cout << "\t6 -- Cancel Book" << endl;
		cout << "\t7 -- My Information" << endl;
		cout << "\t8 -- Change Password" << endl;
//		cout << "\t9 -- I'm Feeling Lucky" << endl;
		cout << "\t0 -- Log Out" << endl;
		cout << "\tPlease enter an option: ";
		cin >> option;
	}
	cout << "Logging Out" << endl;
}
void Librarianmenu(librarian& L, clock_t time)
{
	int option;
	char method;
	int id;
	string password;
	//Display menu to user to select options
	cout << "\nWelcome back, " << L.getUserName() << endl;
	cout << "\nLibrarian Options: " << endl;
//	cout << "\t1 -- Search for Book" << endl;
	cout << "\t1 -- Add Books" << endl;
	cout << "\t2 -- Delete Books" << endl;
	cout << "\t3 -- Search Users" << endl;
	cout << "\t4 -- Add Users" << endl;
	cout << "\t5 -- Delete Users" << endl;
	cout << "\t6 -- My Information" << endl;
	cout << "\t7 -- Change Password" << endl;
	cout << "\t0 -- Log Out" << endl;
	cout << "\tPlease enter an option: ";
	cin >> option;
	while (option != 0)
	{
		if (option == 1)
		{
			L.addBook(library, catelog);
		}
		else if (option == 2)
		{
			L.deleteBook(library, catelog);
		}
		else if (option == 3)
		{
			L.searchUsers(students, teachers, librarians);
		}
		else if (option == 4)
		{
			L.addUser(users, students, teachers, librarians);
		}
		else if (option == 5)
		{
			L.deleteUser(users, students, teachers, librarians);
		}
		else if (option == 6)
		{
			L.myInformation();
		}
		else if (option == 7)
		{
			cout << "Please enter your new password: ";
			cin >> password;
			L.changePassword(password);
		}
		cout << endl;
		cout << "\nLibrarian Options: " << endl;
		cout << "\t1 -- Add Books" << endl;
		cout << "\t2 -- Delete Books" << endl;
		cout << "\t3 -- Search Users" << endl;
		cout << "\t4 -- Add Users" << endl;
		cout << "\t5 -- Delete Users" << endl;
		cout << "\t6 -- My Information" << endl;
		cout << "\t7 -- Change Password" << endl;
		cout << "\t0 -- Log Out" << endl;
		cout << "\tPlease enter an option: ";
		cin >> option;
	}
	cout << "Logging Out" << endl;
}

bool searchUser(BinaryTree<user>::iterator iter, user& target)
{
	// Base case 1: target is not in the binary tree
	if (iter == nullptr)
	{
		return false;
	}
	// Base case 2: Target Node found
	else if (iter->getData().getUserName() == target.getUserName() && iter->getData().getPassword() == target.getPassword())
	{
		return true;
	}
	// If target > node value, search right subtree
	else if (target > iter->getData())
	{
		searchUser(iter->getRight(), target);
	}
	// If target < node value, search left subtree
	else if (target < iter->getData())
	{
		searchUser(iter->getLeft(), target);
	}
}