#include "reader.h"
#include <iostream>
#include <string>

using namespace std;
int sortBookCopies(bookcopy a, bookcopy b)
{
	if (a.getExpiration_Date() > b.getExpiration_Date())
	{
		return 0;
	}
	else if (a.getExpiration_Date() == b.getExpiration_Date())
	{
		if (a.getTitle() > b.getTitle())
		{
			return 0;
		}
		else if (a.getTitle() < b.getTitle())
		{
			return 1;
		}
		else
		{
			if (a.getAuthor() > b.getAuthor())
			{
				return 0;
			}
			else if (a.getAuthor() < b.getAuthor())
			{
				return 1;
			}
			else
			{
				if (a.getISBN() > b.getISBN())
				{
					return 0;
				}
				else if (a.getISBN() < b.getISBN())
				{
					return 1;
				}
				else
				{
					if (a.getID() > b.getID())
					{
						return 0;
					}
					else
					{
						return 1;
					}
				}
			}
		}
	}
	else
	{
		return 1;
	}
}
int partition(vector<bookcopy> arr, int low, int high)
{
	int partition = (low + high) / 2;
	int left = 0, right = 0;
	int i, j;
	bookcopy temp;
	for (i = low; i < high; i++)
	{
		if (i != partition && sortBookCopies(arr[i], arr[partition]) == 0)
		{
			right++;
		}
		else if (i != partition && sortBookCopies(arr[i], arr[partition]) == 1)
		{
			left++;
		}
	}
	if ((high - right) < partition)
	{
		temp = arr[partition];
		arr[partition] = arr[high - right];
		arr[high - right] = temp;
		partition = high - right;
	}
	else if ((low + left) > partition)
	{
		temp = arr[partition];
		arr[partition] = arr[left + low];
		arr[left + low] = temp;
		partition = left + low;
	}
	j = partition + 1;
	for (i = low; i < partition; i++)
	{
		int change = 0;
		while (j < high && change == 0)
		{
			if ((sortBookCopies(arr[i], arr[partition]) == 0 && sortBookCopies(arr[j], arr[partition]) == 1))
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				change = 1;
			}
			if ((sortBookCopies(arr[i], arr[partition]) == 0 && sortBookCopies(arr[j], arr[partition]) == 1 || sortBookCopies(arr[j], arr[partition]) == 0))
			{
				j++;
			}
			else
			{
				break;
			}
		}
	}
	return partition;
}

void quickSort(vector<bookcopy> arr, int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void print_search_results(vector<bookcopy> results, int j)
{
	int i;
	quickSort(results, 0, j);
	for (i = 0; i < results.size(); i++)
	{
		cout << "\nCopy #" << (i + 1) << "\n" << results[i] << "\n";
	}
}

bookcopy bSearchID(BinaryTree<bookcopy> library, int value)
{
	bookcopy temp;
	temp.setID(value);
	if (library.search(temp))
	{
		temp = library.findTarget(temp)->getData();
		return temp;
	}
	return temp;
}

reader::reader()
{
	max_copies = 0;
	max_borrow_period = 0;
	copies_reserved.resize(0);
	copies_borrowed.resize(0);
	num_penalties = 0;
}
reader::reader(string u, string p, int mc, int mbp, int penalties, vector<bookcopy> cb, list<bookcopy> cr)
{
	setUserName(u);
	changePassword(p);
	max_copies = mc;
	max_borrow_period = mbp;
	num_penalties = penalties;
	copies_reserved = cr;
	copies_borrowed = cb;
}
int reader::getmax_Copies()
{
	return max_copies;
}
int reader::getmax_Borrow_Period()
{
	return max_borrow_period;
}
string reader::getuser_type()
{
	return "User";
}
vector<bookcopy> reader::getcopies_borrowed()
{
	return copies_borrowed;
}
list<bookcopy> reader::getcopies_reserved()
{
	return copies_reserved;
}
void reader::setmax_Copies(int mc)
{
	max_copies = mc;
	copies_borrowed.resize(mc);
}
void reader::setmax_Borrow_Period(int mbp)
{
	max_borrow_period = mbp;
}
void reader::setcopies_borrowed(vector<bookcopy> cb)
{
	copies_borrowed = cb;
}
void reader::setcopies_reserved(list<bookcopy> cr)
{
	copies_reserved = cr;
}
void reader::setcopy_borrowed(bookcopy cp)
{
	int i;
	for (i = 0; i < max_copies; i++)
	{
		if (copies_borrowed[i].getTitle() == "None")
		{
			copies_borrowed[i] = cp;
			return;
		}
	}
	if (i == max_copies)
		cout << "\nYou have borrowed the maximum amount of copies you are allowed.\n";
}
void reader::setcopy_reserved(bookcopy cr)
{
	list<bookcopy>::iterator iter = copies_reserved.begin();
	copies_reserved.insert(iter, cr);
}

void searchTitle1(BinaryTree<book>::iterator iter, string title, bool& result)
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
	searchTitle1(iter->getLeft(), title, result);
	searchTitle1(iter->getRight(), title, result);
}
void findISBN1(BinaryTree<book>::iterator iter, string title, long long int& result)
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
	findISBN1(iter->getLeft(), title, result);
	findISBN1(iter->getRight(), title, result);
}

