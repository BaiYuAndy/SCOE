/*create 函数构建的是完全二叉树，中序遍历等同于堆排序*/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class bTree{
	
	public:
		int value;
		
		bTree *leftNode;
		bTree *rightNode;
	
	/*void insert(bTree *b,bTree *s);
	
	void create(bTree *b);
	*/
	void preOrder(bTree *b);
	void inOrder(bTree *b);
	void postOrder(bTree *b);
	void showPreMinOrder(bTree * root,int len,bool preMin);/*前序和中序相同，只是不同位置输出*/
	void showPostOrder(bTree * root,int len);

	int treeDepth(bTree *b);
};

void bTree::preOrder(bTree *t){
	if(t){
		cout<<t->value<<"\t";
		//printf("%d\t",t->value);

		preOrder(t->leftNode);
		preOrder(t->rightNode);
	}
}

void bTree::inOrder(bTree *node){
	if(node){
		inOrder(node->leftNode);
		cout<<node->value<<"\t";
		//printf("%d\t",node->value);
		inOrder(node->rightNode);
	}
}

void bTree::postOrder(bTree *node){
	if(node){
		postOrder(node->leftNode);
		postOrder(node->rightNode);
		cout<<node->value<<"\t";
	}
}

bTree *insert(bTree *node,int value){
	if (node == NULL) {
		node = new bTree;

		node->value = value;
		node->leftNode = NULL;
		node->rightNode =NULL;

    }
    if (node->value == value)
        node->value = value;
    else if (node->value > value)
        node->leftNode = insert(node->leftNode, value);
    else if(node->value < value)  
        node->rightNode = insert(node->rightNode, value);

    return node;

}

bTree* create(bTree *b,int* input){
	int x;
	
	b = NULL;
	int i=0;
	do{

		if(*(input+i)>0)
			b = insert(b,*(input+i));
		i++;

	}while(*(input+i)>0);

	return b;

}

bTree* buildLeverMidOrder(vector<int>& preOrder,vector<int>& minOrder){
	if(preOrder.size() == 0 || minOrder.size()==0 || preOrder.size() !=minOrder.size())
		return NULL;

	int rootKey = preOrder.front();

	bTree* root = new bTree;

	root->value= rootKey;

	if(preOrder.size() == 1){
		if(preOrder.front() == minOrder.front()){
			return root;
		}
		else
			return NULL;
	}

	int index = 0;
	while(index <preOrder.size()-1&& minOrder.at(index)!=rootKey)
		index++;

	vector<int> lLeverOrder,rLeverOrder;

	for(int i=1;i<preOrder.size();i++){
		bool isLeft =false;
		for(int j=0;j<index;j++){
			if(preOrder.at(i) == minOrder.at(j)){
				isLeft =true;
				break;
			}
		}
		if(isLeft)
			lLeverOrder.push_back(preOrder.at(i));
		else
			rLeverOrder.push_back(preOrder.at(i));
	}

	vector<int> lMidOrder,rMidOrder;
	for(int i=0;i<minOrder.size();i++){
		if(i<index)
			lMidOrder.push_back(minOrder.at(i));
		else if(i>index)
			rMidOrder.push_back(minOrder.at(i));
	}

	if(lLeverOrder.size()>0)
		root->leftNode=buildLeverMidOrder(lLeverOrder,lMidOrder);

	if(rLeverOrder.size()>0)
		root->rightNode=buildLeverMidOrder(rLeverOrder,rMidOrder);

	return root;
}

bTree* buildByPreMidOrder(int *preOrder, int *minOrder,int len){
	if(preOrder==NULL||minOrder==NULL||len==0)
		return NULL;
	int rootKey = *preOrder;

	bTree* root = new bTree;
	root->value =rootKey;

	if(len==1){
		if(*preOrder==*minOrder)
			return root;
		else 
			return NULL;
	}

	int* rootMidOrder = minOrder;
	int leftLen=0;
	while(*rootMidOrder!=rootKey &&leftLen<len){
		++rootMidOrder;
		++leftLen;
	}

	if(*rootMidOrder!= rootKey)
		return NULL;

	if(leftLen>0)
		root->leftNode=buildByPreMidOrder(preOrder+1,minOrder,leftLen);

	if(len-leftLen-1>0)
		root->rightNode=buildByPreMidOrder(preOrder+leftLen+1,rootMidOrder+1,len-leftLen-1);

	return root;
}

