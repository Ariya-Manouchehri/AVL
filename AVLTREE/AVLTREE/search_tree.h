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

#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H
#include"DoubleLinkedList.h"
#include<iostream>
#include<algorithm>
#include<assert.h>
#include "exception.h"
using namespace std;

class SearchTree {
private:
	class Node {
	public:
		int nodeValue;
		int treeHeight;
		// The left and right sub-trees
		Node* leftTree;
		Node* rightTree;
		// Hint as to how you can create your iterator
		// Point to the previous and next nodes in linear order
		Node* previousNode;
		Node* nextNode;
		Node* parent;
		// Member functions
		Node(int const&);

		void updateHeight();

		int height() const;
		bool isLeaf() const;
		Node* front();
		Node* back();
		Node* check();
		Node* check2(Node*);
		void Ordering();
		int Ordering2();
		void changeheight1();
		void changeheight2();
		Node* find(int const&);
		void clear();
		void Rotation1();
		void Rotation2();
		void Rotation3();
		void Rotation4();
		void parentcheck();
		// YOU CAN change the return type if these two functions if you want to!
		bool insert(int const&, Node*& toThis);
		bool erase(int const&, Node*& toThis);
	};

	Node* rootNode;
	int treeSize;

	// Hint as to how to start your linked list of the nodes in order 
	Node* frontSentinel;
	Node* backSentinel;

public:
	class Iterator {
	private:
		SearchTree* containingTree;
		Node* currentNode;
		bool isEnd;

		// The constructor is private so that only the search tree can create an iterator
		Iterator(SearchTree* tree, Node* startingNode);

	public:
		// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
		int operator*() const;
		Iterator& operator++();
		Iterator& operator--();
		bool operator==(Iterator const& rhs) const;
		bool operator!=(Iterator const& rhs) const;

		// Make the search tree a friend so that it can call the constructor
		friend class SearchTree;
	};

	// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
	SearchTree();
	~SearchTree();

	bool empty() const;
	int size() const;
	int height() const;
	void printDFSWithHeights(ofstream&) const;

	int front() const;
	int back() const;

	Iterator begin();
	Iterator end();
	Iterator rbegin();
	Iterator rend();
	Iterator find(int const&);
	void clear();
	bool insert(int const&);
	bool erase(int const&);
	void rootChange();
};

//////////////////////////////////////////////////////////////////////
//                Search Tree Public Member Functions               //
//////////////////////////////////////////////////////////////////////


/*This function is the constructor and sets the default values ​​for it*/
SearchTree::SearchTree() :
	rootNode(nullptr),
	treeSize(0),
	frontSentinel(new SearchTree::Node(0)),
	backSentinel(new SearchTree::Node(0)) {
	frontSentinel->nextNode = backSentinel;
	backSentinel->previousNode = frontSentinel;
}


SearchTree::~SearchTree() {
	clear();
}


/*this function is checked tree if empty return true else return false*/
bool SearchTree::empty() const {
	return (rootNode == nullptr);
}


/*this function return treesize*/
int SearchTree::size() const {
	return treeSize;
}


/*this function return treeheight*/
int SearchTree::height() const {
	return rootNode->height();
}


/*at first we make doublelinkedlist and push rootnode at that and then Each of the variables
are push and pop while doublelinkedlist getting empty this function print node and heightnode*/
void SearchTree::printDFSWithHeights(ofstream& out) const {
	DoubleLinkedList<Node*> DFS = DoubleLinkedList<Node*>();
	DFS.pushBack(rootNode);
	out << "START->";
	if (rootNode != nullptr) {
		while (!DFS.empty())
		{
			Node* currnode = DFS.popBack();
			out << "[" << currnode->nodeValue << ", " << currnode->height() << "]" << "->";
			if (currnode->rightTree != nullptr) {
				auto child = currnode->rightTree;
				DFS.pushBack(child);
			}
			if (currnode->leftTree != nullptr) {
				auto child = currnode->leftTree;
				DFS.pushBack(child);
			}
		}
	}
	out << "END" << endl;
}


