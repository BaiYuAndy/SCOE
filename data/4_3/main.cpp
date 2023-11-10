#include <iostream>
using namespace std;
#include "Node.h"

template <class T>
ostream& operator<< ( ostream& cout, Node<T> *p)
{
	
	while (p)
	{
		cout<< p->data << " ";
		p = p -> NextNode();
	}
	cout << endl;
	return cout;
}

void main(void)
{
	Node<int> *p1, *p2, *p3;
	Node<int> *q1, *q2;

	p1 = new Node<int>(20);
	p2 = new Node<int>(31);
	p3 = new Node<int>(17);

	p2->InsertAfter(p1);
	p2->InsertAfter(p3);
	cout << "链表1:"<<p2;

	q1 = new Node<int>(27);
	q2 = new Node<int>(40);
	
	q2->InsertAfter(q1);
	cout << "链表2:"<<q2;
	
	p2->Append(q2);
	cout << "复制后 链表1:"<<p2<<endl;
	cout << "复制后 链表2:"<<q2<<endl;
}