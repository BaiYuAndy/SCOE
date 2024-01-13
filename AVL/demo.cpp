#include <iostream>
#include "demo.h"

using namespace std;

int main(){
	Node *root = NULL;
	int a[10] ={14,78,8,90,21,43,3,12,1,24};
	/*root = new Node(10);

	for(int i=1;i<=7;i++){
		root = root->insertNode(root,10+i);
	}*/

	for(int i=0;i<10;i++){
		root = root->insertNode(root,a[i]);
	}

	/*root->preOrder(root);
	cout<<"\n";
	root->middleOrder(root);
	cout<<"\n";*/
	
	/*Node *p = root->getNodeByValue(root,12);

	cout<<p->data<<"\n";

	Node *parent = p->parent;

	cout<<parent->data<<"\n";*/

	
	root = root->insertNode(root,9);
	root = root->insertNode(root,4);

	/*root->preOrder(root);
	cout<<"\n";
	root->middleOrder(root);
	cout<<"\n";*/

	/*root = root->delNodeByValue(root,90);
	root = root->delNodeByValue(root,1);
	root = root->delNodeByValue(root,9);
	root = root->delNodeByValue(root,3);*/
	root = root->delNodeByValue(root,8);
	root = root->delNodeByValue(root,43);
	root = root->delNodeByValue(root,21);

	root->preOrder(root);
	cout<<"\n";
	root->middleOrder(root);
	cout<<"\n";

	root = root->delNodeByValue(root,14);

	root->preOrder(root);
	cout<<"\n";
	root->middleOrder(root);
	cout<<"\n";

	return 1;

}

