/*this is a demo of B tree which M is 3*/
/*this is demo for B tree M is 3 which means node vector size is 3 need to boom*/
#include <vector>
#include <iostream>

using namespace std;

#define FST 0
#define SEC 1
#define THR 2

#define M 3 //M means node

class treePlus{
private:
	vector<int> data;

public:
	treePlus *leftNode;
	treePlus *middleNode;
	treePlus *upNode;
	treePlus *rightNode;

	treePlus *parentNode;

	treePlus(){
		leftNode = NULL;
		rightNode = NULL;
		middleNode = NULL;
		upNode = NULL;

		parentNode = NULL;
	}
	~treePlus(){
		if(leftNode!=NULL)
			delete leftNode;
		if(rightNode!=NULL)
			delete rightNode;
		if(parentNode!=NULL)
			delete parentNode;
		if(middleNode!=NULL)
			delete middleNode;
		if(upNode!=NULL)
			delete upNode;

		if(!data.empty())
			data.clear();
	}

	bool sizeData(){
		if(data.size()<M)
			return true;
		else
			return false;
	}

	int dataSize(){
		return data.size();
	}

	void deleteData(int seq){
		if(!data.empty())
			data.erase(data.begin()+seq);
	}

	void getData(int value){
		data.push_back(value);

		if(data.size()>1){
			for(int i=0;i<data.size();i++){
				for(int j = i+1;j<data.size();j++){
					if(data.at(i)>data.at(j)){
						int temp = data.at(i);
						data.at(i) = data.at(j);
						data.at(j) = temp;
					}
				}
			}
		}
	}

	void copyData(vector<int> list){
		for(int i=0;i<list.size();i++)
			data.push_back(list.at(i));

	}

	void showData(){
		for(int i=0;i<data.size();i++){
			cout<<data.at(i)<<"\t";
		}
		cout<<"\n";
	}

	void inOrder(treePlus *node);

	void preOrder(treePlus *node);

	int setData(int seq){
		switch(seq){
			case FST:
				return data.at(FST);
				break;
			case SEC:
				return data.at(SEC);
				break;
			case THR:
				return data.at(THR);
				break;
			default:
				return 0;
				break;
		}
	}

	int lastData(){
		int last = data.size();

		last--;
		return setData(last);
	}

	treePlus& searchNode(int value);

	treePlus* spildTree(treePlus *head,treePlus * node);
	treePlus* processTree(treePlus &head,treePlus *node);

	treePlus* findNode(treePlus *head,treePlus *node);

};

void treePlus::preOrder(treePlus *node){
	if(node){
		//if((node->data).size()==1
		//	&& (node->leftNode!=NULL || node->rightNode!=NULL))
			node->showData();

		preOrder(node->leftNode);
		preOrder(node->middleNode);
		preOrder(node->rightNode);
	}
}

void treePlus::inOrder(treePlus *node){
	if(node){
		inOrder(node->leftNode);
		
		node->showData();
		
		inOrder(node->rightNode);
	}
}
static int upStep = 0;
treePlus* rootTemp;

