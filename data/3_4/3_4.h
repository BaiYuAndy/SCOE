#include <iostream>
#define defaultSize 9

template <class T>
class LinearList
{
	private:
														//list max number(same asn-1)
		int Last;

	typedef struct node{
		T *data;
		struct node *next;
	}Node;

		Node *head;

	public:
		void assgin(T *list,int size);// put data maxtrix to list;
		T getElem(int i);//get number from head list;
		void insertElem(T x,int position);
		void reverseList();

		LinearList (){
			head = NULL;
			Last = 0;
		}
		~LinearList(){ 
			if(head!=NULL)
				delete head;
		}
		bool ListEmpty ( )	{return ( Last<=0? true : false);}
		int ListLength ( void ) const { return Last;}

};

template<typename T>
void LinearList<T>::assgin(T *list,int size){
	if(list!=NULL){
		int i = 0;
		while(i<size){
			Node *p,*q;
			if(i == 0){
				head = (Node *)malloc(sizeof(Node));
				head->data = (T *)malloc(sizeof(T));
				*(head->data) = *(list+i);
				head->next=NULL;
				p=head;
				i++;
			}
			else{
				q=(Node *)malloc(sizeof(Node));
				q->data = (T *)malloc(sizeof(T));
				*(q->data) = *(list+i);
				p->next=q;
				p=q;
				p->next=NULL;
	
				i++;
			}
		}
		Last = i;
	}
}

template <typename T>
T LinearList <T> ::getElem(int i){
	assert(i>=0 && i<Last);
	T data;
	int k=0;
	Node *p;
	p=head;
	while(k!=i){
		k++;
		p=p->next;
	}
	data = *(p->data);
	return data;
}

template <typename T>
void LinearList<T>::insertElem(T x,int position){
	assert(position<=Last);

	if(position==0){
		if(head==NULL){
			head=(Node *)malloc(sizeof(Node));
			head->data = (T *)malloc(sizeof(T));
			*(head->data) = x;
			head->next = NULL;
		}
		else{
			Node *p;

			p=(Node *)malloc(sizeof(Node));
			p->data = (T *)malloc(sizeof(T));
			*(p->data) = x;
			p->next = head;

			head=p;
		}
	}
	else{
		assert(head!=NULL);
		Node *p,*q;
		int k=1;
		p=head;
		q=p->next;
		while(k!=position){
			p=p->next;
			q=p->next;
			k++;
		}
		Node *r;
		r=(Node *)malloc(sizeof(Node));
		r->data = (T *)malloc(sizeof(T));
		*(r->data) = x;

		p->next=r;
		
		if(k==Last){
			r->next=NULL;
		}
		else
			r->next=q;
	}
	Last++;
}

template <typename T>
void LinearList<T>::reverseList(){
	assert(head!=NULL);
	Node *p,*q,*r;

	p=head;
	q=p->next;

	while( q!=NULL){
		r=q->next;
		q->next = p;
		
		p = q;
		q = r;
	}
	head->next=NULL;
	head = p;
}