void searchCategory(BinaryTree<book>::iterator iter, string category, bool& result)
{
	// Base case 1: target is not in the binary tree
	if (iter == nullptr)
	{
		return;
	}
	// Base case 2: target found
	else if (iter->getData().getCategory() == category)
	{
		result = true;
		return;
	}

	//PreOrder Traversal of Binary Tree
	searchCategory(iter->getLeft(), category, result);
	searchCategory(iter->getRight(), category, result);
}
void findISBN2(BinaryTree<book>::iterator iter, string category, long long int& result)
{
	// Base case 1: target is not in the binary tree
	if (iter == nullptr)
	{
		return;
	}
	// Base case 2: target found
	else if (iter->getData().getCategory() == category)
	{
		result = iter->getData().getISBN();
		return;
	}
	//PreOrder Traversal of Binary Tree
	findISBN2(iter->getLeft(), category, result);
	findISBN2(iter->getRight(), category, result);
}

void reader::SearchBook(BinaryTree<bookcopy> library, BinaryTree<book> catelog, char method)
{
	vector<bookcopy> results;
	int nbr_books = 0;
	int i = 0;

	switch (method)
	{
	case 'a':
	{
		long long int isbn;
		int j = 0;
		cout << "Enter the ISBN: ";
		cin >> isbn;
		book tempBook;
		bookcopy tempCopy;
		tempBook.setISBN(isbn);
		if (catelog.search(tempBook))
		{
			tempBook = catelog.findTarget(tempBook)->getData();
			vector<int> vec = tempBook.getIDs();

			for (int i = 0; i < tempBook.getnbrCopies(); i++)
			{
				tempCopy.setID(vec[i]);
				results.push_back(library.findTarget(tempCopy)->getData());
			}
		}
		else
		{
			cout << "\nBook not found.\n" << endl;
			break;
		}
		print_search_results(results, j);
		results.clear();
		break;
	}
	case 'b':
	{
		int j = 0;
		string title;
		book tempBook;
		bookcopy tempCopy;
		cout << "Enter the Title: ";
		cin >> title;
		BinaryTree<book>::iterator iter = catelog.getRoot();
		bool b = false;
		searchTitle1(iter, title, b);
		if (b)
		{
			long long int i;
			findISBN1(iter, title, i);
			tempBook.setISBN(i);
			tempBook = catelog.findTarget(tempBook)->getData();
			vector<int> vec = tempBook.getIDs();
			for (int i = 0; i < tempBook.getnbrCopies(); i++)
			{
				tempCopy.setID(vec[i]);
				results.push_back(library.findTarget(tempCopy)->getData());
			}
		}
		else
		{
			cout << "\nBook not found.\n" << endl;
			break;
		}
		print_search_results(results, results.size());
		results.clear();
		break;
	}
	case 'c':
	{
		int j = 0;
		string cat;
		book tempBook;
		bookcopy tempCopy;
		cout << "Enter the Category: ";
		cin >> cat;
		BinaryTree<book>::iterator iter = catelog.getRoot();
		bool b = false;
		searchCategory(iter, cat, b);
		if (b)
		{
			long long int i;
			findISBN2(iter, cat, i);
			tempBook.setISBN(i);
			tempBook = catelog.findTarget(tempBook)->getData();
			vector<int> vec = tempBook.getIDs();
			for (int i = 0; i < tempBook.getnbrCopies(); i++)
			{
				tempCopy.setID(vec[i]);
				results.push_back(library.findTarget(tempCopy)->getData());
			}
		}
		else
		{
			cout << "\nBook not found.\n" << endl;
			break;
		}
		print_search_results(results, results.size());		
		results.clear();
		break;
	}
	case 'd':
	{
		int id, j = 0;
		cout << "Enter the ID: ";
		cin >> id;
		bookcopy temp;
		temp.setID(id);
		if (library.search(temp))
		{
			temp = library.findTarget(temp)->getData();
			results.push_back(temp);
		}
		else
		{
			cout << "\nBook not found.\n" << endl;
			break;
		}
		print_search_results(results, results.size());
		results.clear();
		break;
	}
	case 'e':
	{
		return;
		break;
	}
	default:
		cout << "\nInvalid search method.\n" << endl;
		break;
	}
}

