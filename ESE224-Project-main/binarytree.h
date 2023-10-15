#pragma once
#include "Node.h" 
#include <iostream> 

using namespace std;

template<typename T>
class BinaryTree
{
private:
	// prints binary search tree with preorder traversal
	void printpreOrder(Node<T>* rt) const;

	// prints binary search tree with inorder traversal
	void printinOrder(Node<T>* rt) const;

	// prints binary searchtree with postorder traversal
	void printpostOrder(Node<T>* rt) const;

	// Returns 1 if a target value is inside of the binarysearch tree, returns 0 otherwises
	bool search(Node<T>* rt, T& target);

	// Returns the node where the target value is located inside of the binarysearch tree
	Node<T>* findTarget(Node<T>* rt, T& target);

	// Inserts a value into the binarysearch tree while maintaining its property the a left child is less than its parent node and a right child is greater than its parent node
	void insert(Node<T>* rt, T value);

	// Removess a value from the binarysearch tree while maintaining its property the a left child is less than its parent node and a right child is greater than its parent node
	void remove(Node<T>* rt, T value);

	// Deletes all elements of the binarysearch tree
	void clear(Node<T>* rt);

	// Returns the parent Node of a target in the binary search tree
	Node<T>* findTargetPrevious(Node<T>* rt, T target);

	// Sorts binary tree into binary search tree
	void sort(Node<T>* rt);

	// Returns the largest node in a subtree
	Node<T>* findLargest(Node<T>* rt);

	// Returns the smallest node in a subtree
	Node<T>* findSmallest(Node<T>* rt);

	//BinaryTree root
	Node<T>* root;
public:
	// Default Constructor
	BinaryTree();
	
	//iterator
	typedef Node<T>* iterator;
	
	// Calls private method if tree is not empty
	void sort();

	// Calls private method if tree is not empty
	Node<T>* findTargetPrevious(T target);

	// Returns the root node of the binary search tree
	Node<T>* getRoot();

	// Calls private method if tree is not empty
	void printpreOrder() const;

	// Calls private method if tree is not empty
	void printinOrder() const;

	// Calls private method if tree is not empty
	void printpostOrder() const;

	// Calls private method if tree is not empty
	bool search(T& target);

	// Calls private method if tree is not empty
	Node<T>* findTarget(T& target);

	// Calls private method if tree is not empty
	void insert(T value);

	// Calls private method if tree is not empty
	void remove(T value);

