#include "linkedset.h"
#include <iostream>
using namespace std;

template <class T>
ostream& operator<< ( ostream& cout, LinkedSet<T> *p)
{
	for (int i=0; i<p->Size(); i++)
	{
		p->SetPosition(i);
		cout<< p->GetData() << " ";
	}
	cout << endl;
	return cout;
}

void main( void )
{
	LinkedSet<int> l1, l2, *tmp;

	l1.InsertAfter(1);	
	l1.InsertAfter(2);	
	l1.InsertAfter(3);
	cout<<"linkedset 1:"<<&l1;

	l2.InsertAfter(2);
	l2.InsertAfter(4);
	cout<<"linkedset 2:"<<&l2;

	tmp=Union(l1, l2);
	cout<<"the union:"<<tmp;
	tmp=Intersection(l1, l2);
	cout<<"the intersection:"<<tmp;
}