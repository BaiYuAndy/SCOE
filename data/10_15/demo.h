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

	Node* searchNode(Node *root ,int value);

	Node* deleteNode(Node &root,int value);

	Node* successorNode(Node *root);

	Node* deleteArrange(Node *root,Node* pReplace,bool position);

	Node* rolateDelLeft(Node *root,int value);

	Node* rolateDelRight(Node *root,int value);
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

Node* Node::searchNode(Node *root,int value){
	Node *pCur =NULL;
	if(root ==NULL)
		return NULL;
	
	if(root->data > value){
		if(root->left ==NULL){
			return NULL;
		}
		else{
			pCur =  root->searchNode(root->left,value);
		}
	}
	else if(root->data < value){
		if(root->right ==NULL){
			return NULL;
		}
		else{
			pCur =  root->searchNode(root->right,value);
		}
	}
	else{
		return root;
	}

	return pCur;
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

	if(pCur->right !=NULL){
		parentCur->left = pCur->right;
		(pCur->right)->parent = parentCur;
	}
	else
		parentCur->left = NULL;


	if(pCur->left !=NULL){
		root->right = pCur->left;
		(pCur->left)->parent = root;
	}
	else
		root->right =NULL;
	
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

	if(pCur->left!=NULL){
		parentCur->right = pCur->left;
		(pCur->left)->parent = parentCur;
	}
	else
		parentCur->right = NULL;
	
	if(pCur->right!=NULL){
		root->left = pCur->right;
	
		(pCur->right)->parent = root;
	}
	else 
		root->left = NULL;

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

	if(root->right!=NULL){
		parentCur->left = root->right;
	
		(root->right)->parent = parentCur;
	}
	else
		parentCur->left=NULL;
	
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

	if(root->left!=NULL){
		parentCur->right = root->left;
	
		(root->left)->parent = parentCur;
	}
	else
		parentCur->right = NULL;

	root->left = parentCur;

	pCur->color = "black";
	root->color ="red";
	parentCur->color = "black";

	root->parent = parentCur->parent;

	parentCur->parent = root;
	
	return root;
}

Node* Node::successorNode(Node* root){
	Node *pCur;
	if(root->left == NULL)
		return root;
	else
		pCur = root->successorNode(root->left);

	return pCur;
}

Node* Node::deleteNode(Node &root,int value){
	Node *pCur ;//z
	
	pCur = (root.searchNode(&root,value));

	if(pCur==NULL)
		return &root;
	
	Node *pReplace;//y
	if(pCur->left ==NULL|| pCur->right ==NULL){
		pReplace = pCur;
	}
	else{
		Node *pN = root.searchNode(&root,value);

		pReplace= root.successorNode(pN->right);
	}
	
	Node *pReplaceNext=NULL;//x
	
	if(pReplace->left!=NULL || pReplace->right!=NULL){
	
		if(pReplace->left!=NULL)
			pReplaceNext = pReplace->left;
		else
			pReplaceNext = pReplace->right;
	
		pReplaceNext->parent = pReplace->parent;
	}
	
	if(pReplace->parent==NULL)
		root = *pReplaceNext;
	else if(pReplace == (pReplace->parent)->left){
		
		if(pReplaceNext!=NULL){
			(pReplace->parent)->left = pReplaceNext;
			pReplaceNext->parent = pReplace->parent;
		}
		else
			(pReplace->parent)->left =NULL;
	}
	else{	
		
		if(pReplaceNext!=NULL){
			(pReplace->parent)->right = pReplaceNext;
			pReplaceNext->parent = pReplace->parent;
		}
		else
			(pReplace->parent)->right =NULL;
	}
	//delete(pReplace);
	bool position = true;//left-true right-false;

	if(pReplace!=pCur){
		if(pReplace->data > pCur->data)
			position = false;
		pCur->data = pReplace->data;
	}
	
	if(pReplace->color == "black"){
		if(pReplaceNext == NULL){

			Node *pRoot = (root.deleteArrange(&root,pReplace,position));
			
			return pRoot;
		}
		else{
			
			Node *pRoot = (root.deleteArrange(&root,pReplaceNext,position));
			
			return pRoot;
			
		}
	
		delete(pReplace);
	}
	
	return &root;
}

bool dobuleBlack(Node &root){
	if(root.left==NULL && root.right==NULL)
		return true;
	else if(root.left!=NULL && root.right!=NULL){
		if((root.left)->color =="black" &&(root.right)->color =="black")
			return true;
		else
			return false;
	}
	else
		return false;
}

bool dobuleRed(Node &root){
	if(root.left!=NULL && root.right!=NULL){
		if((root.left)->color =="red" &&(root.right)->color =="red")
			return true;
		else
			return false;
	}
	else
		return false;
}