	// Calls private method if tree is not empty
	void clear();
};
//Constructor
template<typename T>
BinaryTree<T>::BinaryTree() :root(0)
{
}
//Root accessor
template<typename T>
Node<T>* BinaryTree<T>::getRoot()
{
	return root;
}
//clear: Public method
template<typename T>
void BinaryTree<T>::clear()
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		clear(root); //call private method
		root = nullptr; 
	}
}
//clear: private method
template<typename T>
void BinaryTree<T>::clear(Node<T>* theRoot)
{
	if (theRoot == nullptr)
		return;
	else
	{
		clear(theRoot->getLeft());
		clear(theRoot->getRight());
		delete theRoot;
	}
}
//print preOrder: Public method
template<typename T>
void BinaryTree<T>::printpreOrder() const
{
	if (root == nullptr)
	{
		cout << "tree is empty ";
		return;
	}
	else
		printpreOrder(root); //call private method
}
//print preOrder: private method
template<typename T>
void BinaryTree<T>::printpreOrder(Node<T>* theRoot) const
{
	if (theRoot == nullptr)
		return;
	else
	{
		cout << theRoot->getData() << ' ';
		printpreOrder(theRoot->getLeft());
		printpreOrder(theRoot->getRight());
	}
}
//print inOrder: Public method
template<typename T>
void BinaryTree<T>::printinOrder() const
{
	if (root == nullptr)
	{
		cout << "tree is empty ";
		return;
	}
	else
		printinOrder(root); //call private method
}
//print inOrder: private method
template<typename T>
void BinaryTree<T>::printinOrder(Node<T>* theRoot) const
{
	if (theRoot == nullptr)
		return;
	else
	{
		printinOrder(theRoot->getLeft());
		cout << theRoot->getData() << ' ';
		printinOrder(theRoot->getRight());
	}
}
//print postOrder: Public method
template<typename T>
void BinaryTree<T>::printpostOrder() const
{
	if (root == nullptr)
	{
		cout << "tree is empty ";
		return;
	}
	else
		printpostOrder(root); //call private method
}
//print postOrder: private method
template<typename T>
void BinaryTree<T>::printpostOrder(Node<T>* theRoot) const
{
	if (theRoot == nullptr)
		return;
	else
	{
		printpostOrder(theRoot->getLeft());
		printpostOrder(theRoot->getRight());
		cout << theRoot->getData() << ' ';
	}
}
//insert: public method
template<typename T>
void BinaryTree<T>::insert(T value)
{
	if (root == nullptr)
		root = new Node<T>(value);
	else
		insert(root, value); //call private method
}
//insert: private method
template<typename T>
void BinaryTree<T>::insert(Node<T>* root, T value)
{
	if (root == nullptr)
	{
		root = new Node<T>(value);
		return;
	}

	if (value < root->getData())
	{
		//Traverse the left subtree
		if (root->getLeft() == nullptr)
		{
			//insert new node here.
			root->setLeft(new Node<T>(value));
		}
		else
		{
			//recursive call to traverse left subtree
			insert(root->getLeft(), value);
		}
	}
	else
	{
		//Traverse the right subtree
		if (root->getRight() == nullptr)
		{
			//insert new node here
			root->setRight(new Node<T>(value));
		}
		else
		{
			//recursive call to traverse right subtree
			insert(root->getRight(), value);
		}
	}
}
//search: public method
template<typename T>
bool BinaryTree<T>::search(T& target)
{
	if (root == nullptr)
	{
		return false;
	}
	else
		search(root, target); //call private method
}
//search: private method
template<typename T>
bool BinaryTree<T>::search(Node<T>* rt, T& target)
{
	// Base case 1: target is not in the binary tree
	if (rt == nullptr)
	{
		return false;
	}
	// Base case 2: Target Node found
	else if (rt->getData() == target)
	{
		return true;
	}
	// If target > node value, search right subtree
	else if (target > rt->getData())
	{
		if (rt->getRight() != nullptr)
			search(rt->getRight(), target);
		else if (rt->getLeft() != nullptr)
			search(rt->getLeft(), target);
	}	
	// If target < node value, search left subtree
	else if (target < rt->getData())
	{
		if (rt->getLeft() != nullptr)
			search(rt->getLeft(), target);
		else if (rt->getRight() != nullptr)
			search(rt->getLeft(), target);
	}
}
//findTarget: public method
template<typename T>
Node<T>* BinaryTree<T>::findTarget(T& target)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
		findTarget(root, target); //call private method
}
//findTarget: private method
template<typename T>
Node<T>* BinaryTree<T>::findTarget(Node<T>* rt, T& target)
{
	// Base case 1: target is not in the binary tree
	if (rt == nullptr)
	{
		return nullptr;
	}
	// Base case 2: Target Node found
	else if (rt->getData() == target)
	{
		return rt;
	}
	// If target > node value, search right subtree
	else if (target > rt->getData())
	{
		if (rt->getRight() != nullptr)
			findTarget(rt->getRight(), target);
		else if (rt->getLeft() != nullptr)
			findTarget(rt->getLeft(), target);
	}
	// If target < node value, search left subtree
	else if (target < rt->getData())
	{
		if (rt->getLeft() != nullptr)
			findTarget(rt->getLeft(), target);
		else if (rt->getRight() != nullptr)
			findTarget(rt->getRight(), target);
	}
}
//remove: public method
template <typename T>
void BinaryTree<T>::remove(T value)
{
	if (root == nullptr)
	{
		cout << "BinarySearch Tree is empty!";
		exit(1);
	}
	// if root is leaf node
	else if (root->isLeaf())
	{
		if (root->getData() == value)
		{
			delete root;
			root = nullptr;
			return;
		}
		else
		{
			cout << "Target not found in Tree";
			return;
		}
	}
	// if target is at leaf node to the right of the root
	else if (root->getRight() != nullptr && root->getRight()->isLeaf())
	{
		// if target is at root, swap with leaf
		if (root->getData() == value)
		{
			root->setData(root->getRight()->getData());
			delete root->getRight();
			root->setRight(nullptr);
			return;
		}
		// delete leaf
		else if (root->getRight()->getData() == value)
		{
			delete root->getRight();
			root->setRight(nullptr);
			return;
		}
	}
	// if target is at leaf node to the left of the root
	else if (root->getLeft() != nullptr && root->getLeft()->isLeaf())
	{
		// if target is at root, swap with leaf
		if (root->getData() == value)
		{
			root->setData(root->getLeft()->getData());
			delete root->getLeft();
			root->setLeft(nullptr);
			return;
		}
		// delete leaf
		else if (root->getLeft()->getData() == value)
		{
			delete root->getLeft();
			root->setLeft(nullptr);
			return;
		}
	}
	// if root has 2 leaf nodes
	else if (root->getLeft() != nullptr && root->getRight() != nullptr && root->getLeft()->isLeaf() && root->getRight()->isLeaf())
	{
		// if target is at root, swap with left
		if (root->getData() == value)
		{
			root->setData(root->getLeft()->getData());
			delete root->getLeft();
			root->setLeft(nullptr);
		}
		// if target is at left, delete left
		if (root->getLeft()->getData() == value)
		{
			delete root->getLeft();
			root->setLeft(nullptr);
			return;
		}
		// if target is at right, delete right
		else if (root->getRight()->getData() == value)
		{
			delete root->getRight();
			root->setRight(nullptr);
			return;
		}
		// target not found
		else
		{
			cout << "Target not found in Tree";
			return;
		}
	}
	//call private method
	else
	{
		Node<T>* tempNode = findTarget(value);
		// pass node where target is located to provate method
		remove(tempNode, value); 	
	}
}
//remove: private method
template<typename T>
void BinaryTree<T>::remove(Node<T>* rt, T value)
{
	// Base Case: Delete leaf node
	if (rt->getLeft() == nullptr && rt->getRight() == nullptr)
	{
		Node<T>* tempParent;

		// find parent of leaf node
		tempParent = findTargetPrevious(rt->getData());


		if (tempParent->getLeft() != nullptr && tempParent->getLeft()->isLeaf() && tempParent->getLeft()->getData() == rt->getData())
		{
		}
		else if (tempParent->getRight() != nullptr && tempParent->getRight()->isLeaf() && tempParent->getRight()->getData() == rt->getData())
		{
			
		}
		else if (tempParent->getLeft() != nullptr && tempParent->getLeft()->getData() == rt->getData())
		{
			tempParent = tempParent->getLeft();
		}
		else if (tempParent->getRight() != nullptr && tempParent->getRight()->getData() == rt->getData())
		{
			tempParent = tempParent->getRight();
		}

		// Delete leaf node and cut pointer to leaf node
		if (tempParent->getLeft() != nullptr && tempParent->getLeft()->getData() == rt->getData())
		{
			delete rt;
			tempParent->setLeft(nullptr);
			sort();
		}
		else if (tempParent->getRight() != nullptr && tempParent->getRight()->getData() == rt->getData())
		{
			delete rt;
			tempParent->setRight(nullptr);
			sort();
		}
		return;
	}
	// If value is apart of the leftsubtree
	if (value < root->getData())
	{
		// Recursively bubble value down left subtree until it is a leaf
		if (rt->getLeft() != nullptr)
			rt->setData(rt->getLeft()->getData());
		else if (rt->getRight() != nullptr)
			rt->setData(rt->getRight()->getData());

		if (rt->getLeft() != nullptr)
			remove(rt->getLeft(), rt->getLeft()->getData());
		else if (rt->getRight() != nullptr)
			remove(rt->getRight(), rt->getRight()->getData());
	}
	// If value is apart of the right subtree
	else if (value > root->getData())
	{
		// Recursively bubble value down right subtree until it is a leaf
		if (rt->getRight() != nullptr)
			rt->setData(rt->getRight()->getData());
		else if (rt->getLeft() != nullptr)
			rt->setData(rt->getLeft()->getData());

		if (rt->getRight() != nullptr)
			remove(rt->getRight(), rt->getRight()->getData());
		else if (rt->getLeft() != nullptr)
			remove(rt->getLeft(), rt->getLeft()->getData());
	}
	// if value is root
	else if (value == root->getData())
	{
		/*
		* Psueudocode:
		* 1. find max node in left subtree
		* 2. find min node in subtree of max node
		* 3. if parent of max node != old root, min->left = old root->left
		* 4. right child of max node = old root's right child
		* 5. old root left = nullptr, old root right = nullptr, parent->right = nullptr,
		* 6. delete old root
		* 7. max = new root
		*/

		// 1.
		Node<T>* max = findLargest(root->getLeft());
		// 2.
		Node<T>* min = findSmallest(max);

		// 3. 
		Node<T>* tempParent = findTargetPrevious(max->getData());
		if (tempParent->getData() != root->getData())
		{
			min->setLeft(root->getLeft());
		}
		// 4. 
		max->setRight(root->getRight());

		//5. 
		root->setLeft(nullptr);
		root->setRight(nullptr);
		tempParent->setRight(nullptr);
		//6. 
		delete root;

		//7. 
		root = max;

		return;
	}
}
//findTarget: public method
template<typename T>
Node<T>* BinaryTree<T>::findTargetPrevious(T target)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
		return findTargetPrevious(root, target); //call private method
}

