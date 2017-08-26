/*
		Author: Caleb Johnson
		OrderedList.cpp
*/

#include "Student.h"
#include "OrderedList.h"
#include <string>
#include <fstream>

using namespace std;

OrderedList::OrderedList() { length = 0; }
OrderedList::~OrderedList() {}

Student OrderedList::getNode(int index)
{
	return nodes[index];
}

int OrderedList::getLength()
{
	return length;
}

void OrderedList::setNode(int index, Student value)
{
	nodes[index] = value;
}


bool OrderedList::remove(string lastName, string firstName)
{
	for (int i = 0; i < length; i++)
	{
		if ((lastName + ", " + firstName) == nodes[i].toString())
		{
			for (int j = i; j < length - 1; j++)
			{
				nodes[j] = nodes[j + 1];
			}
			length -= 1;
			return true;
		}
	}
	return false;
}

bool OrderedList::insert(Student newItem)
{
	nodes[length] = newItem;
	length += 1;
	return true;
}

Student* OrderedList::search(string lastName, string firstName) //Was originally *search, not sure why
{
	for (int i = 0; i < length; i++)
	{
		if ((lastName + ", " + firstName) == nodes[i].toString())
		{
			return &nodes[i];
		}
	}
	return nullptr;
}

void OrderedList::traverse(void)
{
	bool finishedsorting = false;
	Student tempstudent;
	while (!finishedsorting)
	{
		finishedsorting = true;
		for (int i = 0; i < length - 1; i++)
		{
			string a = nodes[i].toString();
			string b = nodes[i + 1].toString();
			int comparer = a.compare(b);
			if (comparer > 0)
			{
				finishedsorting = false;

				tempstudent = nodes[i];
				nodes[i] = nodes[i + 1];
				nodes[i + 1] = tempstudent;
			}
		}
	}

	for (int i = 0; i < length; i++)
	{
		cout << i + 1 << ".    " << nodes[i].getLastName() << ", " << nodes[i].getFirstName() << " - " << nodes[i].letterGrade() << endl;
	}
}

void OrderedList::traverseByGrade(void)
{
	//string comparestrings[100];
	//for (int i = 0; i < length; i++)
	//{
	//	comparestrings[i] = nodes[i].letterGrade() + nodes[i].toString();
	//}
	//bool finishedsorting = false;
	//string tempstring;
	//Student tempstudent;
	//while (!finishedsorting)
	//{
	//	finishedsorting = true;
	//	for (int i = 0; i < length - 1; i++)
	//	{

	//		int comparer = comparestrings[i].compare(comparestrings[i + 1]);
	//		if (comparer > 0)
	//		{
	//			finishedsorting = false;

	//			tempstring = comparestrings[i];
	//			comparestrings[i] = comparestrings[i + 1];
	//			comparestrings[i + 1] = tempstring;

	//			tempstudent = nodes[i];
	//			nodes[i] = nodes[i + 1];
	//			nodes[i + 1] = tempstudent;
	//		}
	//	}
	//}

	bool finishedsorting = false;
	Student tempstudent;
	while (!finishedsorting)
	{
		finishedsorting = true;
		for (int i = 0; i < length - 1; i++)
		{
			string a = nodes[i].toString();
			string b = nodes[i + 1].toString();
			
			int comparer;
			if (nodes[i].calculateGrade() > nodes[i + 1].calculateGrade())
			{
				comparer = -1;
			}
			else if (nodes[i].calculateGrade() < nodes[i + 1].calculateGrade())
			{
				comparer = 1;
			}
			else
			{
				comparer = a.compare(b);
			}
			if (comparer > 0)
			{
				finishedsorting = false;

				tempstudent = nodes[i];
				nodes[i] = nodes[i + 1];
				nodes[i + 1] = tempstudent;
			}
		}
	}

	for (int i = 0; i < length; i++)
	{
		cout << i + 1 << ".    " << nodes[i].getLastName() << ", " << nodes[i].getFirstName() << " - " << nodes[i].letterGrade() << endl;
	}
}

void OrderedList::traverseOut(ofstream *f, double hwWeight, double qzWeight, double fxWeight)
{
	string newRoster;

	newRoster = to_string(hwWeight) + '\n' + to_string(qzWeight) + '\n' + to_string(fxWeight) + '\n' + to_string(length) + '\n';
	for (int i = 0; i < length; i++)
	{
		newRoster += nodes[i].getLastName() + "    " + nodes[i].getFirstName();
		for (int j = 0; j < 4; j++)
		{
			int a = nodes[i].getHWScore(j);
			newRoster += "    " + to_string(a);
		}
		for (int j = 0; j < 4; j++)
		{
			int a = nodes[i].getQuizScore(j);
			newRoster += "    " + to_string(a);
		}
		newRoster += "    " + to_string(nodes[i].getFinalExam()) + '\n';
	}
	*f << newRoster;
}