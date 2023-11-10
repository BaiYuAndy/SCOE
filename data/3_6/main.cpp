

#include "node.h"

/*Node<Infor<void> > * initList(int size){
	Node<Infor<void> > *head,*p1,*p2;

	int i=0;

	while(i<size){
		if(i==0){
			head = new Node<Infor<void> >();
			(*head)>>(i+1);
			Infor<void> *p = new Infor<void>();
			p->seque = (10+i);
			p->name = sName[i];
			p->score = 100;

			(*head)>>(*p);

			p1 = head;
		}
		else{

			p2 = new Node<Infor<void> >();
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

	return head;

}*/

int main(){

	/*Node<Infor<void> > *node;
	node = new Node<Infor<void> >();

	(*node)>>(12);

	Infor<void> *p = new Infor<void>();
	p->seque = 1;
	p->name = sNmame[9];
	p->score = 100;

	(*node)>>(*p);

	cout<<node;*/

	Stack<Infor<void> > *head;

	//head = head->initList(10);

	Stack<Infor<void> > *node;
	node = head->initList(10);
	//node = 
	cout<<head->front;

	/*for(int i=0;i<10;i++){
		cout<<node;

		node=node->next;
	}*/

	cout<<node;
 	return 1;
}



