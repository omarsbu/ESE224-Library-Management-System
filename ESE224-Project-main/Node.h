#ifndef NODE_H
#define NODE_H
//#include "book.h"
#include "bookcopy.h"
#include "user.h"

template<class T>
class Node
{
private:
	T data;
	Node* left;
	Node* right;
public:
	Node();

	Node(T value);

	Node* getLeft() const;

	Node* getRight() const;

	T getData() const;

	void setLeft(Node*);

	void setRight(Node*);

	void setData(T value);

	void incNodeLeft(Node*& node);

	void incNodeRight(Node*& node);

	bool isLeaf();
};

using namespace std;


template<typename T>
void Node<T>::incNodeRight(Node*& node)
{
	node = node->right;
}
template<typename T>
void Node<T>::incNodeLeft(Node*& node)
{
	node = node->left;
}

template<class T>
Node<T>::Node() : data(), left(nullptr), right(nullptr)
{
}
template<class T>
Node<T>::Node(T value) : data(value), left(nullptr), right(nullptr)
{
}
template<class T>
Node<T>* Node<T>::getLeft() const
{
	return left;
}
template<class T>
Node<T>* Node<T>::getRight() const
{
	return right;
}
template<class T>
T Node<T>::getData() const
{
	return data;
}
template<class T>
void Node<T>::setLeft(Node<T>* l)
{
	left = l;
}
template<class T>
void Node<T>::setRight(Node<T>* r)
{
	right = r;
}
template<class T>
void Node<T>::setData(T value)
{
	data = value;
}
template<class T>
bool Node<T>::isLeaf()
{;	
	if (left == nullptr && right == nullptr)
		return true;
	else
		return false;
}
#endif