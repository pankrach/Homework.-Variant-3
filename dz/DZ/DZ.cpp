// DZ.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;

class sub;
class work
{
private:
	string name;
	vector<sub*> subd;
public:
	friend sub;
	work(string s, sub* str)
	{
		name = s;
		subd.push_back(str);
	}
	void addsubd(sub* str)
	{
		subd.push_back(str);
	}
	void del(sub* str)
	{
		int k;
		for (int i = 0; i < subd.size(); i++)
		{
			if (subd[i] == str)
				k = i;
			else  k = -1;
		}
		if (k != -1)
		{
			subd.erase(subd.begin() + k);
		}
	}
	~work()
	{
		subd.clear();
	}

};

class sub
{
private:
	vector<sub*> psub;
	vector<sub*> psubd;
	vector<work*> pwork;
	string name;
public:
	friend work;
	sub(string s, sub* str)
	{
		name = s;
		psubd.push_back(str);
	}
	void addsub(string s)
	{
		sub* pnew = new sub(s, this);
		psub.push_back(pnew);
	}
	sub* searchsub(string s)
	{
		if (s == "Head") return this;
		for (int i = 0; i < psub.size(); i++)
		{
			if (psub[i]->name == s)
				return psub[i];
		}

		for (sub* k : psub)
		{
			if (k->searchsub(s) != 0) return k->searchsub(s);
		}
		return 0;
	}
	void delsub(string s)
	{
		for (int i = 0; i < psub.size(); i++)
		{
			if (psub[i]->name == s) psub.erase(psub.begin() + i);
		}
	}
	void addwork(string s)
	{
		work* pnew = new work(s, this);
		pwork.push_back(pnew);
	}

	work* searchwork(string s)
	{
		for (int i = 0; i < pwork.size(); i++)
		{
			if (pwork[i]->name == s)
				return pwork[i];
		}

		for (sub* k : psub)
		{
			if (k->searchwork(s) != 0) return k->searchwork(s);
		}
		return 0;
	}

	void delwork(string s)
	{
		for (int i = 0; i < pwork.size(); i++)
		{
			if (pwork[i]->name == s) pwork.erase(pwork.begin() + i);
		}
	}
	
	void list()
	{
		cout << this->name << endl;
		cout << "Workman: ";
		for (int i = 0; i < pwork.size(); i++)
			cout << pwork[i]->name << ' ';
		cout << endl << "Subdivision: ";
		for (int i = 0; i < psub.size(); i++)
			cout << psub[i]->name << ' ';
		cout << endl;
		for (sub* sub : psub)
		{
			sub->list();
		}

	}

};


int main()
{
	sub comp("Head", 0);
	string command1, command2, name1, name2;
	while (command1 != "end")
	{
		cin >> command1;
		if (command1 == "add")
		{
			cin >> command2;
			if (command2 == "work")
			{
				cin >> name1;
				if (comp.searchwork(name1) == 0)
				{
					cin >> name1;
					if (comp.searchsub(name2) != 0)
						comp.searchsub(name2)->addwork(name1);
					else cout << "No subdivision";
				}
				else cout << "Exists";
			}
			if (command2 == "sub")
			{
				cin >> name1;
				cin >> name2;
				comp.searchsub(name1)->addsub(name2);
														 
			}
		
		}
		if (command1 == "del")
		{
			cin >> command2;
			if (command2 == "work")
			{
				cin >> name1;
				cin >> name2;
				comp.searchsub(name2)->delwork(name1);

			}
			if (command2 == "sub")
			{
				cin >> name1;
				cin >> name2;
				comp.searchsub(name2)->delsub(name1);

			}
		}
		if (command1 == "list")
		{
			comp.list();
		}
		
		else cout << "not right command" << endl;
	}
	return 0;
}


