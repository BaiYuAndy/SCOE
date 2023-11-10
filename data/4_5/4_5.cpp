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

/*另一种方法
void main(void)
{
	Node<int> *p1, *p2, *p3;

	p1 = new Node<int>(20);
	p2 = new Node<int>(31);
	p3 = new Node<int>(17);

	p2->InsertAfter(p1);
	p2->InsertAfter(p3);
	cout << "链表为:"<<p2;

	Node<int> *result = p2->Reverse();
	cout << "逆转后:"<< result;
}
*/

void main(void)
{
	Node<int> *p1, *p2, *p3;

	p1 = new Node<int>(20);
	p2 = new Node<int>(31);
	p3 = new Node<int>(17);

	p2->InsertAfter(p1);
	p2->InsertAfter(p3);
	cout << "链表为:"<<p2;

	p2->Reverse(p2);
	cout << "逆转后:"<< p2;
}