void reader::BorrowBook(BinaryTree<bookcopy> library, BinaryTree<book> catelog, int id, clock_t time, user u)
{
	bookcopy target = bSearchID(library, id);
	vector<bookcopy> borrowed = getcopies_borrowed();
	reverse(borrowed.begin(), borrowed.end());
	clock_t time1 = time;
	time1 = clock() - time;
	for (int i = 0; i < borrowed.size(); i++) //check for overdue copies
	{
		if (borrowed[i].getExpiration_Date() != 0 && borrowed[i].getExpiration_Date() < ((time1 / CLOCKS_PER_SEC) / 5))
		{
			cout << "\nPlease return all overdue books before borrowing a new one.\n" << endl;
			return;
		}
	}
	int nbr_borrowed = 0;
	for (int i = 0; i < borrowed.size(); i++) //check if reader has borrowed maximum number of copies
	{
		if (borrowed[i].getBook().getTitle() != "None") {
			nbr_borrowed++;
		}
	}
	if (nbr_borrowed >= getmax_Copies())
	{
		cout << "\nYou have already borrowed the maximum number of books. Please return one before borrowing a new one.\n" << endl;
	}

	if (&target == NULL)
	{
		cout << "\nThat book is not in the library.\n" << endl;
		return;
	}
	for (int i = 0; i < nbr_borrowed; i++) //check if copy of book already borrowed
	{
		if (borrowed[i].getBook().getTitle() == target.getBook().getTitle())
		{
			cout << "\nYou already borrowed a copy of that book.\n" << endl;
			return;
		}
	}
	if (target.getExpiration_Date() != 0) //check if book is not available
	{
		cout << "\nThat book is not available to be borrowed. Would you like to reserve it? (y/n): ";
		char ans;
		cin >> ans;
		if (ans == 'y') {
			ReserveBook(library, catelog, target.getBook().getISBN(), time, u);
		}
		return;
	}
	else
	{
		//update start and expiration dates
		time = clock() - time;
		int startdate = (time / CLOCKS_PER_SEC) / 5;
		target.setStart_Date(startdate);
		target.setExpiration_Date(startdate + getmax_Borrow_Period());
		target.setReserve_Date(0);
		target.setReader_Name(getUserName());
		//increment amount of times the copy has been borrowed
		target.incTimesBorrowed();
		//store in borrowed
		setcopy_borrowed(target);
		cout << "\n" << target.getBook().getTitle() << " has been successfully borrowed. Please return it within " << getmax_Borrow_Period() << " days (Day #"
			<< target.getExpiration_Date() << ").\n" << endl;
		BinaryTree<bookcopy>::iterator iter = library.findTarget(target);
		iter->setData(target);
		return;
	}


}
void reader::ReturnBook(BinaryTree<bookcopy> library, BinaryTree<book> catelog, int id, clock_t time)
{
	int j = 0, index1 = 0;
	vector<bookcopy> borrowed = getcopies_borrowed();
	
	for (int i = 0; i < borrowed.size(); i++) {
		if (borrowed[i].getID() == id) 
		{
			i = index1;
			break;
		}
		else
		{
			if (i == borrowed.size() - 1)
			{
				cout << "\nYou do not own a copy of that book\n";
				return;
			}
		}
	}
	for (int i = index1; i < borrowed.size(); i++)
	{
		if (i < borrowed.size() - 1)
			borrowed[i] = borrowed[i + 1];
	}

	//reset book copy dates and reader name

	bookcopy temp;
	temp.setID(id);
	BinaryTree<bookcopy>::iterator target = library.findTarget(temp);
	temp = target->getData();
	int new_date = 0;
	temp.setStart_Date(new_date);
	temp.setExpiration_Date(new_date);
	temp.setReader_Name("None");
	cout << "\nThe book has been successfully returned. How much did you like this book? ";
	int f, new_favor;
	cin >> f;


	book tb = temp.getBook();
	BinaryTree<book>::iterator iter = catelog.findTarget(tb);

	if (temp.getTimes_Borrowed() > 0)
	{
		new_favor = (f + (temp.getBook().getFavor()) / (temp.getTimes_Borrowed()));

		book tempBook = temp.getBook();
		tempBook.setFavor(new_favor);
		temp.setBook(tempBook);
	}
	//loan book to next reserver
	if (temp.getReserver_Name() != "None") {
		user u = temp.getBook().getReserver();
		CancelReservation(temp, time);
		temp.setReader_Name(temp.getReserver_Name());
		temp.setReserver_Name(temp.getReserver_Name());
		clock_t time2 = clock() - time;
		temp.setReserve_Date(((time2 / CLOCKS_PER_SEC) / 5) + 5);
	}
	else
	{
		temp.setReader_Name("None");
		temp.setReserver_Name("None");
	}

	target->setData(temp);
	iter->setData(target->getData().getBook());

	setcopies_borrowed(borrowed);
	int i;
	return;
}

