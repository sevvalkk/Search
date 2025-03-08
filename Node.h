#ifndef Node_H
#define Node_H

#include <string>
#include <iostream>
#include<ostream>
using namespace std;


class Index
{
public:
	int index;
	Index* nextIndex;
	Index() :index(0), nextIndex(nullptr) {}
	Index(int& ind) :index(ind), nextIndex(nullptr) {}
};

class WordNode
{
public:
	string data;
	WordNode* right;
	WordNode* left;
	Index* indexHead;
	int counter;
	void addIndex(int i);
	void printIndex() const;
	void arrange();
	WordNode() : data(""), counter(1), right(nullptr), left(nullptr), indexHead(nullptr) {}
	WordNode(const string& na) : data(na), counter(1), right(nullptr), left(nullptr), indexHead(nullptr) {}
	WordNode(const string& na, int i) : data(na), counter(i), right(nullptr), left(nullptr), indexHead(nullptr) {}
	~WordNode() { clear(); }
	WordNode* operator=(const WordNode* w);
	bool operator==(const WordNode& w);
	void clear();
};

void WordNode::addIndex(int i)
{
	Index* newIndex = new Index(i);
	if (indexHead == nullptr)
	{
		indexHead = newIndex;
	}
	else
	{
		Index* w = indexHead;
		while (w->nextIndex != nullptr)
		{
			w = w->nextIndex;
		}
		this->counter++;
		w->nextIndex = newIndex;
	}
}

void WordNode::arrange()
{
	if (indexHead == nullptr || indexHead->nextIndex == nullptr)
	{
		return;
	}
	Index* walk = indexHead;
	while (walk->nextIndex != nullptr)
	{
		if (walk->index == walk->nextIndex->index)
		{
			Index* p = walk->nextIndex;
			walk->nextIndex = p->nextIndex;
			delete p;
		}
		else
			walk = walk->nextIndex;
	}
}

void WordNode::printIndex() const
{
	cout << "----------------------------------" << endl;
	cout << "|              Term              |" << endl;
	cout << "----------------------------------" << endl;
	cout << data << " (" << counter << " times occured)" << endl;
	cout << "----------------------------------" << endl;
	cout << "|           File Names           |" << endl;
	cout << "----------------------------------" << endl;
	Index* walk = indexHead;
	while (walk->nextIndex != nullptr)
	{
		cout << walk->index << ", ";
		walk = walk->nextIndex;
	}
	cout << walk->index;
	cout << endl;
}

WordNode* WordNode::operator=(const WordNode* w)
{
	if (*this == *w)
		return this;
	data = w->data;
	counter = w->counter;
	indexHead = w->indexHead;
	return this;
}

bool WordNode::operator==(const WordNode& w)
{
	if (data == w.data && counter == w.counter)
		return true;
	return false;
}

void WordNode::clear()
{
	Index* walk = indexHead;
	Index* temp;
	while (walk != nullptr)
	{
		temp = walk;
		walk = walk->nextIndex;
		delete temp;
	}
	indexHead = nullptr;
}


#endif