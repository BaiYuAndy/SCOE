// red and black tree
#include <iostream>
#include <string.h>
#include <queue>

using namespace std;

template<typename T>
class RedBlackTree{
private:

public:

	typedef struct node
	{
		const char *lable;
		T data;
		struct node *leftNode;
		struct node *rightNode;
		struct node *parentNode;

		node(const char* ch,T value){
			lable = new char();
			lable = ch;
			data = value;

			leftNode=NULL;
			rightNode=NULL;
			parentNode=NULL;
		};

	}Node;

	Node* root;
	Node* last;

	RedBlackTree(){

		root =NULL;
		last =NULL;
	}
	~RedBlackTree(){
		if(root!=NULL)
			delete root;
	}
	
	bool InsertTree(const char *ch,T data);
	void RollLeftRight(Node *cur);
	void RollLeftLeft(Node *cur);

	void RollRightLeft(Node *cur);
	void RollRightRight(Node *cur);

	void preOrder(Node *t);
	void middleOrder(Node *t);

	void adjustTree(Node *cur);
	void showLeverNode();
	int getNodeInfor(Node *cur);

	void changeColor(Node & cur);
	void changeColor(Node *cur);

};

template<typename T>
void RedBlackTree<T>::preOrder(Node *t){
	
	if(t){
		//cout<<t->lable<<"--"<<t->data<<"\t";
		cout<<t->data<<"\t";
		preOrder(t->leftNode);
		preOrder(t->rightNode);
	}
}

template<typename T>
void RedBlackTree<T>::middleOrder(Node *t){
	
	if(t){
		middleOrder(t->leftNode);
		//cout<<t->lable<<"--"<<t->data<<"\t";
		cout<<t->data<<"\t";
		middleOrder(t->rightNode);
	}
}

template<typename T>
bool RedBlackTree<T>::InsertTree(const char* ch,T data){
	if(root ==NULL){
		root = new Node("black",data);

		last = root;
		return true;
	}
	
	Node *parent;
	Node *cur;
	cur=root;
	while(cur){
		if(cur->data< data){
			parent=cur;
			cur=cur->rightNode;
		}
		else if(cur->data>data){
			parent=cur;
			cur=cur->leftNode;
		}
		else
			return false;
	}
	cur = new Node(ch,data);

	if(parent->data <data){
		parent->rightNode=cur;
	}
	else{
		parent->leftNode=cur;
	}
	cur->parentNode =parent;

	last = cur;
	return true;
	
}

template<typename T>
void RedBlackTree<T>::RollRightRight(Node *cur){
	Node *par;
	par = cur->parentNode;

	Node *grand;
	grand = par->parentNode;
	if(grand!=NULL){
		bool leftOr = false;

		if(grand->leftNode!=NULL){
			T tempLeftData = (grand->leftNode)->data;		
		
			if( tempLeftData == par->data)
				leftOr = true;
		}
	
		cur->parentNode = grand;
		
		if(!leftOr)
			grand->rightNode = cur;
		else
			grand->leftNode = cur;

		cur->parentNode =grand;
	}

	par->rightNode=cur->leftNode;

	cur->leftNode = par;
	
	par->parentNode = cur;
	
}

template<typename T>
void RedBlackTree<T>::RollLeftLeft(Node *cur){
	Node *par;
	par = cur->parentNode;

	if(par->parentNode!=NULL){
		Node *head;
	
		head = cur->parentNode = par->parentNode;
		
		bool leftOr = false;
		if(head->leftNode!=NULL){
			T tempLeftData = (head->leftNode)->data;
		
			if( tempLeftData == par->data)
				leftOr = true;
		}
		
		if(!leftOr)
			head->rightNode = cur;
		else{
			head->leftNode = cur;
			par->leftNode = cur->rightNode;
		}
			cur->parentNode = head;
	}
	else{
		cur->parentNode=NULL;
		root = cur;
	}

	par->leftNode =cur->rightNode;

	cur->rightNode = par;
	par->parentNode = cur;
	//(cur->rightNode)->leftNode = NULL;
	
}

