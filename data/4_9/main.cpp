/*this is demo for B tree M is 3 which means node vector size is 3 need to boom*/

#include <vector>
#include <iostream>

using namespace std;

#define FST 0
#define SEC 1
#define THR 2

class treePlus{

private:

	public:

	vector<int> data;

	treePlus *leftNode;
	treePlus *rightNode;
	treePlus *upNode;//father node mean

	treePlus(){
		leftNode = NULL;
		rightNode = NULL;
		upNode = NULL;
	}
	~treePlus(){
		if(leftNode!=NULL)
			delete leftNode;
		if(rightNode!=NULL)
			delete rightNode;
		if(upNode!=NULL)
			delete upNode;
		if(!data.empty())
			data.clear();
	}

	bool sizeData(){
		if(data.size()<3)
			return true;
		else
			return false;
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

	void showData(){
		for(int i=0;i<data.size();i++){
			cout<<data.at(i)<<"\t";
		}
		cout<<"\n";
	}

	treePlus* transferTree(){
		treePlus* root;
		
		if(upNode == NULL){
			upNode = new treePlus();
			(upNode->data).push_back(data.at(SEC));

			upNode->rightNode = new treePlus();

			((upNode->rightNode)->data).push_back(data.at(THR));

			data.pop_back();
			data.pop_back();
		
			root = upNode;
			root->leftNode = this;

			this->upNode = root;
			(upNode->rightNode)->upNode = root;

			return root;
		}
		else{
			treePlus* upLeaf;
			
			if((upNode->data).at(FST)> data.at(THR) ){//left leaf
				
				upLeaf = new treePlus();
				(upLeaf->data).push_back(data.at(SEC));

				upLeaf->rightNode = new treePlus();

				((upLeaf->rightNode)->data).push_back(data.at(THR));

				data.pop_back();
				data.pop_back();
				
				root = upNode;
				
				upLeaf->leftNode = this;
				this->upNode = upLeaf;

				root->leftNode = upLeaf;
				upLeaf->upNode = root;

				(upLeaf->rightNode)->upNode = upLeaf;

			}
			else if((upNode->data).at((upNode->data).size()-1)< data.at(FST)){//right leaf
				
				upLeaf = new treePlus();
				
				(upLeaf->data).push_back(data.at(SEC));

				upLeaf->rightNode = new treePlus();

				((upLeaf->rightNode)->data).push_back(data.at(THR));

				data.pop_back();
				data.pop_back();
				
				root = upNode;
				upLeaf->leftNode = this;

				upNode->rightNode = upLeaf;
				upLeaf->upNode = upNode;

				(upLeaf->leftNode)->upNode = upNode;

			}
			return upLeaf;
		}
		
	}


	treePlus* insertNode(int value,treePlus* root){

		if(root->leftNode==NULL && root->rightNode==NULL){
			root->getData(value);
			
			if(!root->sizeData())
				root = root->transferTree();
		}
		else{
			
			if(value<data.at(FST)){
				
				root->leftNode = root->leftNode->insertNode(value,root->leftNode);

			}
			else if(value>data.at(data.size()-1)
					&& data.size()==2){
				
				root->rightNode = root->rightNode->insertNode(value,root->rightNode);	
			}
			else if(value>data.at(FST)
					&& data.size()==1){

				if(value < (root->rightNode)->data.at(FST)){
					root->getData(value);
			
					if(!root->sizeData())
						root = root->transferTree();
				}
				else{
					root->rightNode = root->rightNode->insertNode(value,root->rightNode);
				}
			}
			
		}
		
		return root;
	}

	void inOrder(treePlus *node);

	void preOrder(treePlus *node);

};

void treePlus::preOrder(treePlus *node){
	if(node){
		//if((node->data).size()==1
		//	&& (node->leftNode!=NULL || node->rightNode!=NULL))
			node->showData();

		preOrder(node->leftNode);
		
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

int main(){
	int data[10]={53,139,75,49,145,36,50,47,101,20};
	//{53,139,75,49,36,50,47,101,149};

	int i=0;

	treePlus* root = new treePlus();
	
	while(i<10){
		
		root = root->insertNode(data[i],root);
		
		i++;
	}

	root = root->insertNode(37,root);
	root = root->insertNode(107,root);
	root = root->insertNode(142,root);
	root = root->insertNode(110,root);
	root = root->insertNode(112,root);
	root = root->insertNode(115,root);
	root->preOrder(root);

	return 1;
}


