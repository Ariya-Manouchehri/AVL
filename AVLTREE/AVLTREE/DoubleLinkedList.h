/*****************************************
* Shahrood User ID:  -
* Submitted for Data Structure Course
* Department of Computer Engineering and IT
* Shahrood University of Technology
*
* By submitting this file, I affirm that
* I am the author of all modifications to
* the provided code.
*****************************************/

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include"DoubleNode.h"
#include <iostream>
#include "exception.h"
template<typename Type>
class DoubleLinkedList {
public:
	DoubleLinkedList();
	DoubleLinkedList(DoubleLinkedList<Type> const&);
	~DoubleLinkedList();

	// Accessors

	int size() const;
	bool empty() const;

	Type front() const;
	Type back() const;

	DoubleNode<Type>* begin() const;
	DoubleNode<Type>* end() const;

	DoubleNode<Type>* find(int const&) const;
	Type count(Type) const;

	// Mutators

	void swap(DoubleLinkedList<Type>&);

	void pushFront(Type);
	void pushBack(Type);

	Type popFront();
	Type popBack();

	int erase(Type);
	int listsize = 0;
private:
	int listSize;
	DoubleNode<Type>* listHead;
	DoubleNode<Type>* listTail;
	DoubleNode<Type>* newnode;
	DoubleNode<Type>* node;


	// List any additional private member functions you author here
	// Friends

