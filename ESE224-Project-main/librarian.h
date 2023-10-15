#pragma once
#include "user.h"
#include "bookcopy.h"
#include "binarytree.h"
#include <fstream>
#include "student.h"
#include "teacher.h"
using namespace std;

class librarian : public user
{
public:
	librarian();

	librarian(string u, string p);

	// Librarian can search for a user in a database by their username
	void searchUsers(BinaryTree<student>& students, BinaryTree<teacher>& teachers, BinaryTree<librarian>& librarians);

	// Librarian can add a new user to the data base, user must be different from existing users
	void addUser(BinaryTree<user>& users, BinaryTree<student>& students, BinaryTree<teacher>& teachers, BinaryTree<librarian>& librarians);

	// Librarian can delete a User by their username, cannot delete another librarian
	void deleteUser(BinaryTree<user>& users, BinaryTree<student>& students, BinaryTree<teacher>& teachers, BinaryTree<librarian>& librarians);

	// Librarian can add n copies of a new book to the library
	void addBook(BinaryTree<bookcopy>& library, BinaryTree<book>& catelog);

	// A librarian can remove an existing book and all of its copies from the library
	void deleteBook(BinaryTree<bookcopy>& library, BinaryTree<book>& catelog);

	friend ostream& operator << (ostream& output, librarian& lib);
};