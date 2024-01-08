#ifndef _MY_HEADFILE
#define _MY_HEADFILE

#include <cmath>
using namespace std;

class Node{
public:
	int data;

	Node *left;
	Node *right;

	int height(Node *root);

	bool isRebalance(Node *root);

	Node* sreachNode(int value);

	void insertNode(int value);

	Node* insertNode(Node *root,int value);

	Node* rebalanceRight(Node *root);
	Node* rebalanceLeft(Node *root);

	Node* rotateLeft(Node *root);
	Node* rotateRight(Node *root);

	Node(int value){
		data = value;
		left =NULL;
		right=NULL;
	}

	void preOrder(Node* root);
	void middleOrder(Node* root);
};

void Node::preOrder(Node* root){
	if(root!=NULL){
		cout<<root->data<<' ';

		preOrder(root->left);
		preOrder(root->right);
	}
}

void Node::middleOrder(Node* root){
	if(root!=NULL){

		middleOrder(root->left);
		cout<<root->data<<' ';
		middleOrder(root->right);
	}
}

int Node::height(Node *root){
  int h = 0;
  if(root != NULL)
  {
    int lHeight = height(root->left);
    int rHeight = height(root->right);
    int maxHeight = max(lHeight,rHeight);
    h = maxHeight + 1;
  }
  return h;
}

bool Node::isRebalance(Node *root){
	if(root->left==NULL &&root->right==NULL){
		return true;
	}
	else if(root->left!=NULL &&root->right!=NULL){
		int diff = root->height(root->left)-root->height(root->right);
		if(abs(diff) <=1)
			return true;
	}
	else if(root->left!=NULL){
		if(root->height(root->left) == 1)
			return true;
	}
	else{
		if(root->height(root->right) == 1)
			return true;
	}

	return false;
}

Node* Node::sreachNode(int value){
	Node *pCur = NULL;

	if(value <data){
		if(left!=NULL)
			pCur = left->sreachNode(value);
		else
			pCur = this;
	}
	else if(value >data){
		if(right!=NULL)
			pCur = right->sreachNode(value);
		else
			pCur = this;
	}
	else{
		pCur->data = value;
	}

	return pCur;
}

void Node::insertNode(int value){
	Node *pCur = sreachNode(value);
	
	if(pCur!=NULL){
		if(value < pCur->data){
			Node *pl = new Node(value);

			pCur->left = pl;
		}
		else if(value > pCur->data){
			Node *pr = new Node(value);

			pCur->right = pr;
		}
	}
}

Node* Node::insertNode(Node *root,int value){
	Node *pCur = root;
	if(pCur==NULL){
		pCur = new Node(value);
	}
	else if(value < pCur->data){
		pCur->left = pCur->insertNode(pCur->left,value);
		pCur = pCur->rebalanceLeft(pCur);
	}
	else if(value > pCur->data){
		pCur->right = pCur->insertNode(pCur->right,value);
		pCur = rebalanceRight(pCur);
	}

	return pCur;
}

Node* Node::rebalanceLeft(Node *root){
	Node *l = root->left;
	Node *r = root->right;

	int hl = height(l);
	int hr = height(r);

	if(hl >hr+1){

		if(height(l->left) > height(l->right)){

			root = root->rotateRight(root);

			return root;
		}
		else{
			root->left = (root->left)->rotateLeft(root->left);
			root = root->rotateRight(root);
			return root;
		}
	}
	else
		return root;
 }

 Node* Node::rebalanceRight(Node *root){
	Node *l = root->left;
	Node *r = root->right;

	int hl = height(l);
	int hr = height(r);

	if(hr >hl+1){

		if(height(r->left) < height(r->right)){
			
			root = root->rotateLeft(root);

			return root;
		}
		else{
			root->right = (root->right)->rotateRight(root->right);
			root = root->rotateLeft(root);
			return root;
		}
	}
	else
		return root;
 }

Node * Node::rotateLeft(Node *root){
	Node *cur;

	cur = root->right;
	root->right = cur->left;
	cur->left = root;

	return cur;
}

Node * Node::rotateRight(Node *root){
	Node *cur;

	cur = root->left;
	root->left = cur->right;
	cur->right = root;

	return cur;
}


#endif
