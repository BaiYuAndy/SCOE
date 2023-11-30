#include <iostream>
#include <stdlib.h>
#include "NODE.h"

using namespace std;

int min(const int a,const int b)
{
	return(a>b)?b:a;
}

int max(const int a,const int b)
{
	return(a>b)?a:b;
}

template<class T>
class LinkedList
{
	protected:
		Node<T> *front,*rear;
		Node<T> *prevPtr,*currPtr;
		int size;
		int position;
		Node<T> *GetNode(const T&item,Node<T> *ptr=NULL);
		void FreeNode(Node<T> *p);
	public:
		LinkedList(void);
		~LinkedList(void);
		LinkedList<T>&operator=(const LinkedList<T>& orgList);
		int Size(void)const;
		bool IsEmpty(void)const;
		int NextNode(void);
		int SetPosition(int pos);
		int GetPosition(void)const;
		void InsertAt(const T&item);
		void InsertAfter(const T&item);
		void DeleteAt(void);
		void DeleteAfter(void);
		T GetData(void)const;
		void SetData(const T&item);
		void Clear(void);
};

//function define:
template<class T>
Node<T> *LinkedList<T>::GetNode(const T& item,Node<T> *ptr)//=NULL
{
	Node<T> *newNode=new Node<T>(item,ptr);
	if(!newNode)
	{
		cerr<<"GetNode: Memory allocation failed!"<<endl;
		return NULL;
	}
	return newNode;
}

template<class T>
void LinkedList<T>::FreeNode(Node<T> *ptr)
{
	if(!ptr)
	{
		cerr<<"FreeNode: invalid node pointer!"<<endl;
		return;
	}
	delete ptr;
}

template<class T>
LinkedList<T>:: LinkedList(void):front(NULL),rear(NULL),prevPtr(NULL),currPtr(NULL),size(0),position(-1)
{}

template<class T>
LinkedList<T>::~LinkedList(void)
{
	Clear();
}

template<class T>
LinkedList<T> &LinkedList<T>::operator =(const LinkedList<T>& orgList)
{
	Node<T> *p=orgList.front;
	Clear();
	while(p)
	{
		InsertAfter(p->data);
		p=p->NextNode();
	}
	SetPosition(orgList.position);
	return *this;
}

template<class T>
int LinkedList<T>::Size(void)const
{
	return size;
}

template<class T>
bool LinkedList<T>::IsEmpty (void)const
{
	return size?false:true;
}

template<class T>
int LinkedList<T>::NextNode(void)
{
	if(position<size)
	{
		position++;
		prevPtr=currPtr;
		currPtr=currPtr->NextNode();
	}
	else
	{
		position=size;
	}
	return position;
}
 
template<class T>
int LinkedList<T>::SetPosition(int pos)//const 
{
	if(!size)return -1;
	pos=min(size,max(0,pos));
	prevPtr=NULL;
	currPtr=front;
	position=0;
	for(int k=0;k<pos;k++)
	{
		position++;
		prevPtr=currPtr;
		currPtr=currPtr->NextNode();
	}
	return position;
}
 
template<class T>
int LinkedList<T>::GetPosition(void)const
{
	return position;
}
 

template<class T>
void LinkedList<T>::InsertAt(const T& item)
{
	Node<T> *newNode;
	if(!size)
	{
		newNode=GetNode(item,front);
		front=rear=newNode;
		position=0;
	}
	else if(!prevPtr)
	{
		newNode=GetNode(item,front);
		front=newNode;
	}
	else
	{
		newNode=GetNode(item,currPtr);
		prevPtr->InsertAfter(newNode);
	}
	size++;
	currPtr=newNode;
}

template<class T>
void LinkedList<T>::InsertAfter(const T& item)
{
	Node<T> *newNode;
	if(!size)
	{
		newNode=GetNode(item);
		front=rear=newNode;
		position=0;
	}
	else if(currPtr==rear||!currPtr)
	{
		newNode=GetNode(item);
		rear->InsertAfter(newNode);
		prevPtr=rear;
		rear=newNode;
		position=size;
	}
	else
	{
		newNode=GetNode(item,currPtr->NextNode());
		currPtr->InsertAfter(newNode);
		prevPtr=currPtr;
		position++;
	}
	size++;
	currPtr=newNode;
}

template<class T>
void LinkedList<T>::DeleteAt(void)
{
	Node<T> *oldNode;
	if(!currPtr)
	{
		cerr<<"DeleteAt: current position is invalid!"<<endl;
		return;
	}
	if(!prevPtr)
	{
		oldNode=front;
		front=currPtr->NextNode();
	}
	else
	{
		oldNode=prevPtr->DeleteAfter();
	}
	if(oldNode==rear)
	{
		rear=prevPtr;
		position--;
	}
	currPtr=oldNode->NextNode();
	FreeNode(oldNode);
	size--;
}

template<class T>
void LinkedList<T>::DeleteAfter(void)
{
	Node<T> *oldNode;
	if(!currPtr||currPtr==rear)
	{
		cerr<<"DeleteAfter: current position is invalid!"<<endl;
		return;
	}
	oldNode=currPtr->DeleteAfter();
	if(oldNode==rear)
	{
		rear=currPtr;
		//positoin--;
	}
	//currPtr=oldNode->NextNode();
	FreeNode(oldNode);
	size--;
}

template<class T>
T LinkedList<T>::GetData(void)const
{
	if(!size||!currPtr)
	{
		cerr<<"Data: current node not exist!"<<endl;
		exit(1);
	}
	return currPtr->data;
} 

template<class T>
void LinkedList<T>::SetData(const T & item)
{
	if(!size||!currPtr)
	{
		cerr<<"Data: current node not exist!"<<endl;
		exit(1);
	}
	currPtr->data=item;
}
 
template<class T>
void LinkedList<T>::Clear(void)
{
	Node<T> *currNode=front,*nextNode;
	while(currNode)
	{
		nextNode=currNode->NextNode();
		FreeNode(currNode);
		currNode=nextNode;
	}
	front=rear=prevPtr=currPtr=NULL;
	size=0;
	position=-1;
}