/*in this function we check Input phrase is rootnode or not if that parent is not
null it is not rootnode and we checked it parent and this Function is Repeat while Let his father be empty*/
void SearchTree::rootChange() {
	while (rootNode->parent != nullptr) {
		rootNode = rootNode->parent;
	}
}


/*this function return The lowest tree amount*/
int SearchTree::front() const {
	if (empty()) {
		throw Underflow();
	}
	return rootNode->front()->nodeValue;
}


/*this function return The Maximum amount of tree*/
int SearchTree::back() const {
	if (empty()) {
		throw Underflow();
	}

	return rootNode->back()->nodeValue;
}


/*this function return The amount of the beginning doublelinkedlist*/
SearchTree::Iterator SearchTree::begin() {
	return empty() ? Iterator(this, backSentinel) : Iterator(this, rootNode->front());
}


/*this function return The The final value of doublelinkedlist*/
SearchTree::Iterator SearchTree::end() {
	return Iterator(this, backSentinel);
}


/*this function return The The final value of doublelinkedlist*/
SearchTree::Iterator SearchTree::rbegin() {
	return empty() ? Iterator(this, frontSentinel) : Iterator(this, rootNode->back());
}


/*this function return The amount of the beginning doublelinkedlist*/
SearchTree::Iterator SearchTree::rend() {
	return Iterator(this, frontSentinel);
}

SearchTree::Iterator SearchTree::find(int const& val) {
	if (empty()) {
		return Iterator(this, backSentinel);
	}

	SearchTree::Node* searchResult = rootNode->find(val);

	if (searchResult == nullptr) {
		return Iterator(this, backSentinel);
	}
	else {
		return Iterator(this, searchResult);
	}
}


/*we clear tree in this function*/
void SearchTree::clear() {
	if (!empty()) {
		rootNode->clear();
		rootNode = nullptr;
		treeSize = 0;
	}

	// Reinitialize the sentinels
	frontSentinel->nextNode = backSentinel;
	backSentinel->previousNode = frontSentinel;
}


/*we insert new node to the tree if tree is empty consider that rootnode 
else insert it to root children and At each stage we check rootnode and update treeheight*/
bool SearchTree::insert(int const& val) {
	if (empty()) {
		rootNode = new SearchTree::Node(val);
		treeSize = 1;
		return true;
	}
	else if (rootNode->insert(val, rootNode)) {
		rootChange();
		rootNode->changeheight1();
		++treeSize;
		return true;
	}
	else {
		return false;
	}
}


/*we remove node to the tree is equaly with val
remove it and At each stage we check rootnode and update treeheight and lessen treesize*/
bool SearchTree::erase(int const& val) {
	if (!empty() && rootNode->erase(val, rootNode)) {
		rootChange();
		rootNode->changeheight1();
		--treeSize;
		return true;
	}
	else {
		return false;
	}
}

//////////////////////////////////////////////////////////////////////
//                   Node Public Member Functions                   //
//////////////////////////////////////////////////////////////////////


/*This function is the constructor and sets the default values ​​for it*/
SearchTree::Node::Node(int const& val) :
	nodeValue(val),
	leftTree(nullptr),
	rightTree(nullptr),
	parent(nullptr),
	nextNode(nullptr),
	previousNode(nullptr),
	treeHeight(0) {
	// does nothing
}


/*this function check left and right height and give maximm
Between values*/
void SearchTree::Node::updateHeight() {
	treeHeight = max(leftTree->height(), rightTree->height()) + 1;
}


/*in this function we check and update treeheight*/
void SearchTree::Node::changeheight1() {
	if (this->rightTree != nullptr) {
		this->rightTree->changeheight1();
	}
	this->changeheight2();
	if (this->leftTree != nullptr) {
		this->leftTree->changeheight1();
	}
	this->changeheight2();
}


/*in this function we check and update treeheight*/
void SearchTree::Node::changeheight2() {
	this->updateHeight();
	if (this->parent != nullptr) {
		this->parent->changeheight2();
	}
}

