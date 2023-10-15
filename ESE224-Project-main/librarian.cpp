#include "librarian.h"
void searchTitle(BinaryTree<book>::iterator iter, string title, bool& result)
{
	// Base case 1: target is not in the binary tree
	if (iter == nullptr)
	{
		return;
	}
	// Base case 2: target found
	else if (iter->getData().getTitle() == title)
	{
		result = true;
		return;
	}
	//PreOrder Traversal of Binary Tree
	searchTitle(iter->getLeft(), title, result);
	searchTitle(iter->getRight(), title, result);
}
void findISBN(BinaryTree<book>::iterator iter, string title, int long long& result)
{
	// Base case 1: target is not in the binary tree
	if (iter == nullptr)
	{
		return;
	}
	// Base case 2: target found
	else if (iter->getData().getTitle() == title)
	{
		result = iter->getData().getISBN();
		return;
	}
	//PreOrder Traversal of Binary Tree
	findISBN(iter->getLeft(), title, result);
	findISBN(iter->getRight(), title, result);
}
/* Constructors */
librarian::librarian()
{
	setUserName("None");
	changePassword("None");
}
librarian::librarian(string u, string p)
{
	setUserName(u);
	changePassword(p);
}
void librarian::searchUsers(BinaryTree<student>& students, BinaryTree<teacher>& teachers, BinaryTree<librarian>& librarians)
{
	string uName;
	cout << "\nEnter a UserName: ";
	cin >> uName;
	student tempS;
	tempS.setUserName(uName);

	teacher tempT;
	tempT.setUserName(uName);
	librarian tempL;
	tempL.setUserName(uName);
	if (students.search(tempS))
	{
		tempS = students.findTarget(tempS)->getData();
		cout << tempS;
	}
	else if (teachers.search(tempT))
	{
		tempT = teachers.findTarget(tempT)->getData();
		cout << tempT;
	}
	else if (librarians.search(tempL))
	{
		tempL = librarians.findTarget(tempL)->getData();
		cout << tempL;
	}
	else
		cout << "\nUser is not in library database\n";
}
void librarian::addUser(BinaryTree<user>& users, BinaryTree<student>& students, BinaryTree<teacher>& teachers, BinaryTree<librarian>& librarians)
{
	string type, username, password;
	fstream data;
	cout << "\nEnter user type Teacher, Student, or Librarian:";
	cin >> type;
	user tempUser;
	cout << "\nEnter new username:";
	cin >> username;
	tempUser.setUserName(username);
	cout << "\nEnter new password:";
	cin >> password;
	tempUser.changePassword(password);
	if (users.search(tempUser))
	{
		cout << "\nUser already exists\n";
		return;
	}
	data.open("student.txt", std::ios::app);
	if (data.fail())
	{
		cerr << "Error: File \"student.txt\" cannot be opened.";
		exit(1);
	}
	if (type == "Student" || type == "student" || type == "STUDENT")
	{
		data << 0 << "\t" << username << "\t" << password;
		student* newStudent = new student;
		newStudent->setUserName(username);
		newStudent->changePassword(password);
		users.insert(*newStudent);
		students.insert(*newStudent);
	}
	else if (type == "Teacher" || type == "teacher" || type == "TEACHER")
	{
		data << 1 << "\t" << username << "\t" << password;
		teacher* newTeacher = new teacher;
		newTeacher->setUserName(username);
		newTeacher->changePassword(password);

		users.insert(*newTeacher);
		teachers.insert(*newTeacher);
	}
	else if (type == "Librarian" || type == "librarian" || type == "LIBRARIAN")
	{
		data << 2 << "\t" << username << "\t" << password;// << "\n";
		librarian* newLibrarian = new librarian;
		newLibrarian->setUserName(username);
		newLibrarian->changePassword(password);
		users.insert(*newLibrarian);
		librarians.insert(*newLibrarian);
	}
	else
	{
		cout << "\nInvalid user type.\n";
		data.close();
		return;
	}
	data.close();
}
void librarian::deleteUser(BinaryTree<user>& users, BinaryTree<student>& students, BinaryTree<teacher>& teachers, BinaryTree<librarian>& librarians)
{
	string username;
	cout << "Enter Username of user you would like to delete: ";
	cin >> username;
	user tempU;
	tempU.setUserName(username);
	if (!users.search(tempU))
	{
		cout << "\nUser does not exist\n";
		return;
	}
	student tempS;
	tempS.setUserName(username);
	teacher tempT;
	tempT.setUserName(username);
	librarian tempL;
	tempL.setUserName(username);
	if (students.search(tempS))
	{
		tempS = students.findTarget(tempS)->getData();
		students.remove(tempS);
	}
	else if (teachers.search(tempT))
	{
		tempT = teachers.findTarget(tempT)->getData();
		teachers.remove(tempT);
	}
	else if (librarians.search(tempL))
	{
		tempL = librarians.findTarget(tempL)->getData();
		librarians.remove(tempL);
	}
	users.remove(tempU);
	fstream data;
	string line;
	int offset;
	ofstream outputfile;
	data.open("student.txt", std::ios::app);
	if (data.fail())
	{
		cerr << "Error: File \"student.txt\" cannot be opened.";
		exit(1);
	}
	data.close();
}
void librarian::addBook(BinaryTree<bookcopy>& library, BinaryTree<book>& catelog)
{
	book newBook;
	fstream data;
	cout << "\nEnter The ISBN, Title, Author, Category, and number of copies of the book you would like to add "
		<< "and enter the IDs of the copies: ";
	cin >> newBook;
	// check if book already exists
	if (catelog.search(newBook))
	{
		cout << "\Book already exists\n";
		return;
	}
	// open copy.txt file
	data.open("copy.txt", std::ios::app);
	if (data.fail())
	{
		cerr << "Error: File \"copy.txt\" cannot be opened.";
		exit(1);
	}
	// add book to catelog
	catelog.insert(newBook);
	vector<int> tempVec = newBook.getIDs();		//vector of book copy IDs
	for (int i = 0; i < tempVec.size(); i++)
	{
		bookcopy* newCopy = new bookcopy;
		newCopy->setBook(newBook);
		newCopy->setID(tempVec[i]);
		// check if copy with ID already exists
		if (library.search(*newCopy))
		{
			cout << "\nA book with the ID " << tempVec[i] << " already exists\n";
			// Decrement amount of copies book has
			newBook.setnbrCopies(newBook.getnbrCopies() - 1);
			// Invalid copy, delete
			delete newCopy;
		}
		else
		{
			// write new copy to copy.txt file
			data << "\n" << newBook.getISBN() << "\t" << newCopy->getID();
			// add new copy to library search tree
			library.insert(*newCopy);
		}
	}
	// close copy.txt file
	data.close();
	// open book.txt file
	data.open("book.txt", std::ios::app);
	if (data.fail())
	{
		cerr << "Error: File \"book.txt\" cannot be opened.";
		exit(1);
	}
	// write new book to book.txt file
	data << "\n" << newBook.getISBN() << "\t" << newBook.getTitle()
		<< "\t" << newBook.getAuthor() << "\t" << newBook.getCategory();
	data.close();
}
void librarian::deleteBook(BinaryTree<bookcopy>& library, BinaryTree<book>& catelog)
{
	book tempbook;
	string title;
	BinaryTree<book>::iterator iter = catelog.getRoot();
	cout << "Enter the title of the book you would like to delete: ";
	cin >> title;
	bool j = false;
	searchTitle(iter, title, j);
	// check if book exists
	if (!j)
	{
		cout << "\nBook does not exist.\n";
		return;
	}
	else
	{
		long long int i = 0;
		// get ISBN of book title
		iter = catelog.getRoot();
		findISBN(iter, title, i);
		tempbook.setISBN(i);
		tempbook = catelog.findTarget(tempbook)->getData();

		// remove book from catelog
		catelog.remove(tempbook);
		// remove copies from library
		vector<int> vec = tempbook.getIDs();
		bookcopy tempcopy;
		for (int i = 0; i < vec.size(); i++)
		{
			tempcopy.setID(vec[i]);
			library.remove(tempcopy);
		}
	}
	fstream data;
	// remove book from book.txt file
	data.open("book.txt", std::ios::app);
	if (data.fail())
	{
		cerr << "Error: File \"book.txt\" cannot be opened.";
		exit(1);
	}
	data.close();
	// remove copy from copy.txt file
	data.open("copy.txt", std::ios::app);
	if (data.fail())
	{
		cerr << "Error: File \"copy.txt\" cannot be opened.";
		exit(1);
	}
	data.close();
}
ostream& operator << (ostream& output, librarian& lib)
{
	cout << "User Type: Librarian" << endl;
	cout << "Username: " << lib.getUserName() << endl;
	cout << "Password: " << lib.getPassword() << endl;
	return cout;
}