template<typename T>
void RedBlackTree<T>::RollLeftRight(Node *cur){
	Node* parent = cur->parentNode;
	Node* grand = parent->parentNode;

	Node *child;
	child = cur->leftNode;

	cur->leftNode = NULL;

	if(grand!=NULL){	
		bool leftOr = false;
		if(grand->leftNode!=NULL){
			T tempLeftData = (grand->leftNode)->data;
	
			if( tempLeftData == parent->data)
				leftOr = true;
		}

		if(leftOr)
			grand->leftNode = child;
		else
			grand->rightNode = child;

		child->parentNode = grand;
	}
	else{
		child->parentNode=NULL;
		root = child;
	}
	parent->rightNode=child->leftNode;

	child->leftNode = parent;
	parent->parentNode = child->leftNode;
	//parent->rightNode = NULL;

	cur->leftNode = child->rightNode;

	(child->rightNode) = cur;
	cur->parentNode = child->rightNode;
}

template<typename T>
void RedBlackTree<T>::RollRightLeft(Node *cur){//cur arg means parent ,parent is left ,new node is right
	
	Node *par;
	par = cur->parentNode;
	Node *head;
	if(par->parentNode!=NULL){
		head = cur->parentNode = par->parentNode;
	
		bool leftOr=false;
		if(head->leftNode !=NULL){
			if( par->data == (head->leftNode)->data )
				leftOr=true;
		}
		else if(head->rightNode !=NULL){
			if( par->data == (head->rightNode)->data )
				leftOr=false;
	
		}
		if(leftOr){
			head->leftNode = cur->rightNode;
	
		}
		else{
			head->rightNode = cur->rightNode;
		}
		
		(cur->rightNode)->parentNode = head;
		
	}
	else{
		(cur->rightNode)->parentNode = NULL;
		root=cur->rightNode;
	}

	Node *child;
	child = cur->rightNode;

	par->leftNode = child->rightNode;
	
	child->rightNode=par;
	par->parentNode = child;
	//par->leftNode=NULL;

	cur->rightNode = child->leftNode;

	child->leftNode=cur;
	cur->parentNode = child;
	//cur->rightNode = NULL;

}

template<typename T>
void RedBlackTree<T>::changeColor(Node &cur){
	
	if(strcmp(cur.lable,"red")==0)
		cur.lable="black";
	else if(strcmp(cur.lable,"black")==0)
		cur.lable="red";
}

template<typename T>
void RedBlackTree<T>::changeColor(Node *cur){
	
	if(strcmp(cur->lable,"red")==0)
		cur->lable="black";
	else if(strcmp(cur->lable,"black")==0)
		cur->lable="red";
}

template<typename T>
void RedBlackTree<T>::adjustTree(Node *cur){
	if(cur == root)
		root->lable="black";

	else{
		Node *parent;
		parent = cur->parentNode;

		bool leftOr=false;
		if(parent->leftNode !=NULL){
			if( cur->data == (parent->leftNode)->data )
				leftOr=true;//current node is left node
		}
		
		if(parent->rightNode !=NULL){
			if( cur->data == (parent->rightNode)->data )
				leftOr=false;//current node is right node
		}
		
		if(parent == root){
			root->lable = "black";
		}
		else{
			Node *grand;
			grand = parent->parentNode;
			
			bool parLeftOr = false;
			if(grand->leftNode!=NULL){
				if(parent->data == (grand->leftNode)->data )
					parLeftOr = true;
			}
			if(grand->rightNode!=NULL){
				if(parent->data == (grand->rightNode)->data )
					parLeftOr = false;
			}

			if(leftOr){
				if(parLeftOr){/*parent is left and cur is left*/
					if(grand->rightNode !=NULL){
						if( strcmp((grand->leftNode)->lable,"red") ==0
							&& strcmp((grand->rightNode)->lable,"red") ==0){
								
								this->changeColor(*grand);
								this->changeColor(*(grand->leftNode));
								this->changeColor(*(grand->rightNode));
									
								adjustTree(grand);
								
						}
						else if(strcmp((grand->leftNode)->lable,"red") ==0
								&& strcmp((grand->rightNode)->lable,"black") ==0){				
								
								changeColor(parent);
								changeColor(grand);
								RollLeftLeft(parent);
						}
					}
					else{

						if(strcmp(parent->lable,"red") ==0){
							
							changeColor(parent);
							changeColor(grand);
							RollLeftLeft(parent);
						}
						
					}
				}
				else{ /*parent is right and cur is left*/
					if(grand->leftNode !=NULL){
						if( strcmp((grand->leftNode)->lable,"red") ==0
							&& strcmp((grand->rightNode)->lable,"red") ==0){
								
									this->changeColor(*grand);
									this->changeColor(*(grand->leftNode));
									this->changeColor(*(grand->rightNode));
		
									adjustTree(grand);
						}
						else if(strcmp((grand->leftNode)->lable,"black") ==0
								&& strcmp((grand->rightNode)->lable,"red") ==0){
							
								this->changeColor(*parent);
								this->changeColor(*grand);
								this->RollLeftRight(parent);
							
						}
					}
					else{
						if(strcmp(parent->lable,"red") ==0){
								
							this->changeColor(*parent);
							this->changeColor(*grand);
							
							this->RollLeftRight(parent);
						}

					}

				}
			}
			else{
				if(parLeftOr){/*parent is left and cur is right*/
					if(grand->rightNode!=NULL){
						if( strcmp((grand->leftNode)->lable,"red") ==0
							&& strcmp((grand->rightNode)->lable,"red") ==0){
								//if(grand!=root){
									this->changeColor(*grand);
									this->changeColor(*(grand->leftNode));
									this->changeColor(*(grand->rightNode));
		
									adjustTree(grand);
								/*}
								else
									changeColor(*cur);*/
						}
						else if(strcmp((grand->leftNode)->lable,"red") ==0
							&& strcmp((grand->rightNode)->lable,"black") ==0){
								
								this->changeColor(*cur);
								/*this condition the grand is must be black
								 so it should be set to red 
								*/
								this->changeColor(*grand);
								
								this->RollRightLeft(parent);
								
						}
					}
					else{
						if(strcmp(parent->lable,"red") ==0){
							
							changeColor(cur);
							
							if(strcmp(grand->lable,"black")==0){
								changeColor(*grand);
							}
							
							RollRightLeft(parent);
						}
					}
				}
				else{/*parent is right and cur is right*/
					if(grand->leftNode !=NULL){
						if( strcmp((grand->leftNode)->lable,"red") ==0
							&& strcmp((grand->rightNode)->lable,"red") ==0){
								changeColor(grand);
								changeColor((grand->leftNode));
								changeColor((grand->rightNode));
								
								adjustTree(grand);
							
						}
						else if(strcmp((grand->rightNode)->lable,"red") ==0
								&& strcmp((grand->leftNode)->lable,"black") ==0){
							
								this->changeColor(*parent);
								this->changeColor(*grand);
								this->RollRightRight(parent);
						}
					}
					else{
						if(strcmp(parent->lable,"red")==0){
							changeColor(parent);
							changeColor(grand);
							this->RollRightRight(parent);
						}
						
					}
				}
			}
		}
	}
}

