#ifndef _MY_HEADFILE
#define _MY_HEADFILE
#include <iostream>
#include <string>
using namespace std;

class Node{
public:
	string color;
	int data;

	Node* left;
	Node* right;
	Node* parent;

	Node(int value){
		data = value;
		left = NULL;
		right = NULL;
		parent = NULL;
		color = "red";
	}

	Node *insertNode(Node* root,int value);
	Node *findInsertPosition(Node *root,int value);

	void preOrder(Node* root);
	void middleOrder(Node* root);

	Node* arrangeNode(Node *root,int value);

	Node* rotateLeftRight(Node *root);
	Node* rotateRightLeft(Node *root);
	
	Node* rotateLeftLeft(Node *root);
	Node* rotateRightRight(Node *root);
};

void Node::preOrder(Node* root){
	if(root!=NULL){
		cout<<root->data<<'-'<<root->color<<'	';

		preOrder(root->left);
		preOrder(root->right);
	}
}

void Node::middleOrder(Node* root){
	if(root!=NULL){

		middleOrder(root->left);
		cout<<root->data<<'-'<<root->color<<'	';
		middleOrder(root->right);
	}
}

Node* Node::findInsertPosition(Node *root,int value){
	Node *pCur =NULL;
	if(root ==NULL)
		return NULL;
	
	if(root->data > value){
		if(root->left ==NULL){
			return root;
		}
		else{
			pCur =  root->findInsertPosition(root->left,value);
		}
	}
	else if(root->data < value){
		if(root->right ==NULL){
			return root;
		}
		else{
			pCur =  root->findInsertPosition(root->right,value);
		}
	}
	else{
		return root;
	}

	return pCur;
}

Node* Node::insertNode(Node* root,int value){
	if(root ==NULL){
		root = new Node(value);
	}
	else if(root->data >value){
		root->left = root->insertNode(root->left,value);

		(root->left)->parent = root;
	}
	else if(root->data <value){
		root->right = root->insertNode(root->right,value);

		(root->right)->parent = root;
	}
	else{
		root->data = value;
	}

	return root;
}

Node* Node::arrangeNode(Node *root,int value){//root is middle node in CMU example
	Node *pCur;

	Node *parentCur;
	parentCur = root->parent;

	if(parentCur->data > root->data){

		if(value > root->data){
	
			pCur = root->right;
	
			if(root->color =="red" && pCur->color =="red"){
	
				parentCur = root->rotateLeftRight(root);
			}
	
			if(parentCur->parent ==NULL)
				parentCur->color ="black";
		}
		else if(value < root->data){
	
			pCur = root->left;
	
			if(root->color =="red" && pCur->color =="red"){
	
				parentCur = root->rotateLeftLeft(root);
				
			}
	
			if(parentCur->parent ==NULL)
				parentCur->color ="black";
		}
	}
	else{
		if(value > root->data){
		
			pCur = root->right;
	
			if(root->color =="red" && pCur->color =="red"){
	
				parentCur = root->rotateRightRight(root);
			}
	
			if(parentCur->parent ==NULL)
				parentCur->color ="black";
		}
		else if(value < root->data){
			
			pCur = root->left;
			
			if(root->color =="red" && pCur->color =="red"){
	
				parentCur = root->rotateRightLeft(root);
			}
	
			if(parentCur->parent ==NULL)
				parentCur->color ="black";
		}
	}
	return parentCur;

}

Node* Node::rotateLeftRight(Node *root){
	Node *parentCur = root->parent;

	Node *pCur = root->right;

	parentCur->left = pCur->right;

	root->right = pCur->left;
	
	pCur->left = root;
	pCur->right = parentCur;

	pCur->color = "red";
	root->color ="black";
	parentCur->color = "black";

	pCur->parent = parentCur->parent;

	root->parent = pCur;
	parentCur->parent  =pCur;

	return pCur;
}

Node* Node::rotateRightLeft(Node *root){

	Node *parentCur = root->parent;

	Node *pCur = root->left;

	parentCur->right = pCur->left;

	root->left = pCur->right;
	
	pCur->left = parentCur;
	pCur->right = root;

	pCur->color = "red";
	root->color ="black";
	parentCur->color = "black";

	pCur->parent = parentCur->parent;

	root->parent = pCur;
	parentCur->parent  =pCur;

	return pCur;
}

Node* Node::rotateLeftLeft(Node *root){
	Node *parentCur = root->parent;
	
	Node *pCur = root->left;

	parentCur->left = root->right;
	
	root->right = parentCur;

	pCur->color = "black";
	root->color ="red";
	parentCur->color = "black";

	root->parent = parentCur->parent;

	parentCur->parent = root;
	
	return root;
}

Node* Node::rotateRightRight(Node *root){
	Node *parentCur = root->parent;
	
	Node *pCur = root->right;

	parentCur->right = root->left;
	
	root->left = parentCur;

	pCur->color = "black";
	root->color ="red";
	parentCur->color = "black";

	root->parent = parentCur->parent;

	parentCur->parent = root;
	
	return root;
}

#endif