void reader::RenewBook(BinaryTree<bookcopy> library, clock_t time)
{
	int nbr_borrowed = 0;
	cout << "\nBorrowed books: ----------------------------" << endl;
	vector<bookcopy> borrowed = getcopies_borrowed();
	for (int i = 0; i < getmax_Copies(); i++)
	{
		if (borrowed[i].getBook().getTitle() != "None") {
			nbr_borrowed++;
		}
	}
	for (int i = 0; i < nbr_borrowed; i++)
	{
		cout << endl;
		cout << borrowed[i];
		cout << "-----------------------------------------------" << endl;
	}
	int id;
	cout << "Enter the ID of the book you would like to renew: ";
	cin >> id;
	bookcopy target = bSearchID(library, id);
	int found = false;
	for (int i = 0; i < nbr_borrowed; i++)
	{
		if (borrowed[i].getID() == id)
		{
			found = true;
		}
	}
	if (found == false)
	{
		cout << "\nThere is no book in your borrowed copies with ID #" << id << ".\n" << endl;
		return;
	}
	Node<bookcopy>* index = library.findTarget(target);		//find copy location in library
	if (index == nullptr)
	{
		cout << "\nThere is no book with ID " << id << " in this library\n" << endl;
		return;
	}
	if (target.getReserver_Name() != "None") {
		cout << "\nYou cannot renew that book, it has been reserved by someone else. \n" << endl;
		return;
	}
	time = clock() - time;
	int startdate = (time / CLOCKS_PER_SEC) / 5;
	target.setStart_Date(startdate);
	target.setExpiration_Date(startdate + getmax_Borrow_Period());
	cout << "\n" << target.getBook().getTitle() << " has been successfully renewed. Please return it within " << getmax_Borrow_Period() << " days (Day #"
		<< target.getExpiration_Date() << ").\n" << endl;
}