template<typename T>
int RedBlackTree<T>::getNodeInfor(Node *cur){
	int value = 0;
	if(cur!=NULL){
		if(cur==root)
			value = 0;
		else{
			Node *parent;
			parent = cur->parentNode;

			if(parent->leftNode!=NULL){
				int tempData = (parent->leftNode)->data;
			
				if (tempData == cur->data){
					if(parent->rightNode!=NULL)
						value = 1;//hit parent left node
					else{
						Node *grand;
						grand = parent->parentNode;
						if(grand!=NULL){
							tempData = (grand->rightNode)->data;
							if(tempData == parent->data)
								value = 2;//hit parent left node and uncle node is null;
							else
								value = 1;
						}
					}
				}
				else{
					if(parent->rightNode!=NULL){
						tempData = (parent->rightNode)->data;
						if (tempData == cur->data)
							value = 2;//hit parent right node
					}
				}
			}

		}
	}
	
	return value;
}

template<typename T>
void RedBlackTree<T>:: showLeverNode(){
	if(root!=NULL){
		queue<Node *> buffer;
		Node *node;
		node = root;
		buffer.push(node);
		
		while(!buffer.empty() ){
		
			if(node->leftNode!=NULL){
				buffer.push(node->leftNode);
			}

			if(node->rightNode!=NULL){
				buffer.push(node->rightNode);
			}

			cout<<(buffer.front())->data<<"--"<<(buffer.front())->lable<<"\t";
			
			int tempInfo = getNodeInfor(buffer.front());
			
			if(tempInfo==2||tempInfo==0)
				cout<<"\n";
			
			buffer.pop();
			node =buffer.front();
			
		}
	}
}

int main(){

	RedBlackTree<int> tree;

	int value[14]={10,8,9,5,4,3,6,7,2,1,11,15,14,16};
	const char *lable = "red";

	int i=0;
	while(i<14){
		tree.InsertTree(lable,value[i]);
		tree.adjustTree(tree.last);
		i++;
	}

	tree.middleOrder(tree.root);
	cout<<"\n";
	tree.preOrder(tree.root);
	cout<<"\n";
	tree.showLeverNode();

	fflush(stdout);
	fflush(stdin);
	return 1;
}


