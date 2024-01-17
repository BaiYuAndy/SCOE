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
		color = "red";
		left = NULL;
		right = NULL;
		parent = NULL;

		data = value;
	}
};

class RBT{
public:
	Node *root;
	Node *NIL;

	RBT(){
		NIL = new Node(0);
		NIL->color = "black";

		root = NIL;
	}

	RBT* insertNode(RBT* t,Node *z);
	void inOrder(RBT *t, Node *n);
	void preOrder(RBT *t, Node *n);

	void insertion_fixup(RBT *t, Node *z);
	void left_rotate(RBT *t, Node *x);
	void right_rotate(RBT *t, Node *x);
	void rb_delete_fixup(RBT *t, Node *x);
	void rb_delete(RBT *t, Node *x);

	void rb_transplant(RBT *t, Node *u, Node *v);

	Node* searchNode(RBT* t, Node* root,int value);

	Node* minimum(RBT *t, Node *x);
};

RBT* RBT::insertNode(RBT* t,Node *z){
	Node *y = t->NIL;
	Node *temp = t->root;

	while(temp != t->NIL) {
  		y = temp;
  		if(z->data < temp->data)
    		temp = temp->left;
  		else
    		temp = temp->right;
	}
	
	z->parent = y;

	if(y == t->NIL) { //newly added node is root
	 	t->root = z;
	}
	else if(z->data < y->data) //data of child is less than its parent, left child
	  	y->left = z;
	else
	  	y->right = z;
	
	z->right = t->NIL;
	z->left = t->NIL;

	t->insertion_fixup(t, z);

	return t;
}

void RBT::inOrder(RBT *t, Node *n) {
	if(n != t->NIL) {
  		inOrder(t, n->left);
  		cout<<n->data<<'-'<<n->color<<'	';
  		inOrder(t, n->right);
	}
}

void RBT::preOrder(RBT *t, Node *n) {
	if(n != t->NIL) {
		cout<<n->data<<'-'<<n->color<<'	';
  		preOrder(t, n->left);
  		preOrder(t, n->right);
	}
}

Node* RBT::searchNode(RBT* t,Node* root, int value){
	if(root == t->NIL)
		return NULL;

	Node *pCur;
	if(value == root->data)
		return root;
	else if(value < root->data)
		pCur = searchNode(t,root->left,value);
	else if(value > root->data)
		pCur = searchNode(t,root->right,value);

	return pCur;
}

void RBT::left_rotate(RBT *t, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if(y->left != t->NIL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == t->NIL) { //x is root
      t->root = y;
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

void RBT::right_rotate(RBT *t, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if(y->right != t->NIL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == t->NIL) { //x is root
      t->root = y;
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

void RBT::insertion_fixup(RBT *t, Node *z) {
    while(z->parent->color == "red") {
      if(z->parent == z->parent->parent->left) { //z.parent is the left child
    
        Node *y = z->parent->parent->right; //uncle of z
    
        if(y->color == "red") { //case 1
          z->parent->color = "black";
          y->color = "black";
          z->parent->parent->color = "red";
          z = z->parent->parent;
        }
        else { //case2 or case3
          if(z == z->parent->right) { //case2
            z = z->parent; //marked z.parent as new z
            left_rotate(t, z);
          }
          //case3
          z->parent->color = "black"; //made parent black
          z->parent->parent->color = "red"; //made parent red
          right_rotate(t, z->parent->parent);
        }
      }
      else { //z.parent is the right child
        Node *y = z->parent->parent->left; //uncle of z
    
        if(y->color == "red") {
          z->parent->color = "black";
          y->color = "black";
          z->parent->parent->color = "red";
          z = z->parent->parent;
        }
        else {
          if(z == z->parent->left) {
            z = z->parent; //marked z.parent as new z
            right_rotate(t, z);
          }
          z->parent->color = "black"; //made parent black
          z->parent->parent->color = "red"; //made parent red
          left_rotate(t, z->parent->parent);
        }
      }
    }
    t->root->color = "black";
}

void RBT::rb_transplant(RBT *t, Node *u, Node *v) {
	if(u->parent == t->NIL)
	  t->root = v;
	else if(u == u->parent->left)
	  u->parent->left = v;
	else
	  u->parent->right = v;
	v->parent = u->parent;
}

Node* RBT::minimum(RBT *t, Node *x) {
	while(x->left != t->NIL)
	  x = x->left;
	return x;
}

void RBT::rb_delete(RBT *t, Node *z) {
	Node *y = z;
	Node *x;
	string y_orignal_color = y->color;

	if(z->left == t->NIL) {
  		x = z->right;
  		rb_transplant(t, z, z->right);
	}
	else if(z->right == t->NIL) {
  		x = z->left;
  		rb_transplant(t, z, z->left);
	}
	else {
  		y = minimum(t, z->right);
  		y_orignal_color = y->color;
  		x = y->right;
  		if(y->parent == z) {
    		x->parent = z;
  		}
  		else {
    		rb_transplant(t, y, y->right);
    		y->right = z->right;
    		y->right->parent = y;
  		}
  	
  		rb_transplant(t, z, y);
  		y->left = z->left;
  		y->left->parent = y;
  		y->color = z->color;
	}
	if(y_orignal_color == "black")
  		rb_delete_fixup(t, x);
}

void RBT::rb_delete_fixup(RBT *t, Node *x) {
	while(x != t->root && x->color == "black") {
  		if(x == x->parent->left) {
    		Node *w = x->parent->right;
    		if(w->color == "red") {
      			w->color = "black";
      			x->parent->color = "red";
      			left_rotate(t, x->parent);
      			w = x->parent->right;
    		}
    		if(w->left->color == "black" && w->right->color == "black") {
      			w->color = "red";
      			x = x->parent;
    		}
    		else {
      			if(w->right->color == "black") {
      			  	w->left->color = "black";
      			  	w->color = "red";
      			  	right_rotate(t, w);
      			  	w = x->parent->right;
      			}
      			w->color = x->parent->color;
      			x->parent->color = "black";
      			w->right->color = "black";
      			left_rotate(t, x->parent);
      			x = t->root;
    		}
  		}
  		else {
    		Node *w = x->parent->left;
    		if(w->color == "red") {
      			w->color = "black";
      			x->parent->color = "red";
      			right_rotate(t, x->parent);
      			w = x->parent->left;
    		}
    		if(w->right->color == "black" && w->left->color == "black") {
      			w->color = "red";
      			x = x->parent;
    		}
    		else{
      			if(w->left->color == "black") {
        			w->right->color = "black";
        			w->color = "red";
        			left_rotate(t, w);
        			w = x->parent->left;
      			}
      			w->color = x->parent->color;
      			x->parent->color = "black";
      			w->left->color = "black";
      			right_rotate(t, x->parent);
      			x = t->root;
    		}
  		}
	}
	x->color = "black";
}

#endif

