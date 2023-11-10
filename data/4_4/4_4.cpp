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
	//currPtr为扫描循环链表的指针变量，prevPtr为其前驱结点的指针
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
	//n次报数过程
	for (i=0; i<n; i++)
	{
		for (int j=0; j<m-1; j++)
		{
			prevPtr = currPtr;
			currPtr = currPtr -> NextNode();
			//若currPtr为表头，则跳过表头记数
			if (currPtr->data <= 0)
			{
				prevPtr = currPtr;
				currPtr = currPtr -> NextNode();
			}
		}

		cout<<"出列人员序号："<<currPtr->data<<endl;
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

	cout<<"出列报数结束!"<<endl;
}

void main(void)
{
	int total;
	cout<<"请输入总人数:"<<endl;
	cin>>total;

	int num;
	cout<<"请输入逢几出列:"<<endl;
	cin>>num;

	int start;
	cout<<"请输入开始序号:"<<endl;
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