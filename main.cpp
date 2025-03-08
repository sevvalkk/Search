#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>
#define MAX 9598 //Number of files

#include "BinaryTree.h"
using namespace std;

void lower(string& str)
{
	for (char& s : str)
		s = tolower(s);
}


void load(BinaryTree& tree)
{
	string input, line;
	ifstream file;
	cout << "Loading..." << endl;

	for (int c = 1; c <= MAX; c++)
	{
		file.open("AllDocs/" + to_string(c) + ".txt", ios::in);
		if (!file.is_open())
		{
			cout << "Error: File " << to_string(c) + ".txt" << " not found!" << endl;
			return;
		}
		char x;
		while (!file.eof())
		{
			x = file.get();
			while (isalpha(x))
			{
				input += tolower(x);
				x = file.get();
			}
			if (input.length() > 0)
			{
				if (tree.find(input) == false)
					tree.insert(input, c);
				else
					tree.addIndexToNode(input, c);
			}
			input.clear();
		}
		file.close();

		if (c % 500 == 0)
			cout << " " << c << " files loaded!" << endl;
		else if (c == MAX)
			cout << " " << c << " files loaded!" << endl;
	}
	cout << "Loading completed!" << endl;
}

void menu(int min, int sec)
{
	string t = "(" + to_string(min) + " Minutes " + to_string(sec) + " Seconds)";
	cout << endl << endl;
	cout << "|---------------------------------------------------------------------|" << endl;
	cout << "|                 Simple Document Retrieval System                    |" << endl;
	cout << left << setw(24) << "|" << setw(20) << t << right << setw(25) << "|" << endl;
	cout << "|---------------------------------------------------------------------|" << endl;
	cout << "| 1. Enter a single keyword to list the document(s)(file names)       |" << endl;
	cout << "| 2. Print the top 10 words that appeared most frequently             |" << endl;
	cout << "| 3. Print the top 10 words that appeared least frequently            |" << endl;
	cout << "| 4. Exit                                                             |" << endl;
	cout << "|---------------------------------------------------------------------|" << endl << endl;
}


int main()
{
	BinaryTree tree;
	string word;
	char option;
	bool flag = false;
	auto start = chrono::high_resolution_clock::now();

	load(tree);
	auto tempend = chrono::high_resolution_clock::now();
	auto tempmin = chrono::duration_cast<chrono::minutes>(tempend - start);
	auto tempsec = chrono::duration_cast<chrono::seconds>(tempend - start)-chrono::duration_cast<chrono::seconds>(tempmin);
	menu(tempmin.count(), tempsec.count());
	cout << "Option: ";
	cin >> option;

	do {
		switch (option)
		{
		case '1': //Enter a single keyword to list the document(s)(file names)
			flag = false;
			cout << "Enter the word you want to search: ";
			cin >> word;
			flag = tree.find(word);
			if (flag)
			{
				cout << "The word is found!" << endl;
				tree.printIndexOfNode(word);
			}
			else
				cout << "The word is not found!" << endl;
			break;
		case '2': //print the top 10 words that appeared most frequently
			tree.Most();
			break;
		case '3': //print the top 10 words that appeared least frequently
			tree.Least();
			break;
		case '4': //Exit
			break;
		default:
			cout << "Invalid option!" << endl;
			break;
		}

		if (option != '4')
		{
			auto end = chrono::high_resolution_clock::now();
			auto min = chrono::duration_cast<chrono::minutes>(end - start);
			auto sec = chrono::duration_cast<chrono::seconds>(end - start) -chrono::duration_cast<chrono::seconds>(min);
			menu(min.count(), sec.count());
			cout << "Option: ";
			cin >> option;
		}

	} while (option != '4');
	cout << "Exiting..." << endl;

	return 0;
}
