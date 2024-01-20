#ifndef _MY_TREEFILE
#define _MY_TREEFILE
#include <iostream>
#include <string>
using namespace std;

class Node{

public:

	int data;
	string colour;
	Node* left;
	Node* right;
	Node* parent;

	Node(int value){
		left = NULL;
		parent=NULL;
		right=NULL;

		data = value;
		colour = "red";
	}
};

class Tree{
public:
	Node *leaf;
	Node *NIL;

	Tree(){
		NIL = new Node(0);
		NIL->colour = "black";

		leaf = NIL;
	}

	Node* insertLeaf(Tree *t,Node *root,Node *node);
	void preOrder(Node *root);
	void inOrder(Node *root);

	Node *searchNode(Tree *t,Node *root,int value);

	Node* arrangeNode(Tree *t,Node *root,int value);

	Node* rotateLeftRight(Node *root);
	Node* rotateRightLeft(Node *root);
	
	Node* rotateLeftLeft(Node *root);
	Node* rotateRightRight(Node *root);
	
	void deleteNode(Tree *t,Node *z);
	Node* successorNode(Tree *t, Node *x);

	void deleteArrange(Tree *t,Node *x);
	
	void left_rotate(Tree *t, Node *x);
	void right_rotate(Tree *t, Node *x);
	//void rb_transplant(Tree *t, Node *u, Node *v);

};

Node* Tree::insertLeaf(Tree *t,Node *root,Node *node){

	if(root == NIL){
		root = node;
		root->left = NIL;
		root->right = NIL;
		root->parent = NIL;
	}
	else{
		if(root->data > node->data){
			root->left = insertLeaf(t,root->left,node);
			root->left->parent = root;
		}
		else if(root->data < node->data){
			root->right = insertLeaf(t,root->right,node);
			root->right->parent =root;
		}
	}

	return root;
}

Node* Tree::searchNode(Tree* t,Node* root, int value){
	Node *pCur = root;
  while (pCur != t->NIL) {
    if (value < pCur->data) {
      if (pCur->left == t->NIL)
        break;
      else
        pCur = pCur->left;
    } 
    else if (value == pCur->data) {
      break;
    } 
    else {
      if (pCur->right == t->NIL)
        break;
      else
        pCur = pCur->right;
    }
  }
  return pCur;
}

Node* Tree::rotateLeftRight(Node *root){
	Node *parentCur = root->parent;

	Node *pCur = root->right;

	parentCur->left = pCur->right;
	(pCur->right)->parent = parentCur;

	root->right = pCur->left;
	(pCur->left)->parent = root;
	
	pCur->left = root;
	pCur->right = parentCur;

	pCur->colour = "red";
	root->colour ="black";
	parentCur->colour = "black";

	pCur->parent = parentCur->parent;

	root->parent = pCur;
	parentCur->parent  =pCur;
	
	return pCur;
}

Node* Tree::rotateRightLeft(Node *root){

	Node *parentCur = root->parent;

	Node *pCur = root->left;

	parentCur->right = pCur->left;
	(pCur->left)->parent = parentCur;

	root->left = pCur->right;

	(pCur->right)->parent = root;

	pCur->left = parentCur;
	pCur->right = root;

	pCur->colour = "red";
	root->colour ="black";
	parentCur->colour = "black";

	pCur->parent = parentCur->parent;

	root->parent = pCur;
	parentCur->parent  =pCur;

	return pCur;
}

Node* Tree::rotateLeftLeft(Node *root){
	Node *parentCur = root->parent;
	
	Node *pCur = root->left;

	parentCur->left = root->right;
	
	(root->right)->parent = parentCur;
	
	root->right = parentCur;

	pCur->colour = "black";
	root->colour ="red";
	parentCur->colour = "black";

	root->parent = parentCur->parent;

	parentCur->parent = root;
	
	return root;
}

Node* Tree::rotateRightRight(Node *root){
	Node *parentCur = root->parent;
	
	Node *pCur = root->right;

	parentCur->right = root->left;
	
	(root->left)->parent = parentCur;

	root->left = parentCur;

	pCur->colour = "black";
	root->colour ="red";
	parentCur->colour = "black";

	root->parent = parentCur->parent;

	parentCur->parent = root;
	
	return root;
}