template<typename T>
Node<T>* BinaryTree<T>::findTargetPrevious(Node<T>* rt, T target)
{
	// Base case 1: target is not in the binary tree
	if (rt == nullptr)
	{
		return nullptr;
	}
	// Base case 2: Target Node found at left node
	else if (rt->getLeft() != nullptr && rt->getLeft()->getData() == target)
	{
		return rt;
	}
	// Base case 3: Target Node found at right node
	else if (rt->getRight() != nullptr && rt->getRight()->getData() == target)
	{
		return rt;
	}
	// If target > node value, search right subtree
	else if (target > rt->getData())
	{
		return findTargetPrevious(rt->getRight(), target);
	}
	// If target < node value, search left subtree
	else if (target < rt->getData())
	{
		return findTargetPrevious(rt->getLeft(), target);
	}
}
//sort: public method
template<typename T>
void BinaryTree<T>::sort()
{
	if (root == nullptr)
		return;
	else if (root->getLeft() == nullptr && root->getRight() == nullptr)
		return;
	else
		sort(root);
}
//sort: private method
template<typename T>
void BinaryTree<T>::sort(Node<T>* rt)
{
	// Base case: finished traversing subtree
	if (rt == nullptr)
		return;

	// if root node < left child, swap
	if (rt->getLeft() != nullptr && rt->getData() < rt->getLeft()->getData())
	{
		// store root node data
		T temp = root->getData();
		rt->setData(rt->getLeft()->getData());

		Node<T>* tempNode = new Node<T>;
		tempNode = rt->getLeft();
		tempNode->setData(temp);
	}
	// if root node > right child swap
	else if (rt->getRight() != nullptr && rt->getData() > rt->getRight()->getData())
	{
		T temp = rt->getData();
		rt->setData(rt->getRight()->getData());

		Node<T>* tempNode = new Node<T>;
		tempNode = rt->getRight();
		tempNode->setData(temp);
	}

	//PreOrder Traversal of tree
	sort(rt->getLeft());
	sort(rt->getRight());

	return;
}
template<typename T>
Node<T>* BinaryTree<T>::findLargest(Node<T>* rt)
{
	// Base case: Largest node found, has no right child
	if (rt->getRight() == nullptr)
	{
		return rt;
	}
	// right child is > parent
	return findLargest(rt->getRight());
}
template<typename T>
Node<T>* BinaryTree<T>::findSmallest(Node<T>* rt)
{
	// Base case: Smallest Node found, has no left child
	if (rt->getLeft() == nullptr)
	{
		return rt;
	}
	// left child is < parent
	return findLargest(rt->getLeft());
}