void reader::ReserveBook(BinaryTree<bookcopy> library, BinaryTree<book> catelog, long long int isbn, clock_t time, user u)
{
	book temp;
	temp.setISBN(isbn);
	if (catelog.search(temp))
	{
		temp = catelog.findTarget(temp)->getData();
	}
	else
	{
		cout << "\nThere is no book with that ISBN.\n" << endl;
		return;
	}
	vector<bookcopy> borrowed = getcopies_borrowed();
	clock_t time1 = time;
	time1 = clock() - time;
	for (int i = 0; i < borrowed.size(); i++) //check for overdue copies
	{
		if (borrowed[i].getExpiration_Date() != 0 && borrowed[i].getExpiration_Date() < ((time1 / CLOCKS_PER_SEC) / 5)) {
			cout << "\nPlease return all overdue books before reserving a new one.\n" << endl;
			return;
		}
	}
	int nbr_borrowed = 0;
	for (int i = 0; i < getmax_Copies(); i++) //check if reader has borrowed maximum number of copies
	{
		if (borrowed[i].getBook().getTitle() != "None") {
			nbr_borrowed++;
		}
	}
	if (nbr_borrowed >= getmax_Copies())
	{
		cout << "\nYou have already borrowed the maximum number of books. Please return one before reserving a new one.\n" << endl;
	}
	for (int i = 0; i < nbr_borrowed; i++) //check if copy of book already borrowed
	{
		if (borrowed[i].getBook().getTitle() == temp.getTitle())
		{
			cout << "\nYou already borrowed a copy of that book.\n" << endl;
			return;
		}
	}
	list<user>::iterator it;
	for (it = temp.getReserverList().begin(); it != temp.getReserverList().end(); it++) {
		string name = it->getUserName();
		if (name == getUserName()) {
			cout << "You are already on the list of reservers for this book. " << endl;
			return;
		}
	}
	//else reservation goes through:
	temp.setReserver(u);
	cout << "\nYou have successfully reserved " << temp.getTitle() << ".\n" << endl;
	for (int i = 0; i < temp.getIDs().size(); i++) {
		int id_tmp = temp.getIDs()[i];
		if (bSearchID(library, id_tmp).getReader_Name() == "None") {
			bSearchID(library, id_tmp).setReserver_Name(getUserName());
			bSearchID(library, id_tmp).setReserve_Date((((clock() - time) / CLOCKS_PER_SEC) / 5) + 5);
			break;
		}
	}
}

void reader::CancelReservation(bookcopy b, clock_t time)
{
	//take off list
	list<user>::iterator it;
	for (it = b.getBook().getReserverList().begin(); it != b.getBook().getReserverList().end(); it++) {
		string name = it->getUserName();
		if (name == getUserName()) {
			b.getBook().getReserverList().erase(it);
			return;
		}
	}
	//add next reserver to copy
	if (!b.getBook().getReserverList().empty()) {
		b.setReserver_Name(b.getBook().getReserver().getUserName());
		b.setReserve_Date((((clock() - time) / CLOCKS_PER_SEC) / 5) + 5);
	}
	else { //if there is no one else on the reserver list
		b.setReserver_Name("None");
		b.setReserve_Date(0);
	}
	return;
}

void treeToFavorArray(Node<bookcopy>* node, int arr[], int i) {
	if (node == NULL) return;
	arr[i] = node->getData().getBook().getFavor();
	treeToFavorArray(node->getLeft(), arr, i++);
	treeToFavorArray(node->getRight(), arr, i++);
}
/*
void reader::feelingLucky(BinaryTree<bookcopy> library, BinaryTree<book> catelog)
{
	//convert library tree to array for quickSort
	int arr[100];
	Node<bookcopy>* node = library.getRoot();
	treeToFavorArray(node, arr, 0);
	int arrSize = 0;
	for (int i = 0; i < 100; i++)
	{
		if (arr[i] != 0) 
		{
			arrSize++;
		}
	}

	//quicksort by favor ratings
	quickSort(arr, 0, arrSize - 1);
	cout << "The top 10 most liked books are: " << endl;
	for (int i = arrSize - 1; i >= arrSize - 10; i--) {
		book temp; //find books corresponding to top ranked favors
		temp.setFavor(arr[i]);
		if (catelog.search(temp))
		{
			temp = catelog.findTarget(temp)->getData();
		}
		cout << "#" << i + 1 << ": " << temp.getTitle() << " (Favor: " << arr[i] << ") " << endl;
	}
}
*/
void reader::operator = (reader rhs)
{
	max_copies = rhs.max_copies;
	max_borrow_period = rhs.max_borrow_period;
	copies_reserved = rhs.copies_reserved;

	setUserName(rhs.getUserName());
	changePassword(rhs.getPassword());

	for (int i = 0; i < max_copies; i++)
	{
		copies_borrowed[i] = rhs.copies_borrowed[i];
	}
}