#include "demo.h"
#include <cstdlib>
#include <ctime>

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

	int dataList[10] = {20,40,30,35,50,36,21,32,26};

	int i=0;
	while(i<6){
		root = insertToTree(root,dataList[i]);
		i++;
	}

	/*srand(unsigned(time(0)));

	const int MAX = 10000000;
	const int MIN = 100;

	int a = 0;
	//int n = 10000;
	for(int i=0;i<MAX;i++){
		a = (rand()%(MAX-MIN+1) +MIN);

		root = insertToTree(root,a);
	}*/

	/*root = (root->deleteNode(*root,8));
	root = (root->deleteNode(*root,15));
	root = (root->deleteNode(*root,6));
	root = (root->deleteNode(*root,12));*/
	root = root->deleteNode(*root,10);
	//root = insertToTree(root,10);
	root = root->deleteNode(*root,20);
	root = root->deleteNode(*root,30);

	root = insertToTree(root,42);
	root = root->deleteNode(*root,35);
	
	root->preOrder(root);
	cout<<"\n";
	root->middleOrder(root);
	cout<<"\n";

	root = root->deleteNode(*root,36);

	root->preOrder(root);
	cout<<"\n";
	root->middleOrder(root);
	cout<<"\n";

	return 1;
}
