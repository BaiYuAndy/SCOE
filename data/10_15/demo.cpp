#include <cstdlib>
#include <ctime>
#include "tree.h"

#define N 50

using namespace std;

Node *addToTree(Tree *root,int value){
	Node *pN = new Node(value);
	
	root->leaf = root->insertLeaf(root,root->leaf,pN);

	pN = root->searchNode(root,root->leaf,value);

	return pN;
}

Node *reBalance(Tree* root,Node *pN,int value){

	while(pN->parent !=root->NIL){
		pN = root->arrangeNode(root,pN,value);

		if(pN->parent!=root->NIL){
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

void insertToTree(Tree *root,int value){

	Node *pN;
	pN = addToTree(root,value);
	//cout<<pN->data<<' '<<pN->parent->data<<endl;
	if(pN->parent!=root->NIL)
		root->leaf = reBalance(root,pN->parent,value);
}

int main(){

	Tree *root = new Tree();

	//int dataList[10] = {20,40,30,35,50,36,21,32,26,15};

	int i=1;
	while(i<10000000){
		//insertToTree(root,dataList[i]);
		insertToTree(root,i);

		i++;
	}
	
  	Node *pD;
  	for(int i=1;i<10000002;i++){
    	pD =root->searchNode(root,root->leaf,i);
    
      	if(pD !=root->NIL)
      		root->deleteNode(root, pD);
    
  	}

	root->preOrder(root->leaf);
	cout<<"\n************\n";
	root->inOrder(root->leaf);
	cout<<"\n";
	
	
	
	/*srand(unsigned(time(0)));

	const int MAX = 10000000;
	const int MIN = 1;

	int a = 0;
	for(int i=0;i<MAX;i++){
		a = (rand()%(MAX-MIN+1) +MIN);
		
		insertToTree(root,a);
	}
	*/
	/*for(i=1;i<10;i++){
		
		root = root->deleteNode(*root,i+10);
		
	}*/
	
	//Node *pN = root->searchNode(root,25);
	//cout<<pN->left->data;
	/*
	
	*/
	return 1;
}
