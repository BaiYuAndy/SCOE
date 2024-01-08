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

int main(void)
{
	/*Node<int> *p1, *p2, *p3,*p4;

	p1 = new Node<int>(20);
	p2 = new Node<int>(31);
	p3 = new Node<int>(17);
	p4 = new Node<int>(15);

	p2->InsertAfter(p1);
	p2->InsertAfter(p3);
	p2->InsertAfter(p4);
	cout << "list:\t\t"<<p2;

	p2->Reverse(p2);
	cout << "Reverse:\t"<< p2;*/

	int data[10] = {22,15,25,90,8,72,17,9,18,6};

	Node<int> *list = new Node<int>(data[0],NULL);

	for(int i=1;i<10;i++){
		Node<int> *pInsert = new Node<int>(data[i],NULL);

		list->InsertAfter(pInsert);
	}

	cout << "list:\t\t"<<list;
	//list->DeleteAfter();
	list = list->DeleteNode(15);
	cout << "list:\t\t"<<list;
	list->Reverse(list);
	cout << "Reverse:\t"<< list;


	return 0;
}
