#include "DNode.h"
#include "linkedlist.h"
#include <iostream>
using namespace std;

template <class T>
ostream& operator<< ( ostream& cout, LinkedList<T> *p)
{
	for (int i=0; i<p->Size(); i++)
	{
		p->SetPosition(i);
		cout<< p->GetData() << " ";
	}
	cout << endl;
	return cout;
}

template <class T>
ostream& operator<< ( ostream& cout, DNode<T> *p)
{
	DNode<T> *tmp = p->NextNode();
	
	do
	{
		cout<<tmp->GetData()<<" ";
		tmp = tmp ->NextNode();
	}while (tmp!=p);

	cout << endl;
	return cout;
}

template <class T>
void convert(LinkedList<T> &l1, DNode<T> *l2)
{
	DNode<T> *tmp;
	DNode<T> *zeroptr=l2;

	int m = l1.Size();
	for ( int i=0; i<m; i++)
	{
		tmp = new DNode<T>;
		l1.SetPosition(i);
		tmp->data = l1.GetData();
		if (tmp->data < 0)
		{
			l2->InsertAfter(tmp);
			zeroptr = zeroptr->NextNode();
		}
		if (tmp->data > 0) l2->InsertBefore(tmp);
		if (tmp->data == 0) zeroptr->InsertAfter(tmp);
	}
}

int main( void )
{
	LinkedList<int> list;
	DNode<int> *result = new DNode<int>(0);//±íÍ·½áµã

	list.InsertAfter(1);	
	list.InsertAfter(-2);	
	list.InsertAfter(2);	
	list.InsertAfter(0);	
	list.InsertAfter(-4);	
	list.InsertAfter(4);	
	list.InsertAfter(0);	
	list.InsertAfter(-1);		
	list.InsertAfter(3);
	cout<<"source list:"<<&list;

	convert(list,result);
	cout<<"dlinkedslist:"<<result;

	return 0;
}