treePlus* treePlus::processTree(treePlus &head,treePlus *node){
	
	treePlus *left,*right,*middle,*upNode;

	left = node->leftNode;
	right = node->rightNode;
	middle = node->middleNode;
	upNode = node->upNode;

	treePlus *root;
	
	if(node->parentNode==NULL)
		root = new treePlus();
	else
		root = node->parentNode;

	if( node->parentNode ==NULL
		|| (root->setData(FST)> node->setData(THR) )){
		
		//node->showData();
		
		root->getData(node->setData(SEC));

		bool grandParent = false;
		if(!root->sizeData() 
			&& (root->setData(FST)> node->setData(FST))
			){
			root = processTree(head,root);

			//if(root->parentNode !=NULL){
				root = root->leftNode;
				grandParent = true;
			//}
			
		}
		
		root->rightNode = new treePlus();
		(root->rightNode)->getData(node->setData(THR));
		(root->rightNode)->parentNode = root;
	
		root->leftNode = new treePlus();
		(root->leftNode)->getData(node->setData(FST));
		(root->leftNode)->parentNode = root;
		
		if(left!=NULL){
			(root->leftNode)->leftNode = left;
			left->parentNode = (root->leftNode);
		}
		if(right!=NULL){
			(root->rightNode)->rightNode = right;
			right->parentNode = (root->rightNode);
		}
		if(middle!=NULL){
			(root->rightNode)->leftNode = middle;
			middle->parentNode = (root->rightNode);
		
		}
		if(upNode!=NULL){
			(root->leftNode)->rightNode = upNode;
			upNode->parentNode = (root->leftNode);
		}

		node->deleteData(THR);
		node->deleteData(SEC);
		node->deleteData(FST);
		
		if(grandParent){
			head =*(root->parentNode);
		}
		else
			head = *root;
	}
	else if(root->setData(root->dataSize()-1) < node->setData(FST)){
		
		root->getData(node->setData(SEC));

		bool grandParent = false;
		if(!root->sizeData()){
			root = processTree(head,root);
			root = root->rightNode;
			grandParent = true;
			
		}
		
		root->rightNode = new treePlus();
		(root->rightNode)->getData(node->setData(THR));
		(root->rightNode)->parentNode = root;
		
		root->middleNode = new treePlus();
		(root->middleNode)->getData(node->setData(FST));
		(root->middleNode)->parentNode = root;
		
		if(left!=NULL){
			(root->middleNode)->leftNode = left;
			left->parentNode = (root->middleNode);
		}
		if(right!=NULL){
			(root->rightNode)->rightNode = right;
			right->parentNode = (root->rightNode);
		}
		if(middle!=NULL){
			(root->rightNode)->leftNode = middle;
			middle->parentNode = (root->rightNode);
		}
		if(upNode!=NULL){
			(root->middleNode)->rightNode = upNode;
			upNode->parentNode = (root->middleNode);
		}
	
		node->deleteData(THR);
		node->deleteData(SEC);
		node->deleteData(FST);
		
		if(grandParent){
			head =*(root->parentNode);
		}
		else
			head = *root;
	}
	else if( ((root->setData(FST)< node->setData(FST))
			&&(root->setData(root->dataSize()-1) > node->setData(FST))) ){
		
		treePlus* rootTwo = new treePlus();

		rootTwo->getData(node->setData(SEC));

		rootTwo->rightNode = new treePlus();
		(rootTwo->rightNode)->getData(node->setData(THR));
		(rootTwo->rightNode)->parentNode = root;
	
		rootTwo->leftNode = new treePlus();
		(rootTwo->leftNode)->getData(node->setData(FST));
		(rootTwo->leftNode)->parentNode = root;
	
		if(left!=NULL){
			(rootTwo->leftNode)->leftNode = left;
			left->parentNode = (rootTwo->leftNode);
		}
		if(right!=NULL){
			(rootTwo->rightNode)->rightNode = right;
			right->parentNode = (rootTwo->rightNode);
		}
		if(middle!=NULL){
			(rootTwo->rightNode)->leftNode = middle;
			middle->parentNode = (rootTwo->rightNode);
		
		}
		if(upNode!=NULL){
			(rootTwo->leftNode)->rightNode = upNode;
			upNode->parentNode = (rootTwo->leftNode);
		}
		
		rootTwo->parentNode = root;
		root->middleNode = rootTwo;
		head = *root;
		
		spildTree(&head,rootTwo);
		

	}

	return root;
}

