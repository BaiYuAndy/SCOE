#include "demo.h"
#include <cstdlib>
#include <ctime>

#define N 50

using namespace std;

Node *addToTree(Node& root,int value){
	Node *pN = root.findInsertPosition(&root,value);
	
	if(pN!=NULL){
		
		root = *(root.insertNode(&root,value));
	}

	return pN;
}

Node *reBalance(Node *pN,int value){

	while(pN->parent !=NULL){
		pN = pN->arrangeNode(pN,value);

		if(pN->parent!=NULL){
			if( (pN->parent)->data> pN->data ){
				(pN->parent)->left = pN;
			}
			else if( (pN->parent)->data < pN->data ){
				(pN->parent)->right = pN;
			}
			pN = pN->parent;
		}

	}

	return pN;
}

Node* insertToTree(Node *root,int value){

	Node *pN;
	pN = addToTree(*root,value);
	root = reBalance(pN,value);

	return root;
}



int main(){

	Node *root = new Node(10);
	root->color = "black";
	
	//int dataList[N] = {20,40,30,35,50,36,21,32,26,15};

	/*int i=1;
	int n =10;
	while(i<n){
		root = insertToTree(root,i+10);
		i++;
	}
	*/

	srand(unsigned(time(0)));

	const int MAX = 10000000;
	const int MIN = 1;

	int a = 0;
		for(int i=0;i<MAX;i++){
		a = (rand()%(MAX-MIN+1) +MIN);
		
		root = insertToTree(root,a);
		
	}

	/*for(i=1;i<10;i++){
		
		root = root->deleteNode(*root,i+10);
		
	}*/
	
	//Node *pN = root->searchNode(root,25);
	//cout<<pN->left->data;
	/*
	root->preOrder(root);
	cout<<"\n************\n";
	root->middleOrder(root);
	cout<<"\n";
	*/
	return 1;
}