	//friend std::ostream& operator<<(std::ostream&, DoubleLinkedList const&);
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////


/*This function is the constructor and sets the default values ​​for it*/
template<typename Type>
DoubleLinkedList<Type>::DoubleLinkedList() :
	// Updated the initialization list here
	listHead(nullptr),
	listTail(nullptr),
	listSize(0)
{
	// Enter your implementation here
}


/*this function is copy constructor give a input of the type doublelinklist and with a loop
pushback To the current list*/
template<typename Type>
DoubleLinkedList<Type>::DoubleLinkedList(DoubleLinkedList const& list) :
	// Updated the initialization list here
	listHead(nullptr),
	listTail(nullptr),
	listSize(0)
{
	// Enter your implementation here
	for (DoubleNode<Type>* ptr = list.begin(); ptr != nullptr; ptr = ptr->next()) {
		this->pushBack(ptr->value());
	}


}


template<typename Type>
DoubleLinkedList<Type>::~DoubleLinkedList() {
	// Enter your implementation here
}


/*this function return listsize*/
template<typename Type>
int DoubleLinkedList<Type>::size() const {
	return listSize;
}


/*this function chcked list is empty or not if empty return true else return false*/
template<typename Type>
bool DoubleLinkedList<Type>::empty() const {
	return begin() == nullptr;
}


/*this function is point to headlist if listhead is null trow exteption else return listhead value*/
template<typename Type>
Type DoubleLinkedList<Type>::front() const {
	if (begin() == nullptr) {
		throw Underflow();
	}

	return begin()->value(); // This returns the default value
}


/*this function is point to taillist if listtail is null trow exteption else return listtail value*/
template<typename Type>
Type DoubleLinkedList<Type>::back() const {
	if (end() == nullptr) {
		throw Underflow();
	}

	return end()->value(); // This returns the default value
}


/*this function is return listhead*/
template<typename Type>
DoubleNode<Type>* DoubleLinkedList<Type>::begin() const {
	// Enter your implementation here

	return listHead;
}


/*this function is return listtail*/
template<typename Type>
DoubleNode<Type>* DoubleLinkedList<Type>::end() const {
	// Enter your implementation here

	return listTail;
}


/*this function is give a input of the type int and with a loop
checked it if (value == nodevalue) return nodeaddress else return null*/
template<typename Type>
DoubleNode<Type>* DoubleLinkedList<Type>::find(int const& value) const {
	for (auto ptr = this->begin(); ptr != nullptr; ptr = ptr->next()) {
		if (ptr->nodeValue == value) {
			return ptr;
		}
	}
	return nullptr;
}


/*this function is give a input of the type int and with a loop
checked it. if (value == nodevalue)increase size and finally return size*/
template<typename Type>
Type DoubleLinkedList<Type>::count(Type value) const {
	DoubleNode<Type>* node = listHead;
	Type size = 0;
	while (node != nullptr)
	{
		if (node->nodeValue == value) {
			size++;
		}
		node = node->next();
	}
	delete node;
	return size;
}


/*this function is give a input of the type doublelinklist
and moves it with the current object*/
template<typename Type>
void DoubleLinkedList<Type>::swap(DoubleLinkedList& list) {
	DoubleNode<Type>* temp1 = this->listHead;
	this->listHead = list.listHead;
	list.listHead = temp1;

	DoubleNode<Type>* temp2 = this->listTail;
	this->listTail = list.listTail;
	list.listTail = temp2;

	Type length = this->listSize;
	this->listSize = list.listSize;
	list.listSize = length;
}


/*this function is give a input of the type int
and check list. if list is empty sets listhead and listtail with it
else pushfront To the bottom of the list*/
template<typename Type>
void DoubleLinkedList<Type>::pushFront(Type value) {
	if (!empty()) {
		listHead = new DoubleNode<Type>(value, nullptr, begin());
		(listHead->nextNode)->previousNode = listHead;
	}
	if (empty()) {
		listHead = new DoubleNode<Type>(value, nullptr, nullptr);
		listTail = listHead;
	}
	listSize++;
}


/*this function is give a input of the type int
and check list. if list is empty sets listhead and listtail with it
else pushback To the top of the list*/
template<typename Type>
void DoubleLinkedList<Type>::pushBack(Type value) {
	if (!empty())
	{
		listTail = new DoubleNode<Type>(value, listTail, nullptr);
		(listTail->previousNode)->nextNode = listTail;
	}
	if (empty()) {
		pushFront(value);
		return;
	}
	listSize++;
}


/*this function just delete From the beginning of the list
if list is empty trow exteption  else if not empty but have one node
listhead and listtail is sets null else delete The first node*/
template<typename Type>
Type DoubleLinkedList<Type>::popFront() {
	Type f = listHead->nodeValue;
	if (empty()) {
		throw Underflow();
	}
	if (!empty() && listSize == 1) {
		listHead = nullptr;
		listTail = nullptr;
	}
	if (!empty()) {
		listHead = listHead->next();
		listHead->previousNode = nullptr;
	}
	listSize--;
	return f;
}


/*this function just delete From the bottom of the list
if list is empty trow exteption  else if not empty but have one node
listhead and listtail is sets null else delete The last node*/
template<typename Type>
Type DoubleLinkedList<Type>::popBack() {
	Type b = listTail->nodeValue;
	if (empty()) {
		throw Underflow();
	}
	if (!empty() && listSize == 1) {
		listHead = nullptr;
		listTail = nullptr;
	}
	if (!empty()) {
		listTail = listTail->previous();
		listTail->nextNode = nullptr;
	}
	listSize--;
	return b;
}


/*this function erase node that equal with input
In this way if (nodevalue ==input) if node is equal listhead*/
template<typename Type>
int DoubleLinkedList<Type>::erase(Type value) {
	DoubleNode<Type>* node = listHead;
	int size = 0;
	while (node != nullptr)
	{
		if (node->nodeValue == value) {
			if (node != listHead && node != listTail) {
				((node->previousNode)->nextNode) = (node->nextNode);
				newnode = node->nextNode;
				DoubleNode<Type>* n = (node->previousNode);
				delete node;
				node = newnode;
				(node->previousNode) = n;
				size++;
				listSize--;
				continue;
			}
			if (node == listHead) {
				newnode = node->nextNode;
				delete node;
				node = newnode;
				node->previousNode = nullptr;
				listHead = node;
				size++;
				listSize--;
				continue;
			}
			if (node == listTail) {
				((node->previousNode)->nextNode) = nullptr;
				listTail = node->previousNode;
				listTail->nextNode = nullptr;
				delete node;
				node = nullptr;
				size++;
				listSize--;
				continue;
			}
		}
		node = node->next();
	}
	return size;
}


/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

/*std::ostream& operator<<(std::ostream& out, DoubleLinkedList const& list) {
	out << "head";

	// print list from start to end
	for (auto* ptr = list.begin(); ptr != nullptr; ptr = ptr->next()) {
		out << "->" << ptr->value();
	}
	out << "->0" << std::endl << "tail";

	// print list from end to start
	for (auto ptr = list.end(); ptr != nullptr; ptr = ptr->previous()) {
		out << "->" << ptr->value();
	}
	out << "->0";

	return out;
}*/

#endif
