#ifndef NODE_CLASS
#define NODE_CLASS

#include<iostream>

using namespace std;

const char * sName[10]={"liyan","zhangyunhua","gaoyuan","zhangmofeng",
					"zhaopingping","sunsiting","zhouyi","lifang",
					"xiameng","leixin"};

template<typename T>
class Infor{
	public:

	const char *name;
	int score;
	int seque;

};

template<typename T>
class Stack
{
 	
public:

 	int num;

 	T *data;

 	Stack *next;

 	Stack *front;

 	Stack(){
 		num = 0;

 		data =NULL;

 		next = NULL;

 		front = NULL;

 	};

 	~Stack(){
 		if(data!=NULL)
 			delete data;
 		if(front!=NULL)
 			delete front;
 		if(next !=NULL)
 			delete next;
 	}

 	Stack<T> & operator<<(Infor<void> *p);
 	
 	Stack<T> & operator>>(int num);

 	Stack<T> & operator>>(Infor<void> &p);

 	Stack<Infor<void> > * initList(int size);

};

template <typename T>
Stack<Infor<void> >  *Stack<T>::initList(int size){
	Stack<Infor<void> > *head,*p1,*p2;

	int i=0;

	while(i<size){
		if(i==0){
			head = new Stack<Infor<void> >();
			(*head)>>(i+1);
			Infor<void> *p = new Infor<void>();
			p->seque = (10+i);
			p->name = sName[i];
			p->score = 100;

			(*head)>>(*p);

			p1 = head;

		}
		else{

			p2 = new Stack<Infor<void> >();
			(*p2)>>(i+1);
			Infor<void> *p = new Infor<void>();
			p->seque = (10+i);
			p->name = sName[i];
			p->score = 100;
			(*p2)>>(*p);

			p1->next = p2;

			p1=p2;

		}

		i++;
	}

	this->front = p1;
	(this->front)->next = NULL;

	return head;

}

template <typename T>
Stack<T> & Stack<T>::operator>>(int num){
	this->num = num;

	return *this;
}

template <typename T>
Stack<T> & Stack<T>::operator>>(Infor<void> &p){
	data = new Infor<void>();

	*data = p;
	return *this;
}

template <typename T>
Stack<T> & Stack<T>::operator<<(Infor<void> *p){
	cout<<p->name<<"\t";
	cout<<p->seque<<"\t";
	cout<<p->score<<"\n";

	return *this;
}

/*
template <typename T>
ostream& operator<<(ostream& cout, Infor<T> *p){
	cout<<p->name<<"\t";
	cout<<p->seque<<"\t";
	cout<<p->score<<"\n";

	return cout;
}
*/

template <typename T>
ostream& operator<< ( ostream& cout, Stack<T> *p){
	if(p!=NULL){
		cout<<p->num<<"\n";

		(*p)<<p->data;
	}

	return cout;
}

#endif  // NODE_CLASS