Node* Tree::arrangeNode(Tree *t,Node *root,int value){//root is middle node in CMU example
	Node *pCur;

	Node *parentCur;
	parentCur = root->parent;

	if(parentCur->data > root->data){

		if(value > root->data){
	
			pCur = root->right;
	
			if(root->colour =="red" && pCur->colour =="red"){
	
				parentCur = rotateLeftRight(root);
			}
	
			if(parentCur->parent ==t->NIL)
				parentCur->colour ="black";
		}
		else if(value < root->data){
	
			pCur = root->left;
	
			if(root->colour =="red" && pCur->colour =="red"){
	
				parentCur = rotateLeftLeft(root);
				
			}
	
			if(parentCur->parent ==t->NIL)
				parentCur->colour ="black";
		}
	}
	else{
		if(value > root->data){
		
			pCur = root->right;
	
			if(root->colour =="red" && pCur->colour =="red"){
	
				parentCur = rotateRightRight(root);
			}
	
			if(parentCur->parent ==t->NIL)
				parentCur->colour ="black";
		}
		else if(value < root->data){
			
			pCur = root->left;
			
			if(root->colour =="red" && pCur->colour =="red"){
	
				parentCur = rotateRightLeft(root);
			}
	
			if(parentCur->parent ==t->NIL)
				parentCur->colour ="black";
		}
	}
	return parentCur;

}

/*void Tree::rb_transplant(Tree *t, Node *u, Node *v) {
	if(u->parent == t->NIL)
	  t->leaf = v;
	else if(u == u->parent->left)
	  u->parent->left = v;
	else
	  u->parent->right = v;
	v->parent = u->parent;
}*/

Node* Tree::successorNode(Tree *t, Node *x) {
	while(x->right != t->NIL)
	  x = x->right;
	return x;
}

void Tree::deleteNode(Tree *t, Node *z) {
	Node *y;
	if(z->left == t->NIL || z->right ==t->NIL)
		y=z;
	else
		y = t->successorNode(t,z);

	Node *x;

	if(y->left !=t->NIL)
		x = y->left;
	else
		x = y->right;

	x->parent = y->parent;

	if(y->parent == t->NIL)
		t->leaf = x;
	else{ 
		if(y == y->parent->left)
			y->parent->left =x;
		else
			y->parent->right =x;
	}

	if(y!=z)
		z->data = y->data;

	if(y->colour =="black"){
		t->deleteArrange(t,x);
	}

}

void Tree::deleteArrange(Tree *t,Node *x){

	while(x != t->leaf && x->colour == "black") {
  		if(x == x->parent->left) {
    		Node *w = x->parent->right;
    		if(w->colour == "red") {
      			w->colour = "black";
      			x->parent->colour = "red";
      			left_rotate(t, x->parent);
      			w = x->parent->right;
    		}
    		if(w->left->colour == "black" && w->right->colour == "black") {
      			w->colour = "red";
      			x = x->parent;
    		}
    		else {
      			if(w->right->colour == "black") {
      			  	w->left->colour = "black";
      			  	w->colour = "red";
      			  	right_rotate(t, w);
      			  	w = x->parent->right;
      			}
      			w->colour = x->parent->colour;
      			x->parent->colour = "black";
      			w->right->colour = "black";
      			left_rotate(t, x->parent);
      			x = t->leaf;
    		}
  		}
  		else if(x == x->parent->right){
    		Node *w = x->parent->left;
    		if(w->colour == "red") {
      			w->colour = "black";
      			x->parent->colour = "red";
      			right_rotate(t, x->parent);
      			w = x->parent->left;
    		}
    		if(w->right->colour == "black" && w->left->colour == "black") {
      			w->colour = "red";
      			x = x->parent;
    		}
    		else{
      			if(w->left->colour == "black") {
        			w->right->colour = "black";
        			w->colour = "red";
        			left_rotate(t, w);
        			w = x->parent->left;
      			}
      			w->colour = x->parent->colour;
      			x->parent->colour = "black";
      			w->left->colour = "black";
      			right_rotate(t, x->parent);
      			x = t->leaf;
    		}
  		}
  		else{

  			break;
  		}
	}
	x->colour = "black";
}

void Tree::left_rotate(Tree *t, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if(y->left != t->NIL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == t->NIL) { //x is root
      t->leaf = y;
    }
    else if(x == x->parent->left) { //x is left child
      x->parent->left = y;
    }
    else { //x is right child
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void Tree::right_rotate(Tree *t, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if(y->right != t->NIL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == t->NIL) { //x is root
      t->leaf = y;
    }
    else if(x == x->parent->right) { //x is left child
      x->parent->right = y;
    }
    else { //x is right child
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void Tree::preOrder(Node *root){
	if(root!=NIL){
		cout<<root->data<<'-'<<root->colour<<' ';
		preOrder(root->left);
		preOrder(root->right);
	}
}

void Tree::inOrder(Node *root){
	if(root!=NIL){
		inOrder(root->left);
		cout<<root->data<<'-'<<root->colour<<' ';
		inOrder(root->right);
	}
}

#endif