/*this function we checked tree if leftheight and rightheigh Their differences
More than one we need Rotation so we return that node*/
SearchTree::Node* SearchTree::Node::check() {
	int leftheight = this->leftTree->height();
	leftheight += 1;
	int rightheight = this->rightTree->height();
	rightheight += 1;
	int check = leftheight - rightheight;
	if (check < 0) {
		check = -check;
	}
	if (check > 1) {
		return this;
	}
	if (this->parent != nullptr) {
		this->parent->check();
	}
}


/*this function we checked tree if leftheight and rightheigh Their differences
More than one we need Rotation so we return that node*/
SearchTree::Node* SearchTree::Node::check2(Node* toThis) {
	if (this != nullptr) {
		return nullptr;
	}
	if (this == toThis) {
		Node* left = this->parent->leftTree;
		Node* right = this->parent->rightTree;
		if (left == this) {
			this->parent->leftTree = nullptr;
		}
		if (right == this) {
			this->parent->rightTree = nullptr;
		}
		this->parent->changeheight2();
		this->parent->check2(this);
	}
	int leftheight = this->leftTree->height();
	leftheight += 1;
	int rightheight = this->rightTree->height();
	rightheight += 1;
	int check = leftheight - rightheight;
	if (check < 0) {
		check = -check;
	}
	if (check > 1) {
		return this;
	}
	if (this->parent != nullptr) {
		this->parent->check2(this);
	}
}


/*this function The operation rotates right to right*/
void SearchTree::Node::Rotation1() {
	Node* n = this->rightTree->leftTree;
	this->rightTree->parent = this->parent;
	if (this->parent != nullptr) {
		Node* left = this->parent->leftTree;
		Node* right = this->parent->rightTree;
		if (right == this) {
			this->parent->rightTree = this->rightTree;
		}
		if (left == this) {
			this->parent->leftTree = this->rightTree;
		}
	}
	this->parent = this->rightTree;
	this->rightTree = n;
	this->parent->leftTree = this;
}


/*this function The operation rotates left to left*/
void SearchTree::Node::Rotation2() {
	Node* m = this->leftTree->rightTree;
	this->leftTree->parent = this->parent;
	if (this->parent != nullptr) {
		Node* left = this->parent->leftTree;
		Node* right = this->parent->rightTree;
		if (right == this) {
			this->parent->rightTree = this->leftTree;
		}
		if (left == this) {
			this->parent->leftTree = this->leftTree;
		}
	}
	this->parent = this->leftTree;
	this->leftTree = m;
	this->parent->rightTree = this;
}


/*this function The operation rotates left to right*/
void SearchTree::Node::Rotation3() {
	Node* a = this->leftTree->rightTree->leftTree;
	Node* b = this->leftTree->rightTree->rightTree;
	this->leftTree->rightTree->parent = this->parent;
	if (this->parent != nullptr) {
		Node* left = this->parent->leftTree;
		Node* right = this->parent->rightTree;
		if (right == this) {
			this->parent->rightTree = this->leftTree->rightTree;
		}
		if (left == this) {
			this->parent->leftTree = this->leftTree->rightTree;
		}
	}
	this->parent = this->leftTree->rightTree;
	this->parent->rightTree = this;
	this->parent->leftTree = this->leftTree;
	this->leftTree->parent = this->parent;
	this->leftTree = b;
	this->parent->leftTree->rightTree = a;
}


/*this function The operation rotates right to left*/
void SearchTree::Node::Rotation4() {
	Node* h = this->rightTree->leftTree->leftTree;
	Node* k = this->rightTree->leftTree->rightTree;
	this->rightTree->leftTree->parent = this->parent;
	if (this->parent != nullptr) {
		Node* left = this->parent->leftTree;
		Node* right = this->parent->rightTree;
		if (right == this) {
			this->parent->rightTree = this->rightTree->leftTree;
		}
		if (left == this) {
			this->parent->leftTree = this->rightTree->leftTree;
		}
	}
	this->parent->leftTree = this;
	this->parent->rightTree = this->rightTree;
	this->rightTree->parent = this->parent;
	this->rightTree = h;
	this->parent->rightTree->leftTree = k;
}


