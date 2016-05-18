// DZ.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <vector>
using namespace std;

class sub;
class work
{
private:
	string name;
	sub* subd;
	vector<string> subddop;
	vector<string> history;
public:
	friend sub;
	friend ofstream& operator<<(ofstream& os, const sub& p);
	work(string s, sub* str)
	{
		name = s;
		subd = str;
	}
	void addsubd(string str)
	{
		subddop.push_back(str);
	}
	void delsubd(string str)
	{
		for (int i = 0; i < subddop.size(); i++)
		{
			if (subddop[i] == str)
				subddop.erase(subddop.begin() + i);
		}
	}
	~work()
	{
		subddop.clear();
		history.clear();
	}

};

class sub
{
private:
	vector<sub*> psub;
	sub* psubd;
	vector<work*> pwork;
	string name;
public:
	friend work;
	sub(string s, sub* str)
	{
		name = s;
		psubd = str;
	}
	void addsub(string s)
	{
		sub* pnew = new sub(s, this);
		psub.push_back(pnew);
	}
	void addsub(sub* s)
	{
		s->psubd = this;
		psub.push_back(s);
	}
	sub* searchsub(string s)
	{
		if (s == "head") return this;
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
		pnew->history.push_back(this->name);
		pwork.push_back(pnew);	
	}
	void addwork(work* s)
	{
		s->subd = this;
		s->history.push_back(this->name);
		pwork.push_back(s);
	}
	sub* searchwork(string s)
	{
		for (int i = 0; i < pwork.size(); i++)
		{
			if (pwork[i]->name == s)
				return this;
		}

		for (sub* k : psub)
		{
			if (k->searchwork(s) != 0) return k->searchwork(s);
		}
		return 0;
	}
	void informwork(string a)
	{
		for (work* k : pwork)
		{
			if (k->name == a)
			{
				cout << "\t" << k->name << endl << " Powered by: " << this->name << endl;
				cout << "Worked on: ";
				for (int i = 0; i<k->history.size(); i++)
					cout << k->history[i] << ' ';
				cout << endl;
				cout << "Earns on: ";
				for (int i = 0; i<k->subddop.size(); i++)
					cout << k->subddop[i] << ' ';
				cout << endl;
			}
		}
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
		cout <<"\t" << this->name << endl;
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
	sub* getsubd()
	{
		return psubd;
	}
	work* getwork(string a)
	{
		for (work* k : pwork)
		{
			if (k->name == a)
				return k;
		}
	}
	~sub()
	{
		psub.clear();
		pwork.clear();
	}
	friend void merger(sub*a, sub* b);
	friend ofstream& operator<<(ofstream& os, const sub& p);
};
void merger(sub*a, sub* b)
{
	for (int i = 0; i < b->pwork.size(); i++)
		a->addwork(b->pwork[i]);
	for (int i = 0; i < b->psub.size(); i++)
		a->addsub(b->psub[i]);
}

ofstream& operator<<(ofstream& os, const sub& p)
{
	for (int i = 0; i < p.pwork.size(); i++)
		os << "Workman: " << p.pwork[i]->name << ' ' << p.pwork[i]->subd->name << endl;
	for (int i = 0; i < p.psub.size(); i++)
		os << "Subdivision: " << p.psub[i]->name << ' ' << p.psub[i]->psubd->name << endl;
	for (int i = 0; i < p.psub.size(); i++)
		os << *p.psub[i];
	return os;
}

int main()
{
	sub comp("head", 0);
	string command1, command2, name1, name2;
	int k = 0;
	while (command1 != "end")
	{
	
		cin >> command1;
		if (command1 == "add")
		{
			k = 1;
			cin >> command2;
			if (command2 == "work")          //найм сотрудника
			{
				cin >> name1;
				if (comp.searchwork(name1) == 0)
				{
					cin >> name2;
					if (comp.searchsub(name2) != 0)
						comp.searchsub(name2)->addwork(name1);
					else cout << "No subdivision";
				}
				else cout << "Exists";
			}
			if (command2 == "sub")              //создание подразделения
			{
				cin >> name1;
				if (comp.searchsub(name1) == 0)
				{
					cin >> name2;
					if (comp.searchsub(name2) != 0)
						comp.searchsub(name2)->addsub(name1);
					else cout << "No subdivision";
				}
				else cout << "Exists";
			}
			if ((command2 != "work") && (command2 != "sub")) cout << "not right command" << endl;
		}

		if (command1 == "del")
		{
			k = 1;
			cin >> command2;
			if (command2 == "work")                  //увольнение сотрудника
			{
				cin >> name1;
				if (comp.searchwork(name1) != 0)
				{
					comp.searchwork(name1)->delwork(name1);
				}
				else cout << "No workman";
			}
			if (command2 == "sub")                       //расформирование подразделения
			{
				cin >> name1;
				if (comp.searchsub(name1) != 0)
				{
					comp.searchsub(name1)->getsubd()->delsub(name1);
				}
				else cout << "No subdivision";
			}
			if ((command2 != "work") && (command2 != "sub")) cout << "not right command" << endl;

		}
		if (command1 == "transfer")               
		{
			k = 1;
			cin >> command2;
			if (command2 == "work")            //перевод сотрудника между подразделениями
			{
				cin >> name1;
				if (comp.searchwork(name1) != 0)
				{
					cin >> name2;
					if (comp.searchsub(name2) != 0)
					{
						work* k;
						k = comp.searchwork(name1)->getwork(name1);
						comp.searchwork(name1)->delwork(name1);
						comp.searchsub(name2)->addwork(k);
					}
					else cout << "No subdivision";
				}
				else cout << "No workman";
			}
			if (command2 == "sub")              //перемещение подразделений
			{
				cin >> name1;
				if (comp.searchsub(name1) != 0)
				{
					cin >> name2;
					if (comp.searchsub(name2) != 0)
					{
						sub* k;
						k = comp.searchsub(name1);
						if (k->searchsub(name2) == 0)
						{
							comp.searchsub(name1)->getsubd()->delsub(name1);
							comp.searchsub(name2)->addsub(k);
						}
						else cout << "Transfer not available";
					}
					else cout << "No subdivision";
				}
				else cout << "No subdivision";
			}
			if ((command2 != "work") && (command2 != "sub")) cout << "not right command" << endl;
		}
		if (command1 == "list")
		{
			k = 1;
			comp.list();
		}
		if (command1 == "merger")                    //объединение подразделений
		{
			k = 1;
			cin >> name1;
			if (comp.searchsub(name1) != 0)
			{
				cin >> name2;
				if (comp.searchsub(name2) != 0)
				{
					if (comp.searchsub(name1)->searchsub(name2) != 0)
					{
						merger(comp.searchsub(name1), comp.searchsub(name2));
						comp.searchsub(name2)->getsubd()->delsub(name2);
					}
					if (comp.searchsub(name2)->searchsub(name1) != 0)
					{
						merger(comp.searchsub(name2), comp.searchsub(name1));
						comp.searchsub(name1)->getsubd()->delsub(name1);
					}
					if ((comp.searchsub(name1)->searchsub(name2) == 0) && (comp.searchsub(name2)->searchsub(name1) == 0))
					{
						merger(comp.searchsub(name2), comp.searchsub(name1));
						comp.searchsub(name1)->getsubd()->delsub(name1);
					}
				}
				else cout << "No subdivision";
			}
			else cout << "No subdivision";
		}
		if (command1 == "inform")             //поиск сотрудника и информация о нём
		{
			k = 1;
			cin >> name1;
			if (comp.searchwork(name1) != 0)
				comp.searchwork(name1)->informwork(name1);
			else cout << "No workman";
		}
		if (command1 == "save")                   //сохранение данных
		{
			k = 1;
			ofstream fout;
			fout.open("data.txt");
			fout << comp;

			fout.close();
		}
		if (command1 == "open")                     //восстановление данных
		{
			k = 1;
			ifstream fin;
			fin.open("data.txt");
			sub q("head", 0);
			comp = q;
			while (!fin.eof())
			{
				fin >> command2;
				fin >> name1;
				fin >> name2;
				if (name1 == "work")
				{
					comp.searchsub(name2)->addwork(name1);
				}
				if (command2 == "sub")
				{
					comp.searchsub(name2)->addsub(name1);
				}
			}

			if (command2 == "work")
				comp.searchwork(name1)->delwork(name1);
			if (command2 == "sub")
				comp.searchsub(name1)->getsubd()->delsub(name1);
			fin.close();
		}
		if (command1 == "end")
		{
			k = 1;
		}
		if (command1 == "addsubd")                   //работа сотрудника на несколько ставок
		{
			k = 1;
			cin >> name1;
			if (comp.searchwork(name1) != 0)
			{
				cin >> name2;
				if (comp.searchsub(name2) != 0)
				{
					comp.searchwork(name1)->getwork(name1)->addsubd(name2);
				}
				else cout << "No subdivision";
			}
			else cout << "No workman";
		}
		if (command1 == "delsubd")                     //увольнение сотрудника со второстепенной ставки
		{
			k = 1;
			cin >> name1;
			if (comp.searchwork(name1) != 0)
			{
				cin >> name2;
				if (comp.searchsub(name2) != 0)
				{
					comp.searchwork(name1)->getwork(name1)->delsubd(name2);
				}
				else cout << "No subdivsion";
			}
			else cout << "No workman";
		}
		if (k==0) cout << "not right command" << endl; 
	}
	return 0;
}
