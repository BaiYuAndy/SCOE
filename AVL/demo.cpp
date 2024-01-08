#include <iostream>
#include "demo.h"

using namespace std;

int main(){
	Node *root;
	
	root = new Node(10);
	
	/*int data=0;
	data = root->height(root);

	cout<<data;

	Node *node;
	node = root->sreachNode(11);
	cout<<node->data;*/

	root->insertNode(11);
	root->insertNode(12);

	/*
	root->insertNode(9);
	cout<<root->isRebalance(root);*/

	root = root->rotateLeft(root);

	root = root->insertNode(root,9);
	root = root->insertNode(root,8);
	//cout<<root->isRebalance(root);
	
	//root->left = root->rotateRight(root->left);

	root = root->insertNode(root,15);
	root = root->insertNode(root,20);
	root = root->insertNode(root,24);

	root = root->insertNode(root,17);
	root = root->insertNode(root,16);

	root->preOrder(root);
	cout<<"\n";
	root->middleOrder(root);
	cout<<"\n";

	return 1;
}