/*in this function we ordaring tree to avl tree we check left and right tree
Each one was more we consider it first Rotation and check again Intended node
Each one was more leftheight or rightheigh and then we chose The rotation that is more appropriate*/
void SearchTree::Node::Ordering() {
	if (this == nullptr) {
		return;
	}
	int name1 = -1;
	int name2 = -1;
	int left = 0;
	int right = 0;
	if (this->leftTree != nullptr) {
		left = this->leftTree->height();
		left += 1;
	}
	if (this->rightTree != nullptr) {
		right = this->rightTree->height();
		right += 1;
	}
	int check = left - right;
	if (check < 0) {
		check = -check;
	}
	if (check > 1) {
		if (left > right) {
			name1 = 0;
			name2 = this->leftTree->Ordering2();
		}
		if (right > left) {
			name1 = 1;
			name2 = this->rightTree->Ordering2();
		}
		if (name1 == 1 && name2 == 1) {
			this->Rotation1();	
		}
		if (name1 == 0 && name2 == 0) {
			this->Rotation2();
		}
		if (name1 == 0 && name2 == 1) {
			this->Rotation3();
		}
		if (name1 == 1 && name2 == 0) {
			this->Rotation4();
		}
	}
}
int SearchTree::Node::Ordering2() {
	int leftorder = this->leftTree->height();
	leftorder += 1;
	int rightoreder = this->rightTree->height();
	rightoreder += 1;
	if (leftorder > rightoreder) {
		return 0;
	}
	if (rightoreder > leftorder) {
		return 1;
	}
	return -1;
}


/*this function is return tree height*/
int SearchTree::Node::height() const {
	return (this == nullptr) ? -1 : treeHeight;
}


/*this function check input node is leaf or note*/
bool SearchTree::Node::isLeaf() const {
	return ((leftTree == nullptr) && (rightTree == nullptr));
}


/*this function return The lowest tree amount*/
SearchTree::Node* SearchTree::Node::front() {
	return (leftTree == nullptr) ? this : leftTree->front();
}


/*this function return The Maximum amount of tree*/
SearchTree::Node* SearchTree::Node::back() {
	return (rightTree == nullptr) ? this : rightTree->back();
}


/*this function we return node that Its value is equal to the tree node*/
SearchTree::Node* SearchTree::Node::find(int const& val) {
	if (val == nodeValue) {
		return this;
	}
	else if (val < nodeValue) {
		return (leftTree == nullptr) ? nullptr : leftTree->find(val);
	}
	else {
		return (rightTree == nullptr) ? nullptr : rightTree->find(val);
	}
}


/*we are clear tree in this function*/
void SearchTree::Node::clear() {
	if (leftTree != nullptr) {
		leftTree->clear();
	}

	if (rightTree != nullptr) {
		rightTree->clear();
	}

	delete this;
}


