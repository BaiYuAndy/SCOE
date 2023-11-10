#include <iostream>
using namespace std;
#include "CNode.h"

template <class T>
ostream& operator<< ( ostream& cout, CNode<T> *p)
{
	do
	{
		cout<< p->data << " ";
		p = p -> NextNode();
	} while (p->data<=0);
	cout << endl;
	return cout;
}

void Josephus(CNode <int> *list, int s, int m)
{
	//currPtrΪɨ��ѭ�������ָ�������prevPtrΪ��ǰ������ָ��
	CNode<int> *prevPtr = list, *currPtr;
	CNode<int> *deleteNodePtr;

	int n = abs(list->data);
	if (s>n) 
	{
		cerr<<"error"<<endl;
		return;
	}

	for (int i=0; i<s-1; i++)
		prevPtr = prevPtr->NextNode();

	currPtr = prevPtr->NextNode();
	//n�α�������
	for (i=0; i<n; i++)
	{
		for (int j=0; j<m-1; j++)
		{
			prevPtr = currPtr;
			currPtr = currPtr -> NextNode();
			//��currPtrΪ��ͷ����������ͷ����
			if (currPtr->data <= 0)
			{
				prevPtr = currPtr;
				currPtr = currPtr -> NextNode();
			}
		}

		cout<<"������Ա��ţ�"<<currPtr->data<<endl;
		deleteNodePtr = currPtr;
		currPtr = currPtr -> NextNode();
		prevPtr -> DeleteAfter();
		delete deleteNodePtr;

		if (currPtr->data<= 0)
		{
			prevPtr = currPtr;
			currPtr = currPtr -> NextNode();
		}
		list->data++;
	}

	cout<<"���б�������!"<<endl;
}

void main(void)
{
	int total;
	cout<<"������������:"<<endl;
	cin>>total;

	int num;
	cout<<"������꼸����:"<<endl;
	cin>>num;

	int start;
	cout<<"�����뿪ʼ���:"<<endl;
	cin>>start;

	CNode<int> *people=new CNode<int>(0-total), *ptr;
	for (int i = total; i >= 1; i--)
	{
		ptr = new CNode<int>(i);
		people ->InsertAfter(ptr);
	}

	cout<<people;
	Josephus(people, start, num);
}