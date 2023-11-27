#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

#define N 2

class Btree{
public:

	vector<int> keys;
	
	vector<Btree *> leafs;

	Btree* parent;

	int keyLength();

	int degree;
	int keyDegree;
	int leafDegree;

	Btree(){
		degree = N;
		keyDegree = degree*2-1;
		leafDegree = degree*2;
		parent = NULL;

	}

	Btree* insertNode(int data,Btree* node);
	void insertNodeleaf(int data,Btree& node,Btree& root);
	void showKey();
	void arrangeKeys();
	void preOrder();

	Btree* spildKeys(Btree* node);

	Btree* travelNode(int data,bool& hit);

	Btree & operator+(int data); 
	Btree* addNode(int data,Btree* root);

	Btree * searchNode(int key,int& seq);

	Btree * searchNode(int key);

	void deleteNode(int key);
};

void Btree::preOrder(){
	showKey();
	if(!leafs.empty()){
		for(int i=0;i<leafs.size();i++){
			(leafs.at(i))->preOrder();
		}
	}
}

void Btree::showKey(){
	if(!keys.empty()){
		for(int i=0;i<keys.size();i++)
			cout<<keys.at(i)<<"\t";
	cout<<"\n";
	}
}

void Btree::arrangeKeys(){
	if(!keys.empty()){
		for(int i=0;i<keys.size();i++){
			for(int j=i+1;j<keys.size();j++){
				if(keys.at(i)>keys.at(j)){
					int temp = keys.at(j);
					keys.at(j) = keys.at(i);
					keys.at(i) = temp;
				}
			}
		}
	}
}

int Btree::keyLength(){
	if(keys.empty())
		return 0;
	else
		return keys.size();
}

Btree* Btree::insertNode(int data,Btree* node){
	if(keyLength()<keyDegree){
		keys.push_back(data);
		arrangeKeys();
		return this;
	}
	else{

		arrangeKeys();
		
		node = node->spildKeys(node);
		
		Btree *leafNode;
		bool hit = false;
		leafNode = node->travelNode(data,hit);
	
		leafNode->insertNode(data,leafNode);

		return node;
	}
}

void Btree::insertNodeleaf(int data,Btree& node,Btree& root){
	if( node.keyLength()<(node.keyDegree) ){
		(node.keys).push_back(data);
		node.arrangeKeys();
	}
	else{
		if(node.parent == NULL){
			node = *(node.spildKeys(&node));
			node.addNode(data,&node);
			
		}
		else if( (node.parent)->keyLength() < ((node.parent)->keyDegree) ){
			
			(node.parent) = (node.spildKeys(&node));
			(node.parent)->addNode(data,(node.parent));

			Btree *parent =  (node.parent);
			while(parent->parent !=NULL){
				parent = parent->parent;
			}
			root = *parent;
			
		}
		else{
			Btree* nodeParent = (node.parent);
			//if(nodeParent->parent!=NULL){
				while( nodeParent->parent!=NULL
					&&(nodeParent->parent)->keyLength() >= ((nodeParent->parent)->keyDegree)){

					nodeParent = (nodeParent->parent);
				}
			//}
			
			//(node.parent)->parent = ((node.parent)->spildKeys((node.parent)));
			(nodeParent)->parent = ((nodeParent)->spildKeys((nodeParent)));
			
			node.addNode(data,&node);
			//((node.parent)->parent)->preOrder();

			Btree *parent =  (node.parent);
			while(parent->parent !=NULL){
				parent = parent->parent;
			}
			root = *parent;
		}
	}
}