void bTree::showPreMinOrder(bTree * root,int len,bool preMin){
	stack<bTree *> buffer;

	buffer.push(root);
	bTree *node;
	node =root;
	int i = 0;
	while(i<len && (node!=NULL || !buffer.empty()) ){
		while(node!=NULL){
			if(preMin)
				cout<<node->value<<"\t";
			buffer.push(node);
			node = node->leftNode;
		}
		if(!buffer.empty()){
			node =buffer.top();
			if(!preMin)
				cout<<node->value<<"\t";
			buffer.pop();
			node = node->rightNode;
		}
		i++;
	}
	
}

typedef struct postNode{
	bTree *ptr;
	int flag;
}element;

void bTree::showPostOrder(bTree * root,int len){
	stack<element> buffer;

	//buffer.push(root);
	bTree *node;
	node =root;

	element elem;

	while((node!=NULL || !buffer.empty()) ){
		if(node!=NULL){
			elem.ptr = node;
			elem.flag =1;
			buffer.push(elem);
			node = node->leftNode;
		}
		else{
			elem = buffer.top();
			buffer.pop();
			node = elem.ptr;
			if(elem.flag ==1){
				elem.flag=2;
				buffer.push(elem);
				node = node->rightNode;
			}
			else{
				cout<<node->value<<"\t";
				node =NULL;
			}
		}
		
	}
	
}

void showLeverNode(bTree *root){
	if(root!=NULL){
		queue<bTree *> buffer;
		bTree *node;
		node = root;
		buffer.push(node);
		
		while(!buffer.empty() ){
		
			if(node->leftNode!=NULL){
				buffer.push(node->leftNode);
			}

			if(node->rightNode!=NULL){
				buffer.push(node->rightNode);
			}

			cout<<(buffer.front())->value<<"\t";
			buffer.pop();
			node =buffer.front();
		}
	}
}

int bTree::treeDepth(bTree *b){
	int depthLeft = 0, depthRight = 0;

	if(b==NULL)
		return 0;
	else{
		depthLeft = treeDepth(b->leftNode);
		depthRight= treeDepth(b->rightNode);

		if(depthLeft > depthRight)
			return depthLeft+1;
		else
			return depthRight+1;
	}
}

int getDepth(bTree *b){
	queue<bTree *> buffer;

	bTree *node =b;

	int front=0,rear=0,depth=0,levelLoc;

	if(b!=NULL){
		buffer.push(node);
		++rear;
	}
	levelLoc = rear;

	while(front<rear){

		node=buffer.front();
		buffer.pop();
		++front;

		if(node->leftNode!=NULL){
			buffer.push(node->leftNode);
			++rear;
		}
		if(node->rightNode!=NULL){
			buffer.push(node->rightNode);
			++rear;
		}

		if(front ==levelLoc){
			depth++;
			levelLoc =rear;
		}
	}
	return depth;
}

int main(){

	int nodeValueInput[9]={7,4,2,5,8,6,3,1,0};

	bTree *pRoot;
	
	pRoot = new bTree;

	int pre[8]={1,2,4,7,3,5,6,8};
	int min[8]={4,7,2,1,5,3,8,6};
	int lev[8]={1,2,3,4,5,6,7,8};

	//pRoot = create(pRoot,nodeValueInput);

	vector<int> perList;
	perList.assign(pre,pre+8);
	vector<int> inList;
	inList.assign(min,min+8);

	vector<int> leverList;
	leverList.assign(lev,lev+8);

	pRoot = buildByPreMidOrder(pre,min,8);
	
	//pRoot = buildLeverMidOrder(leverList,inList);

	//cout<<"depth is : "<<pRoot->treeDepth(pRoot);
	cout<<"depth is : "<<getDepth(pRoot);
	/*cout<<"\nleverOrder list: \t";
	showLeverNode(pRoot);

	cout<<"\npreorder list: \t";
	pRoot->preOrder(pRoot);
	cout<<"\nother: \t\t";
	pRoot->showPreMinOrder(pRoot,8,true);

	cout<<"\nin order list: \t";
	pRoot->inOrder(pRoot);
	cout<<"\nother: \t\t";
	pRoot->showPreMinOrder(pRoot,8,false);

	cout<<"\npost order list: ";
	pRoot->postOrder(pRoot);
	cout<<"\nother: \t\t";
	pRoot->showPostOrder(pRoot,8);
	*/
	
	return 0;
	
}

