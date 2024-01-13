#ifndef _MY_HEADFILE
#define _MY_HEADFILE

#include <cmath>
using namespace std;

class Node{
public:
	int data;

	Node *left;
	Node *right;
	Node *parent;

	int height(Node *root);

	bool isRebalance(Node *root);

	Node* sreachNode(int value);

	void insertNode(int value);

	Node* insertNode(Node *root,int value);

	Node* rebalanceRight(Node *root);
	Node* rebalanceLeft(Node *root);

	Node* rotateLeft(Node *root);
	Node* rotateRight(Node *root);

	Node* getNodeByValue(Node *root,int value);

	Node* delNodeByValue(Node *root,int value);

	Node(int value){
		data = value;
		left =NULL;
		right=NULL;
		parent = NULL;
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
	
Node* Node::getNodeByValue(Node *root,int value){
	Node *pCur = NULL;

	if(root->data == value)
		pCur =root;
	else if(root->data > value)
		pCur = getNodeByValue(root->left,value);
	else if(root->data < value)
		pCur = getNodeByValue(root->right,value);

	return pCur;
}

Node* Node::delNodeByValue(Node *root,int value){
	Node *pCur = getNodeByValue(root,value);
	Node *parentCur = pCur->parent;

	if(pCur->left ==NULL && pCur->right==NULL){
	  if(parentCur!=NULL){
	  	if(parentCur->data > pCur->data)
	  		parentCur->left = NULL;
	  	else
	  		parentCur->right = NULL;
		}
		else{
			return NULL;
		}

	  delete(pCur);

	}
	else if(pCur->left!=NULL && pCur->right==NULL){
		if(parentCur!=NULL){
			if(parentCur->data > pCur->data)
	  		parentCur->left = pCur->left;
	  	else
	  		parentCur->right = pCur->left;

	  	(pCur->left)->parent = parentCur;
		}
		else{
			root = pCur->left;
			return root;
		}

	  delete(pCur);
	}
	else if(pCur->left==NULL && pCur->right !=NULL){
		if(parentCur!=NULL){
			if(parentCur->data > pCur->data)
	  		parentCur->left = pCur->right;
	  	else
	  		parentCur->right = pCur->right;
	
	  	(pCur->right)->parent = parentCur;
	  }
		else{
			root = pCur->right;
			return root;
		}

	  delete(pCur);
	}
	else{
		if(pCur->left!=NULL){
			Node* pNext = pCur->left;

			while(pNext->right!=NULL){
				pNext = pNext->right;
			}
			
			pCur->data = pNext->data;
			parentCur = pNext->parent;
			if(parentCur!=NULL){
				if(parentCur->data > pCur->data){
					if(pNext->left!=NULL)
						parentCur->left = pNext->left;
	  			else
	  				parentCur->left = NULL;
				}
	  		else{
	  			if(pNext->left!=NULL)
						parentCur->right = pNext->left;
					else
	  				parentCur->right = NULL;
	  		}
	  	}
			//delete(pNext);
			//cout<<parentCur->data<<endl;

			
		}
	}

	while(parentCur !=NULL ){

		if(isRebalance(parentCur)){

			parentCur=parentCur->parent;
		}
		else{
			
			int hl = parentCur->height(parentCur->left);
			int hr = parentCur->height(parentCur->right);

			if(hl+1 <hr){
				parentCur = parentCur->rotateLeft(parentCur);

				if(parentCur->parent !=NULL){
					if((parentCur->parent)->data > parentCur->data){
	  				(parentCur->parent)->left = parentCur;
					}
	  			else{
	  				(parentCur->parent)->right = parentCur;
	  			}
				}
				
				parentCur = parentCur->parent;

			}
			else if(hl >hr+1){

				parentCur = parentCur->rotateRight(parentCur);
				
				if(parentCur->parent !=NULL){
					if((parentCur->parent)->data > parentCur->data){
	  				(parentCur->parent)->left = parentCur;
					}
	  			else{
	  				(parentCur->parent)->right = parentCur;
	  			}
				}
				
				parentCur = parentCur->parent;


			}

		}
	}
	return root;

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
		(pCur->left)->parent = pCur;
	}
	else if(value > pCur->data){
		pCur->right = pCur->insertNode(pCur->right,value);
		pCur = rebalanceRight(pCur);
		(pCur->right)->parent = pCur;
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
	
	if(cur->left!=NULL){
		(cur->left)->parent = root;
	}

	cur->left = root;
	cur->parent = root->parent;

	root->parent = cur;

	return cur;
}

Node * Node::rotateRight(Node *root){
	Node *cur;

	cur = root->left;

	root->left = cur->right;

	if(cur->right!=NULL){
		(cur->right)->parent = root;
	}

	cur->right = root;
	cur->parent = root->parent;

	root->parent = cur;

	return cur;
}


#endif