Node* Node::deleteArrange(Node *root,Node *pReplace,bool position){
	
	Node* pSplice;//w,x-NULL ddb node

	
	while(pReplace->parent!=NULL && pReplace->color == "black"){
		
		if((pReplace->parent)->data > pReplace->data ||
			((pReplace->parent)->data == pReplace->data&& position) 
			){

			pSplice = (pReplace->parent)->right;

			if(pSplice == NULL){
				(pReplace->parent)->color = "black";
				return root;
			}
			
			if(pSplice->color=="red"){

				pSplice->color = "black";
				(pReplace->parent)->color ="red";
	
				Node *pParent = (pSplice->parent);
				pParent = root->rolateDelLeft(root,(pSplice->parent)->data);

				pSplice = (pReplace->parent)->right;
				pSplice->parent = pReplace->parent;
			}

			if(dobuleBlack(*pSplice) && pSplice->color=="black"){

				pSplice->color = "red";
				
				pReplace = pReplace->parent;
		
			}
			else{
				if(pSplice->color=="black" && (pSplice->right)==NULL){

					(pSplice->left)->color = "black";
					pSplice->color = "red";
					
					(pReplace->parent)->right = (pReplace->parent)->rolateDelRight(pSplice, pSplice->data);
	
					pSplice = (pReplace->parent)->right;
				}
				else if( pSplice->color=="black" && (pSplice->right)->color == "black"){

					(pSplice->left)->color = "black";
					pSplice->color = "red";
					
					(pReplace->parent)->right = (pReplace->parent)->rolateDelRight(pSplice, pSplice->data);
	
					pSplice = (pReplace->parent)->right;
				}
			
				pSplice->color = pReplace->parent->color;
				pReplace->parent->color = "black";
				pSplice->right->color = "black";
				
				if((pReplace->parent)->parent!=NULL){
					if( (pReplace->parent)->parent->data > (pReplace->parent)->data){
						(pReplace->parent) = rolateDelLeft(pReplace->parent,pReplace->parent->data);
						(pReplace->parent)->parent->left = (pReplace->parent);
	
					}
					else{
						(pReplace->parent) = rolateDelLeft(pReplace->parent,pReplace->parent->data);
						(pReplace->parent)->parent->right = (pReplace->parent);
					}
				}
				else{
					
					root = rolateDelLeft(pReplace->parent,pReplace->parent->data);
				}

				break;
          	}
		}
		else if((pReplace->parent)->data < pReplace->data 
			||((pReplace->parent)->data == pReplace->data&& !position)
			){
			
			pSplice = (pReplace->parent)->left;

			if(pSplice == NULL){
				(pReplace->parent)->color = "black";
				return root;
			}
			
			if(pSplice->color=="red"){
				pSplice->color = "black";
				(pReplace->parent)->color ="red";

				Node *pParent = (pSplice->parent);
				pParent = root->rolateDelRight(root,(pSplice->parent)->data);
				
				pSplice = (pReplace->parent)->left;
				pSplice->parent = pReplace->parent;
			}

			if(dobuleBlack(*pSplice) && pSplice->color=="black" ){

				pSplice->color = "red";
				
				pReplace = pReplace->parent;
			}
			else {
				if(pSplice->color=="black" && (pSplice->left)==NULL){

					(pSplice->right)->color = "black";
					pSplice->color = "red";
				
					(pReplace->parent)->left = (pReplace->parent)->rolateDelLeft(pSplice, pSplice->data);

					pSplice = (pReplace->parent)->left;
				}
				else if( pSplice->color=="black" && (pSplice->left)->color == "black"){

					(pSplice->right)->color = "black";
					pSplice->color = "red";
				
					(pReplace->parent)->left = (pReplace->parent)->rolateDelLeft(pSplice, pSplice->data);

					pSplice = (pReplace->parent)->left;
				}

				pSplice->color = pReplace->parent->color;
				pReplace->parent->color = "black";
				pSplice->left->color = "black";

				if((pReplace->parent)->parent !=NULL){
					if( (pReplace->parent)->parent->data > (pReplace->parent)->data){
						(pReplace->parent) = rolateDelRight(pReplace->parent,pReplace->parent->data);
						(pReplace->parent)->parent->left = (pReplace->parent);
	
					}
					else{
						(pReplace->parent) = rolateDelRight(pReplace->parent,pReplace->parent->data);
						(pReplace->parent)->parent->right = (pReplace->parent);
					}
				}
				else{
					
					root = rolateDelRight(pReplace->parent,pReplace->parent->data);
					
				}
				
				break;
			}
		}

	}
	
	pReplace->color = "black";
	
	while(pReplace->parent!=NULL)
		pReplace = pReplace->parent;

	root = pReplace;

	return root;
}

Node* Node::rolateDelLeft(Node *root,int value){

	Node *pCur= root->searchNode(root,value);
	
	Node *pR = pCur->right;
	pR->parent = pCur->parent;
	
	if(pR->left!=NULL){
		pCur->right = pR->left;
		(pR->left)->parent = pCur;
	}
	else
		pCur->right = NULL;
	
	
	pR->left = pCur;
	pCur->parent = pR;

	return pR;
}

Node* Node::rolateDelRight(Node *root,int value){

	Node *pCur= root->searchNode(root,value);
	
	Node *pR = pCur->left;
	pR->parent = pCur->parent;
	
	if(pR->right!=NULL){
		pCur->left = pR->right;
		(pR->right)->parent = pCur;
	}
	else
		pCur->left = NULL;
	
	Node *pl = pCur;
	pR->right = pl;
	pCur->parent = pR;

	return pR;
}

#endif
