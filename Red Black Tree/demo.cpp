#include "demo.h"

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

	Node *root = new Node(15);
	root->color = "black";

	int dataList[8] = {10,12,8,6,16,18,24,19};

	/*int i=0;
	while(i<8){
		root = insertToTree(root,dataList[i]);
		i++;
	}*/

	for(int i=1;i<20;i++){
		root = insertToTree(root,i+15);
	}

	/*Node *pN;
	pN = addToTree(*root,10);
	root = reBalance(pN,10);

	pN = addToTree(*root,12);
	root = reBalance(pN,12);

	pN = addToTree(*root,8);
	root = reBalance(pN,8);

	pN = addToTree(*root,6);
	root = reBalance(pN,6);

	pN =addToTree(*root,16);
	root = reBalance(pN,16);

	pN =addToTree(*root,18);
	root = reBalance(pN,18);

	pN=addToTree(*root,24);
	root = reBalance(pN,24);

	pN=addToTree(*root,19);
	root = reBalance(pN,19);*/

	
	root->preOrder(root);
	cout<<"\n";
	root->middleOrder(root);
	cout<<"\n";

	return 1;
}