Btree* Btree::spildKeys(Btree* node){

	if( parent ==NULL){
		
		int up = keyDegree/2;

		Btree *root = new Btree();
		root->insertNode(keys.at(up),root);
		Btree *leftNode = new Btree();
	
		for(int i=0;i<up;i++){
			leftNode->insertNode(keys.at(i),leftNode);

			if(!leafs.empty()){
				(leftNode->leafs).push_back( leafs.at(i));
				(leafs.at(i))->parent = leftNode;
			}
		}

		if(!leafs.empty()){
			(leftNode->leafs).push_back( leafs.at(up));
			
			(leafs.at(up))->parent = leftNode;
		}

		leftNode->parent = root;
		
		Btree *rightNode = new Btree();
	
		for(int i=up+1;i<keyDegree;i++){
			rightNode->insertNode(keys.at(i),rightNode);

			if(!leafs.empty()){
				(rightNode->leafs).push_back( leafs.at(i));
				(leafs.at(i))->parent = rightNode;
			}
		}

		if(!leafs.empty()){
			(rightNode->leafs).push_back( leafs.at(keyDegree));
			(leafs.at(keyDegree))->parent = (rightNode);
		}

		rightNode->parent = root;
	
		(root->leafs).push_back(leftNode);
		(root->leafs).push_back(rightNode);
		
		return root;
	}
	else{
		
		int up = keyDegree/2;

		int temp = keys.at(up);

		Btree *root = node->parent;

		Btree *leftNode = new Btree();
		bool hitAdd = false;
		for(int i=0;i<up;i++){
			leftNode->insertNode(keys.at(i),leftNode);
			if( !(node->leafs).empty()){
				(leftNode->leafs).push_back(((node->leafs).at(i)));
				((node->leafs).at(i))->parent = leftNode;
				if(!hitAdd)
					hitAdd = true;
			}
		}
		leftNode->parent = root;

		if( !(node->leafs).empty() && hitAdd){
			(leftNode->leafs).push_back(((node->leafs).at(up)));
			((node->leafs).at(up))->parent = leftNode;

		}

		Btree *rightNode = new Btree();
		hitAdd=false;
		for(int i=up+1;i<keyDegree;i++){
			rightNode->insertNode(keys.at(i),rightNode);
			if( !(node->leafs).empty()){
				(rightNode->leafs).push_back(((node->leafs).at(i)));
				((node->leafs).at(i))->parent = rightNode;
				if(!hitAdd)
					hitAdd = true;
			}
		}
		rightNode->parent = root;

		if( !(node->leafs).empty() && hitAdd){
			
			(rightNode->leafs).push_back(((node->leafs).at(keyDegree)));
			((node->leafs).at(keyDegree))->parent = rightNode;
		}

		bool lastHit = false;

		for(int i=0;i<(root->leafs).size();i++){
			if( (root->leafs).at(i) == node){
				(root->leafs).at(i) = leftNode;
				lastHit = true;
				(root->leafs).push_back(rightNode);
				Btree *tempNode = (root->leafs).at( (root->leafs).size()-1);
				for(int j =(root->leafs).size()-1;j>i+1;j--){
					(root->leafs).at(j) = (root->leafs).at(j-1);
				}
				(root->leafs).at(i+1) = rightNode;
				break;
			}
		}

		if(!lastHit){
			(root->leafs).push_back(leftNode);
			(root->leafs).push_back(rightNode);
		}
			
		(root->keys).push_back(temp);
		root->arrangeKeys();

		return (root);
	}
	
}

Btree* Btree::travelNode(int data,bool& hit){
	Btree *node;
	
	if( leafs.empty()){
		hit =true;
		node = this;
	}
	else{
		int i=0;
		for(i=0;i<keys.size();i++){
			
			if(data<keys.at(i)){
				node = (leafs.at(i))->travelNode(data,hit);
				break;
			}
		}
		if(!hit){
			node = (leafs.at(i))->travelNode(data,hit);
		}
	}
	
	return node;
}

Btree* Btree::addNode(int data,Btree* root){

	if( leafs.empty()){
			
		root->insertNode(data,this);
	}
	else{
		/*Btree *node;
		bool hit = false;
		node = root->travelNode(data,hit);
		
		node = node->insertNode(data,node);*/
		Btree *node;
		bool hit = false;
		node = root->travelNode(data,hit);
		
		root->insertNodeleaf(data,*node,*root);
	}

	return root;
}

Btree & Btree::operator+(int data){
	
	if( leafs.empty()){
			
		insertNode(data,this);
	}
	else{
		Btree *node;
		bool hit = false;
		node = travelNode(data,hit);
		
		node = node->insertNode(data,node);
	}

	return *this;
}