treePlus* treePlus::spildTree(treePlus *head,treePlus * node){
	
	if(node->parentNode == NULL){
		
		return processTree(*head,node);
	}
	else{
		treePlus *parent;
		parent = node->parentNode;
		treePlus &gen = *(head->findNode(head,parent));
		
		if( (node->lastData() < (parent)->setData(FST) )
			&& (!node->sizeData()) ){
		
			parent->getData(node->setData(SEC));
			
			if(parent->leftNode ==NULL){
				parent->leftNode = new treePlus();

				(parent->leftNode)->getData(node->setData(FST));
				(parent->leftNode)->parentNode = parent;
			}
			else{				
				if(node->setData(THR) > parent->setData(FST)){
					
					parent->upNode = new treePlus();

					(parent->upNode)->getData(node->setData(THR));
					(parent->upNode)->parentNode = parent;
				}
			}
			
			
			if(parent->middleNode == NULL){
			
				parent->middleNode = new treePlus();

				(parent->middleNode)->getData(node->setData(THR));
				(parent->middleNode)->parentNode = parent;
			}
			else {

				if(node->setData(THR) < (parent->middleNode)->setData(FST)){
					parent->upNode = new treePlus();

					(parent->upNode)->getData(node->setData(THR));
					(parent->upNode)->parentNode = parent;
				}
			}
			node->deleteData(THR);
			node->deleteData(SEC);
			
			gen = *parent;

			while(!(parent)->sizeData()){
				parent = processTree(*head,parent);
			}

		}
		else if(node->setData(FST) >(parent)->setData(parent->dataSize()-1)){

			parent->getData(node->setData(SEC));

			if(parent->rightNode ==NULL){
				parent->rightNode = new treePlus();

				(parent->rightNode)->getData(node->setData(THR));
				(parent->rightNode)->parentNode = parent;
			}

			if(parent->middleNode == NULL){
			
				parent->middleNode = new treePlus();

				(parent->middleNode)->getData(node->setData(FST));
				(parent->middleNode)->parentNode = parent;

			}
			else{
				
				parent->upNode = new treePlus();
				(parent->upNode)->copyData( (parent->middleNode)->data);
				(parent->upNode)->parentNode = parent;
				
				( (parent->middleNode)->data).clear();
				(parent->middleNode)->getData(node->setData(FST));
			}
		
			node->deleteData(SEC);
			node->deleteData(FST);
			gen = *parent;

			while(!parent->sizeData()){
				parent = processTree(*head,parent);
			}
		}
		else if(node->setData(FST) > (parent)->setData(FST)
				&& node->setData(FST) < (parent)->setData( (parent->dataSize()-1) )){

			if(!node->dataSize()){
				parent->getData(node->setData(SEC));
			
				if(parent->upNode == NULL){
					
					parent->upNode = new treePlus();
					(parent->upNode)->getData(node->setData(FST));
					(parent->upNode)->parentNode = parent;
					
				}
	
				int middleTemp = node->setData(THR);
				((parent->middleNode)->data).clear();
				(parent->middleNode)->getData(middleTemp);
			
				node->deleteData(SEC);
				node->deleteData(FST);
			}
			else{
				parent->getData(node->setData(FST));
				if(parent->middleNode == NULL)
					parent->middleNode = new treePlus();
		
				(parent->middleNode) = node->rightNode;
				(parent->middleNode)->parentNode = parent;		
				
				if(parent->upNode == NULL)		
					parent->upNode = new treePlus();
				
				(parent->upNode) = node->leftNode;
				(parent->upNode)->parentNode = parent;	
				node->deleteData(FST);
			}

			gen = *parent;

			while(!parent->sizeData()){
				parent = processTree(*head,parent);
			}
		}
		
		return node;
	}
}


treePlus& treePlus::searchNode(int value){
	
	if(leftNode == NULL || rightNode==NULL){
		getData(value);
		
		treePlus &node = *this;
		return node;
	}
	else if(value < setData(FST)){
			treePlus &node = (leftNode->searchNode(value));
			return node;
	}
	else if(value > setData( dataSize()-1 )){
			treePlus &node = (rightNode->searchNode(value));
			return node;
		}
	else{
			treePlus &node = (middleNode->searchNode(value));
			return node;
		
	}
	
}

treePlus* treePlus::findNode(treePlus *head,treePlus * node){
	if(node->setData(FST) == head->setData(FST)){
		
		return head;
	}
	else if(node->setData(FST) < head->setData(FST)){
			head->leftNode = findNode(head->leftNode,node);
			return head->leftNode;
	}
	else if(node->setData(FST) > head->setData( head->dataSize()-1 )){
			head->rightNode = findNode(head->rightNode,node);
			return head->rightNode;
		}
	else{
		head->middleNode = findNode(head->middleNode,node);
		return head->middleNode;
	}
	
}

int main(){

	treePlus * root = new treePlus();
	
	treePlus * hit;
	int data[18]={53,139,75,49,145,5,12,47,48,4,66,68,88,129,67,69,70,71};

	for(int i=0;i<18;i++){
		treePlus & node= ( root->searchNode(data[i]) );
		//node.showData();
		if(!node.sizeData()){
			hit = &node;
			root->spildTree(root,hit);
		}
		
	}
	
	root->preOrder(root);
	
	return 1;
}




