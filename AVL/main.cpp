#include <iostream>

using namespace std;

typedef struct node{
	int value;
	struct node *leftNode;
	struct node *rightNode;
}Leaf;

class Tree{
	public:

		int value;
		Tree *leftNode;
		Tree *rightNode;
		Tree *parentNode;

		Tree* insertNode(Tree* root, int data);

	Tree(){
		parentNode =NULL;
		leftNode = NULL;
		rightNode  = NULL;
	}

	void preOrder(Tree* root);
	void middleOrder(Tree* root);

	int high(Tree *root);
	int skew(Tree *root);

	Tree* rotationTree(Tree* root);
	Tree* rotationTreeLeft(Tree* root);
	Tree* rotationTreeOther(Tree* root);
	Tree* rotationTreeOtherLeft(Tree* root);
};

int Tree::high(Tree *root){
	int hLeft,hRight;
	if(root){
		hLeft = high(root->leftNode);
		hRight = high(root->rightNode);

		return hLeft>hRight?hLeft+1:hRight+1;
	}
	else
		return 0;
}

int Tree::skew(Tree *root){
	int minus = 0;
	int hLeft = 0;
	int hRight = 0;

	if(root->rightNode!=NULL)
		hRight = high(root->rightNode);
	if(root->leftNode!=NULL)
		hLeft = high(root->leftNode);
	
	minus = hRight - hLeft;
	//minus = high(root->rightNode) - high(root->leftNode);

	return minus;
}

void Tree::preOrder(Tree* root){
	if(root!=NULL){
		cout<<root->value<<' ';

		preOrder(root->leftNode);
		preOrder(root->rightNode);
	}
}

void Tree::middleOrder(Tree* root){
	if(root!=NULL){

		middleOrder(root->leftNode);
		cout<<root->value<<' ';
		middleOrder(root->rightNode);
	}
}

Tree* Tree::insertNode(Tree* root,int data){
	if(root ==NULL){
		root = new Tree();
		root->value =data;
	}
	if(data < root->value ){
		root->leftNode =  root->insertNode(root->leftNode,data);
		(root->leftNode)->parentNode = root;
	}
	else if(data > root->value ){
		root->rightNode = root->insertNode(root->rightNode,data);
		(root->rightNode)->parentNode = root;
	}

	return root;
}

Tree* Tree::rotationTree(Tree* root){

	Tree* up = new Tree();
	Tree* middle = new Tree();
	Tree* bottom = new Tree();

	up = root;
	middle = root->rightNode;
	bottom = (root->rightNode)->leftNode;

	//cout<<up->value<<' '<<middle->value<<' '<<bottom->value<<endl;

	if(bottom->rightNode!=NULL){
		
		(middle->leftNode) = bottom->rightNode;
		(bottom->rightNode)->parentNode = middle->leftNode;
	}
	else
		middle->leftNode = NULL;

	if(bottom->leftNode!=NULL){
		
		up->rightNode = bottom->leftNode;
		(bottom->leftNode)->parentNode = up->rightNode;
	}
	else
	 	up->rightNode = NULL;

	bottom->leftNode = up;
	up->parentNode = bottom;

	bottom->rightNode = middle;
	middle->parentNode = bottom;

	//cout<<(bottom->parentNode)->value<<"\n";// = NULL;

	
	return bottom;
}

Tree* Tree::rotationTreeOther(Tree* root){
	
	Tree* up = new Tree();
	Tree* bottom = new Tree();

	up = root;
	bottom = root->rightNode;

	if(bottom->leftNode!=NULL){
		
		up->rightNode = bottom->leftNode;
		(bottom->leftNode)->parentNode = up->rightNode;
	}
	else
	 	up->rightNode = NULL;

	bottom->leftNode = up;
	up->parentNode = bottom;

	
	return bottom;
}

Tree* Tree::rotationTreeLeft(Tree* root){//for sitution -2 1

	Tree* up = new Tree();
	Tree* middle = new Tree();
	Tree* bottom = new Tree();

	up = root;
	middle = root->leftNode;
	bottom = (root->leftNode)->rightNode;

	//cout<<up->value<<' '<<middle->value<<' '<<bottom->value<<endl;

	if(bottom->leftNode!=NULL){
		
		(middle->rightNode) = bottom->leftNode;
		(bottom->leftNode)->parentNode = middle->rightNode;
	}
	else
		middle->rightNode = NULL;

	if(bottom->rightNode!=NULL){
		
		up->leftNode = bottom->rightNode;
		(bottom->rightNode)->parentNode = up->leftNode;
	}
	else
	 	up->leftNode = NULL;

	bottom->rightNode = up;
	up->parentNode = bottom;

	bottom->leftNode = middle;
	middle->parentNode = bottom;

	
	return bottom;
}

