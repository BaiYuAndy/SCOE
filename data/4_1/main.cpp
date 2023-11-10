#include <iostream>
using namespace std;

#include "Node.h"

int main()
{
	Node<int> *p1, *p2, *p3;
	p1 = new Node<int> (20);
	p2 = new Node<int> (31);
	p2 -> InsertAfter(p1);
	p3 = new Node<int> (17);
	p2 -> InsertAfter(p3);
	cout << p2->data <<" "<<p2->NextNode()->data<<" ";
	p3 ->data = (*p2).NextNode()->data;
	p3 ->data ++;
	cout << p3->data <<" "<<p2->NextNode()->NextNode()->data<<" " <<endl;

	p1 = p2 -> DeleteAfter();
	cout << p1->data <<endl;

	return 1;
}