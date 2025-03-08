#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iomanip>
#include <stack>
#include <string>
#include <iostream>
#include <queue>
#include "Node.h"
using namespace std;

class Node
{
public:
	string data;
	Node* next;
	Index* indexH;
	int counter;
	void addIndex(int i);
	void printIndex() const;
	void clear();
	Node() :next(nullptr), counter(1), indexH(nullptr) {}
	Node(const string& na) : data(na), next(nullptr), counter(1), indexH(nullptr) {}
	Node(const string& na, int i) : data(na), next(nullptr), counter(i), indexH(nullptr) {}
	~Node() { clear(); }
	void print()const {
		cout << data << "->";
	}
};

void Node::addIndex(int i)
{
	Index* newIndex = new Index(i);
	if (indexH == nullptr)
	{
		indexH = newIndex;
	}
	else
	{
		Index* w = indexH;
		while (w->nextIndex != nullptr)
		{
			w = w->nextIndex;
		}
		this->counter++;
		w->nextIndex = newIndex;
	}
}


void Node::printIndex() const
{
	cout << "--------------------------" << endl;
	cout << "|          Term          |" << endl;
	cout << "--------------------------" << endl;
	cout << data << " " << counter << endl;
	cout << "--------------------------" << endl;
	cout << "|       File Names       |" << endl;
	cout << "--------------------------" << endl;
	Index* walk = indexH;
	while (walk->nextIndex != nullptr)
	{
		cout << walk->index << ", ";
		walk = walk->nextIndex;
	}
	cout << walk->index;
	cout << endl;
}

void Node::clear()
{
	Index* walk = indexH;
	Index* temp;
	while (walk != nullptr)
	{
		temp = walk;
		walk = walk->nextIndex;
		delete temp;
	}
}


class LinkedList
{
public:
	LinkedList() : head ( nullptr ) {}
	~LinkedList() { clear(); }
	bool find(string& word);
	void clear();
	void print();
	void MostLL();
	void LeastLL();
    void add(string&word);
	void addIndexToNode(string& word, int filename);
	Node* search(string& word);
    void insertToLL(WordNode* root);
    Node* getHead()const {return head;}
private:
	Node* head;
};


void LinkedList::MostLL() //prints the most frequent 10 words
{
	cout << "_________________________________" << endl;
	cout << "|    The most frequent words    |" << endl;
	cout << "|-------------------------------|" << endl;

	vector<int> counts;
	LinkedList words;
	bool first = false;
	for (int i = 0; i < 10; i++)
	{
		Node* w = head;
		string data;
		int counter = 0;
		while (w != nullptr)
		{
			if (first == false && w->counter > counter)
			{
				data = w->data;
				counter = w->counter;
			}
			else if (first == true && w->counter >= counter && w->counter < counts[i-1])
			{
				if (!words.find(w->data))
				{
					data = w->data;
					counter = w->counter;
				}
			}
			w = w->next;
		}
		counts.push_back(counter);
		words.add(data);
		first = true;

		cout << "|" << setw(15) << data << " : " << setw(6) << to_string(counts[i]) << " times |" << endl;
		
	}
	cout << "---------------------------------" << endl;
}

void LinkedList::LeastLL() //prints the least frequent 10 words
{
	cout << "_________________________________" << endl;
	cout << "|    The least frequent words   |" << endl;
	cout << "|-------------------------------|" << endl;

	vector<int> counts;
	LinkedList words;
	bool first = false;
	for (int i = 0; i < 10; i++)
	{
		Node* w = head;
		string data;
		int counter = 10;
		while (w != nullptr)
		{
			if (first == false && w->counter < counter)
			{
				data = w->data;
				counter = w->counter;
			}
			else if (first == true && w->counter < counter && w->counter >= counts[i-1])
			{
				if (!words.find(w->data))
				{
					data = w->data;
					counter = w->counter;
				}
			}
			w = w->next;
		}
		counts.push_back(counter);
		words.add(data);
		first = true;

		cout << "|" << setw(15) << data << " : " << setw(6) << to_string(counts[i]) << " times |" << endl;

	}
	cout << "---------------------------------" << endl;
}


void LinkedList::clear()
{
	while (head != nullptr)
	{
		Node* p = head;
		head = head->next;
		delete p;
	}
}

bool LinkedList::find(string& word) //returns true if the word is found
{
	Node* w = head;
	if (w == nullptr)
	{
		return false;
	}
	while (w != nullptr)
	{
		if (w->data == word)
		{
			return true;
		}
		w = w->next;
	}
	return false;
}
void LinkedList::add(string& word) //inserts the word to the linked list
{
	Node* newNode = new Node(word);
	if (head == nullptr)
	{
		head = newNode;
        newNode->next = nullptr;
	}
	else
	{
		Node* w = head;
		while (w->next != nullptr)
		{
			w = w->next;
		}
		w->next = newNode;
		newNode->next = nullptr;
	}
	
}

void LinkedList::insertToLL(WordNode* root) //inserting binary tree into linked list by Breadth First Traversal
{
	if(root!=nullptr)
	{
		queue<WordNode*> q;
		q.push(root);
		Node* w = head;
		while(!q.empty())
		{
			WordNode*t = q.front();
			q.pop();
			Node* newNode = new Node(t->data, t->counter);
			if(head==nullptr)
			{
				head = newNode;
				w = head;
			}
			else
			{
				w->next = newNode;
				w=w->next;
			}
			if(t->left!=nullptr)
			    q.push(t->left);
			if(t->right!=nullptr)
			    q.push(t->right);
		}
	}
}

#endif