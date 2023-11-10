#include <iostream>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <queue>

typedef struct node
{
	int data;

	struct node *next;
}ND;

using namespace std;

typedef struct heapNode{
	int data;

	struct heapNode * leftNode;
	struct heapNode * rightNode;
}HD;

HD * creatHeap(int data,HD *heap){
	//cout<<data<<endl;
	if(heap==NULL){
		heap = (HD *)malloc(sizeof(HD));


		heap->data = data;
		heap->leftNode = NULL;
		heap->rightNode =NULL;
	}
	if(data>heap->data){
		heap->rightNode=creatHeap(data,heap->rightNode);
	}
	else if(data<heap->data){
		heap->leftNode=creatHeap(data,heap->leftNode);
	}
	else
		heap->data = data;

	return heap;
}

vector<vector<int> >* levelOrder(HD *root){
	vector<vector<int> > *res;

	res = new vector<vector<int> >;

	queue<HD*> q;

	if(root ==NULL)
		return res;
	q.push(root);
	vector<int> v;
	while(!q.empty()){
		v.clear();

		int size =q.size();
		while(size--){
			HD* temp=q.front();
			v.push_back(temp->data);
			if(temp->leftNode)
				q.push(temp->leftNode);
			if(temp->rightNode)
				q.push(temp->rightNode);
			q.pop();
		}
		res->push_back(v);
	}
	return res;
}

void showHeap(HD *heap){
	if(heap){
		showHeap(heap->leftNode);
		cout<<heap->data<<"\t";
		showHeap(heap->rightNode);
	}
}//this is same as middle sort

void show(int *num,int size){
	for(int i =0;i<size;i++){
		cout<<*(num+i)<<" ";
	}
}

int * heapSort(int *data,int total){
	
	assert(total>0);

	HD * root;
	root =NULL;

	int i=0;
	do{
		root = creatHeap(*(data+i),root);
		i++;
	}while(i<total);

	stack<HD*> middleStack;

	HD* p;
	p = root;
	middleStack.push(p);
	i=0;
	int j=0;
	while(i<total &&(p!=NULL ||!middleStack.empty()) ) {
		while(p!=NULL){
			middleStack.push(p);
			p=p->leftNode;
		}
		if(!middleStack.empty()){
			p = middleStack.top();
			//cout<<p->data;
			*(data+j) = p->data;
			j++;
			middleStack.pop();
			p=p->rightNode;
		}
		i++;
	}

	return data;
}

int *bubble(int *num,int size){

	if(size<=0){

		return NULL;
	}
	else{
		for(int i=0;i<size;i++){
			//int temp = *(num+i);
			for(int j=i+1;j<size;j++){
				if(*(num+i) > *(num+j)){
					int temp = *(num+j);
					*(num+j) = *(num+i);
					*(num+i) = temp;
				}
			}
		}

	return num;
	}
}

int *insert(int *num,int size){
	if(size<=0){
		return NULL;
	}
	else{
		int i,j;
		for(i=0;i<size;i++){
			for( j=i;j>0;j--){
				if(*(num+j)<*(num+j-1)){
					int temp;
					temp =*(num+j);
					*(num+j) = *(num+j-1);
					*(num+j-1) =temp;
				}
				else 
					break;
			}

		}
	}

	return num;
}

int *shell(int *num,int size) {
        int j;
        for (int gap = size/2; gap >  0; gap /= 2) {
            for (int i = gap; i < size; i++) {
                int tmp = *(num+i);
                for (j = i; j >= gap && (tmp < *(num+j - gap)); j -= gap) {
                    *(num+j) = *(num +j - gap);
                }
                *(num+j) = tmp;
            }
        }
        return num;
    }

int *quick(int *num,int low,int high){
	if(low>=high){
		return num;
	}

	int key = *(num+low);
	int i =low;
	int j = high;
	int temp;
	while(i!=j){
		while(key <= *(num+j) && i<j)
			j--;
		while(key >= *(num+i) && i<j)
			i++;
		if(i<j){
			temp = *(num+j);
			*(num+j) =*(num+i);
			*(num+i) = temp;
		}
	}
	temp = *(num+low);
	*(num+low) = *(num+i);
	*(num+i) = temp;

	num = quick(num,low,i-1);
	num = quick(num,i+1,high);

	return num;

}

int* shiftDown(int *num,int achor,int size){
	assert(size>0);

	int data = *(num+achor-1);

	int i = achor;

	while( (2*i)<=size){
		if( (2*i)+1 <=size){
			if( *(num+(2*i)) > *(num+(2*i)-1) ){
				if( *(num+(2*i)) >data){
					int temp = *(num+(2*i));
					*(num+(2*i)) = data;
					*(num+achor-1) = temp;

					achor = 2*i+1;
				}
				else
					break;
			}
			else{
				if( *(num+(2*i)-1) >data){
					int temp = *(num+(2*i)-1);
					*(num+(2*i)-1) = data;
					*(num+achor-1) = temp;

					achor = 2*i;
				}
				else
					break;
			}
		}
		else{
			if( *(num+(2*i)-1) >data){
					int temp = *(num+(2*i)-1);
					*(num+(2*i)-1) = data;
					*(num+achor-1) = temp;

					achor = 2*i;
				}
				else
					break;
		}
		i=achor;
	}
	return num;
}

int* buildHeap(int *num,int size){
	int i=0;

	assert(size>0);
	i= size/2;
	
	while(i>0 ){
		shiftDown(num,i,size);	
		i--;
	}
	return num;
}

void shitDown(int *num,int size){

	int data = *num;
	*num = *(num+size-1);

	*(num+size-1) = data;

	size--;
	
	if(size>0){
	
		int i=1,j=0;
	
		while(2*i<=size){
			j=0;
			if( *(num+i-1) <*(num+2*i-1)){
				int temp = *(num+2*i-1);
				*(num+2*i-1) = *(num+i-1);
				*(num+i-1) =temp;
				j=2*i;
			}
			
			if(2*i+1 <=size){

				if( *(num+i-1) <*(num+2*i)){
					int temp = *(num+2*i);
					*(num+2*i) = *(num+i-1);
					*(num+i-1) =temp;
					j=2*i+1;
				}
			}
			if(j==0)
				break;
			else
				i=j;
		}
	}
}

int* sortHeap(int *num,int size){
	buildHeap(num,size);

	while(size>0){
		shitDown(num,size);
		size--;
	}
	return num;
}


int main(){

	int data[10] = {13,22,16,62,41,17,19,30,15,28};

	int *point;

	point =data;
	
	cout<<"1-insert 2-shell 3- bintree 4-quick 5-heap: ";
	int choose = 0;
	cin>>choose;

	switch(choose){

	case 1:
		point =insert(point,10);
		show(point,10);
		break;
	
	case 2:
		point = shell(point,10);
		show(point,10);
		break;
	
	case 3:
		point=heapSort(point,10);
		show(point,10);
		break;

	case 4:
		point=quick(point,0,9);
		show(point,10);
		break;

	case 5:
		
		point = sortHeap(point,10);
		show(point,10);
		break;

	default:
		break;
	}
	/*
	HD *root;

	root = NULL;
	int i=0;
	while(i<10){
		root = creatHeap(data[i],root);
		i++;
	}
	showHeap(root);

	vector<vector<int> >* q;
	q=levelOrder(root);

	i=0;
	while(i<q->size()){
		int j=0;
		while(j< (q->at(i)).size() ){
			cout<<(q->at(i)).at(j)<<"\t";
			j++;
		}
		cout<<"\n";
		i++;
	}
	*/
	return 0;
}