/*in this function we check tree and Put the node in the right place of the tree
And at each stage we check that our tree loses its height*/
bool SearchTree::Node::insert(int const& val, SearchTree::Node*& toThis) {
	if (val < nodeValue) {
		if (leftTree == nullptr) {
			leftTree = new SearchTree::Node(val);
			leftTree->nextNode = toThis;
			leftTree->previousNode = toThis->previousNode;
			if (toThis->previousNode != nullptr) {
				toThis->previousNode->nextNode = leftTree;
			}
			toThis->previousNode = leftTree;
			leftTree->parent = this;
			leftTree->changeheight2();
			leftTree->check()->Ordering();
			updateHeight();
			return true;
		}
		else {
			if (leftTree->insert(val, leftTree)) {
				updateHeight();
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (val > nodeValue) {
		if (rightTree == nullptr) {
			rightTree = new SearchTree::Node(val);
			rightTree->previousNode = toThis;
			rightTree->nextNode = toThis->nextNode;
			if (toThis->nextNode != nullptr) {
				toThis->nextNode->previousNode = rightTree;
			}
			toThis->nextNode = rightTree;
			rightTree->parent = this;
			rightTree->changeheight2();
			rightTree->check()->Ordering();
			updateHeight();

			return true;
		}
		else {
			if (rightTree->insert(val, rightTree)) {
				updateHeight();
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}
}


/*in this function we check tree and erase Remove the desired node from the tree
And at each stage we check that our tree loses its height*/
bool SearchTree::Node::erase(int const& val, SearchTree::Node*& toThis) {
	if (val < nodeValue) {
		if (leftTree == nullptr) {
			return false;
		}
		else {
			if (leftTree->erase(val, leftTree)) {
				updateHeight();
				return true;
			}

			return false;
		}
	}
	else if (val > nodeValue) {
		if (rightTree == nullptr) {
			return false;
		}
		else {
			if (rightTree->erase(val, rightTree)) {
				updateHeight();
				return true;
			}

			return false;
		}
	}
	else {
		assert(val == nodeValue);
		if (isLeaf()) {
			if (toThis->previousNode != nullptr) {
				toThis->previousNode->nextNode = toThis->nextNode;
			}
			if (toThis->nextNode != nullptr) {
				toThis->nextNode->previousNode = toThis->previousNode;
			}
			toThis->check2(toThis)->Ordering();
			toThis = nullptr;
			delete this;
		}
		else if (leftTree == nullptr) {
			if (toThis->previousNode != nullptr) {
				toThis->previousNode->nextNode = toThis->nextNode;
			}
			if (toThis->nextNode != nullptr) {
				toThis->nextNode->previousNode = toThis->previousNode;
			}
			toThis = rightTree;
			toThis->rightTree = nullptr;
			toThis->parent = this->parent;
			toThis->parentcheck();
			toThis->changeheight2();
			toThis->check()->Ordering();
			delete this;
		}
		else if (rightTree == nullptr) {
			if (toThis->previousNode != nullptr) {
				toThis->previousNode->nextNode = toThis->nextNode;
			}
			if (toThis->nextNode != nullptr) {
				toThis->nextNode->previousNode = toThis->previousNode;
			}
			toThis = leftTree;
			toThis->leftTree = nullptr;
			toThis->parent = this->parent;
			toThis->parentcheck();
			toThis->changeheight2();
			toThis->check()->Ordering();
			delete this;
		}
		else {
			nodeValue = rightTree->front()->nodeValue;
			rightTree->erase(nodeValue, rightTree);
			updateHeight();
		}
		return true;
	}
}


void SearchTree::Node::parentcheck() {
	Node* left = this->parent->leftTree;
	Node* right = this->parent->rightTree;
	if (left == this) {
		this->parent->leftTree = this;
	}
	if (right == this) {
		this->parent->rightTree = this;
	}
}

//////////////////////////////////////////////////////////////////////
//                   Iterator Private Constructor                   //
//////////////////////////////////////////////////////////////////////


/*This function is the constructor and sets the default values ​​for it*/
SearchTree::Iterator::Iterator(SearchTree* tree, SearchTree::Node* startingNode) :
	containingTree(tree),
	currentNode(startingNode) {
	// This is done for you...
	// Does nothing...
}

//////////////////////////////////////////////////////////////////////
//                 Iterator Public Member Functions                 //
//////////////////////////////////////////////////////////////////////

int SearchTree::Iterator::operator*() const {
	// This is done for you...
	return currentNode->nodeValue;
}

SearchTree::Iterator& SearchTree::Iterator::operator++() {
	if (currentNode == nullptr) {
		currentNode = containingTree->end().currentNode;
	}
	else if (currentNode->nextNode == nullptr) {
		currentNode = containingTree->end().currentNode;
	}
	else {
		currentNode = currentNode->nextNode;
	}
	return *this;
}

SearchTree::Iterator& SearchTree::Iterator::operator--() {
	if (currentNode == nullptr) {
		currentNode = containingTree->begin().currentNode;
	}
	if (currentNode->previousNode == nullptr) {
		currentNode = containingTree->begin().currentNode;
	}
	else {
		currentNode = currentNode->previousNode;
	}
	return *this;
}

bool SearchTree::Iterator::operator==(SearchTree::Iterator const& rhs) const {
	// This is done for you...
	return (currentNode == rhs.currentNode);
}

bool SearchTree::Iterator::operator!=(SearchTree::Iterator const& rhs) const {
	// This is done for you...
	return (currentNode != rhs.currentNode);
}

#endif