Btree * Btree::searchNode(int key,int& seq ){
	
	Btree *hitPosition;
	hitPosition = NULL;
	
	if(!keys.empty()){
		int i=0;
		for(i=0;i<keys.size();i++){
			if(key == keys.at(i)){
				hitPosition = this;
				break;
			}
			else if(key<keys.at(i)){
				hitPosition = (leafs.at(i))->searchNode(key,seq);
				seq = i;
				break;
			}
		}
		if(i == keys.size()){
			hitPosition = (leafs.at(i))->searchNode(key,seq);
		}
	}

	return hitPosition;

}

Btree * Btree::searchNode(int key){
	
	Btree *hitPosition;
	hitPosition = NULL;
	
	if(!keys.empty()){
		int i=0;
		for(i=0;i<keys.size();i++){
			if(key == keys.at(i)){
				hitPosition = this;
				break;
			}
			else if(key<keys.at(i)){
				hitPosition = (leafs.at(i))->searchNode(key);
				break;
			}
		}
		if(i == keys.size()){
			hitPosition = (leafs.at(i))->searchNode(key);
		}
	}

	return hitPosition;

}

void Btree::deleteNode(int key){
	int seq =0;
	Btree * currentNode = searchNode(key,seq);

	if(currentNode!=NULL && currentNode->parent!=NULL){

		if((currentNode->keys).size() > degree-1){
			int i =0;
			for(i=0;i<(currentNode->keys).size();i++){
				if(key == (currentNode->keys).at(i)){
					break;
				}
			}
			(currentNode->keys).erase((currentNode->keys).begin()+i);
		}
		else{
			//currentNode->preOrder();
			Btree * parent = currentNode->parent;
			if(seq>0){
				if( (((parent->leafs).at(seq-1))->keys).size()>degree-1){
					//int downValue = (((parent->leafs).at(seq-1))->keys).back();

					int i =0;
					for(i=0;i<(currentNode->keys).size();i++){
						if(key == (currentNode->keys).at(i)){
						break;
						}
					}
					(currentNode->keys).erase((currentNode->keys).begin()+i);

					(currentNode->keys).push_back( (parent->keys).at(seq-1));

					currentNode->arrangeKeys();

					(parent->keys).at(seq-1) = (((parent->leafs).at(seq-1))->keys).back();
					(((parent->leafs).at(seq-1))->keys).pop_back();

				}
				else if(seq+1<(parent->leafs).size() 
						&& (((parent->leafs).at(seq+1))->keys).size()>degree-1 ){
					int i =0;
					for(i=0;i<(currentNode->keys).size();i++){
						if(key == (currentNode->keys).at(i)){
						break;
						}
					}
					
					(currentNode->keys).erase((currentNode->keys).begin()+i);

					(currentNode->keys).push_back( (parent->keys).at(seq));

					currentNode->arrangeKeys();
					
					(parent->keys).at(seq) = (((parent->leafs).at(seq+1))->keys).front();
					(((parent->leafs).at(seq+1))->keys).erase((((parent->leafs).at(seq+1))->keys).begin());
					
				}
			}
		}

		
	}

}

int main(){
	Btree* root = new Btree();

	int value[14] = {11,8,7,3,4,6,9,15,21,23,2,1,10,5};

	for(int i=0;i<14;i++){
		
		if( (root->leafs).empty()){
			
			root->insertNodeleaf(value[i],*root,*root);
		}
		else{
			Btree *node;
			bool hit = false;
			node = root->travelNode(value[i],hit);
			
			
			root->insertNodeleaf(value[i],*node,*root);
		}
		//root->addNode(value[i],root);
	}


	//root = root+25;

	root = root->addNode(25,root);

	root = root->addNode(12,root);
	root = root->addNode(19,root);
	root = root->addNode(22,root);
	root = root->addNode(17,root);
	root = root->addNode(32,root);
	root = root->addNode(14,root);
	root = root->addNode(26,root);

	root = root->addNode(36,root);
	root = root->addNode(66,root);
	root = root->addNode(68,root);
	root = root->addNode(0,root);
	
	//root->preOrder();
	//Btree *node;
	//node = root->searchNode(15);
	//node = node->parent;
	//node->preOrder();
	/*root->deleteNode(15);
	root->deleteNode(22);
	root->deleteNode(23);*/
	/*if( (root->keys).size() > (root->keyDegree) ){

		root = root->spildKeys(root);
	}*/
	root->preOrder();
	
	return 1;
}