Tree* Tree::rotationTreeOtherLeft(Tree* root){// for sitution -2 -1
	
	Tree* up = new Tree();
	Tree* bottom = new Tree();

	up = root;
	bottom = root->leftNode;

	if(bottom->rightNode!=NULL){
		
		up->leftNode = bottom->rightNode;
		(bottom->rightNode)->parentNode = up->leftNode;
	}
	else
	 	up->rightNode = NULL;

	bottom->rightNode = up;
	up->parentNode = bottom;

	
	return bottom;
}

Tree* getSkew(Tree *root,Tree* skewNode){
	Tree *node;
	node= root;
	int minus = node->skew(node);
	
	if(minus<2){
		return node;
	}
	else{

	while(minus>2){
		node = node->rightNode;
		minus = node->skew(node);
	}
	
	minus = node->skew(node->rightNode);
	
	if(minus ==1 ||minus ==0 || minus ==-1){
		skewNode = node;
	}
	else{
		skewNode = getSkew(node->rightNode,skewNode);
	}

	return skewNode;
	
	}
}

Tree* skewMore(Tree* root,bool& leftOrRight){

	Tree *node;
	node= root;
	int minus = node->skew(node);
	//cout<<minus<<endl;
	if(minus>2){

		while(minus>2){
			node = node->rightNode;
	
			minus = node->skew(node);
		}
	}
	else if(minus< -2){

		while(minus< -2){
			node = node->leftNode;
	
			minus = node->skew(node);
		}
	}
	if(minus == 2){
		leftOrRight = false;
		return node;
	}
	else if(minus == -2){
		leftOrRight = true;
		return node;
	}
	else
		return NULL;
	
}

int skewCount(Tree* root){
	Tree *node;
	node= root;
	int minus = 0;
	
	if(node !=NULL)
		minus = node->skew(node);
	
	
	return minus;
	
}

int main(){

	cout<<"AVL tree : \n";

	int data[8] = {8,5,6,7,4,9,2,3};//{2,5,3,6,7,9,8,4};

	Tree* root = new Tree();
	root->value = data[0];

	bool direct = true;

	for(int i=1;i<8;i++){
		root = root->insertNode(root,data[i]);

		if((skewMore(root,direct))!=NULL){
			Tree *node = skewMore(root,direct);
			
			bool loop = true;
			while(loop){
				
				if(skewCount(node->rightNode) == -1 && !direct){
					if(node->parentNode == NULL){
						node = node->rotationTree(node);
						
						node->parentNode = NULL;
						root = node;
					}
					else{
						Tree* parentLast = (node->parentNode);
						node = node->rotationTree(node);
						parentLast->rightNode = node;
						(node->parentNode) = parentLast;
					}
					loop = false;
				}
				else if( (skewCount(node->rightNode) == 1
					||skewCount(node->rightNode) == 0) && !direct){
					
					if(node->parentNode == NULL){
						node = node->rotationTreeOther(node);
						node->parentNode = NULL;
						root = node;
					}
					else{
						Tree* parentLast = (node->parentNode);
						
						node = node->rotationTreeOther(node);
						parentLast->rightNode = node;
						(node->parentNode) = parentLast;
					}
					loop = false;
				}
				else if(skewCount(node->leftNode) == -1 && direct){
					if(node->parentNode == NULL){
						node = node->rotationTreeOtherLeft(node);
						
						node->parentNode = NULL;
						root = node;
					}
					else{
						Tree* parentLast = (node->parentNode);
						node = node->rotationTreeOtherLeft(node);
						parentLast->leftNode = node;
						(node->parentNode) = parentLast;
					}
					loop = false;
				}
				else if( (skewCount(node->leftNode) == 1
					||skewCount(node->leftNode) == 0) && direct){
					
					if(node->parentNode == NULL){
						node = node->rotationTreeLeft(node);
						node->parentNode = NULL;
						root = node;
					}
					else{
						Tree* parentLast = (node->parentNode);
						
						node = node->rotationTreeLeft(node);
						parentLast->leftNode = node;
						(node->parentNode) = parentLast;
					}
					loop = false;
				}
				else{ 
					
					if(!direct)
						node = node->rightNode;
					else
						node = node->leftNode;

				}
			}

		}

	}

	cout<<"\n";
	root->preOrder(root);
	cout<<"\n";
	root->middleOrder(root);
	//
	return 1;

}

