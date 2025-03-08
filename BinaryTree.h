#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iomanip>
#include "Node.h"
#include "LinkedList.h"
#include <string>
#include <iostream>
using namespace std;


class BinaryTree
{
public:
	BinaryTree() : root(nullptr) {}
	~BinaryTree() { clear(root); }
	BinaryTree(const BinaryTree& rhs);
	void printIndexOfNode(string& word);
	void print();
	void Most();
	void Least();
	void addIndexToNode(string& word, int filename);
	bool find(string& word) { return findWord(root, word); }
	WordNode* search(string& k) { return search(root, k); }
	void insert(string& word, int filename);
	void sorted();
	void clear(WordNode* r);
private:
	WordNode* root;

	void inOrderTraversal(WordNode* w) //recursion function for inorder traversal
	{
		if (w == nullptr)
		{
			return;
		}
		inOrderTraversal(w->left);
		cout << w->data << " ";
		inOrderTraversal(w->right);
	}

	WordNode* copyTree(const WordNode* other) //recursive copy constructor
	{
		if (other == nullptr)
			return nullptr;
		WordNode* newNode = new WordNode(other->data, other->counter);
		newNode->left = copyTree(other->left);
		newNode->right = copyTree(other->right);
		return newNode;
	}

	WordNode* search(WordNode* r, string& k)  //returns the node that contains the word
	{
		if (r == nullptr)
			return nullptr;
		if (r->data == k)
			return r;
		if(r->data < k)
		    return search(r->right, k);
		return search(r->left, k);
	}

	bool findWord(WordNode* r, string& k) //returns true if the word is found
	{
		if (r == nullptr)
			return false;
		if (r->data == k)
			return true;
		if(r->data < k)
		    return findWord(r->right, k);
		return findWord(r->left, k);
	}
};


void BinaryTree::Most()
{
	LinkedList list;
	list.insertToLL(root);
	list.MostLL();
}

void BinaryTree::Least()
{
	LinkedList list;
	list.insertToLL(root);
	list.LeastLL();
}



void BinaryTree::print() //Inorder traversal printing
{
	inOrderTraversal(root);
}


void BinaryTree::addIndexToNode(string& word, int filename) //adds the index to the node that contains the word
{
	if (find(word))
	{
		search(word)->addIndex(filename);
		search(word)->arrange();
	}
	else
	{
		insert(word, filename);
	}
}

void BinaryTree::printIndexOfNode(string& word) //prints the index of the node that contains the word
{
	if (find(word))
	{
		search(word)->printIndex();
	}
	else
	{
		cout << "The word is not found!" << endl;

	}
}

BinaryTree::BinaryTree(const BinaryTree& rhs) //copy constructor wrapper
{
	root = copyTree(rhs.root);
}


void BinaryTree::insert(string& word, int filename)
{
	WordNode* newNode = new WordNode(word);
	newNode->addIndex(filename);
	if (root == nullptr)
	{
		root = newNode;
		return;
	}
	WordNode* w = root;

	while (w != nullptr) 
	{
		if (w->data == word) 
			return; 
		if (w->data < word) 
		{
			if (w->right == nullptr) 
			{
				w->right= newNode;
				break;
			}
			w = w->right;
		}
		else if (w->data > word) 
		{
			if (w->left == nullptr) 
			{
				w->left = newNode;
				break;
			}
			w = w->left;
		}
	}
}

void BinaryTree::clear(WordNode* r)
{
	if(r==nullptr)
		return;
	clear(r->left);
	clear(r->right);
	delete r;
	r = nullptr;
}


#endif