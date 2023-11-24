#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

#define N 3

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
	void showKey();
	void arrangeKeys();
	void preOrder();

	Btree* spildKeys(Btree* node);

	Btree* travelNode(int data,bool& hit);

	Btree & operator+(int data); 
	Btree* addNode(int data,Btree* root);
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

Btree* Btree::spildKeys(Btree* node){

	if(parent ==NULL){
		int up = keyDegree/2;

		Btree *root = new Btree();
		root->insertNode(keys.at(up),root);
		Btree *leftNode = new Btree();
	
		for(int i=0;i<up;i++)
			leftNode->insertNode(keys.at(i),leftNode);
		leftNode->parent = root;
		
		Btree *rightNode = new Btree();
	
		for(int i=up+1;i<keyDegree;i++)
			rightNode->insertNode(keys.at(i),rightNode);
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
	
		for(int i=0;i<up;i++)
			leftNode->insertNode(keys.at(i),leftNode);
		leftNode->parent = root;
		
		Btree *rightNode = new Btree();
	
		for(int i=up+1;i<keyDegree;i++)
			rightNode->insertNode(keys.at(i),rightNode);
		rightNode->parent = root;

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
		
		free(node);
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
		Btree *node;
		bool hit = false;
		node = root->travelNode(data,hit);
		
		node = node->insertNode(data,node);
	}

	return root;
}

Btree & Btree::operator+(int data){
	cout<<data;
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

int main(){
	Btree* root = new Btree();

	int value[14] = {11,8,7,3,4,6,9,15,21,23,2,1,10,5};

	for(int i=0;i<14;i++){
		
		if( (root->leafs).empty()){
			
			root = root->insertNode(value[i],root);
		}
		else{
			Btree *node;
			bool hit = false;
			node = root->travelNode(value[i],hit);
			
			node = node->insertNode(value[i],node);
		}
		
	}
	//root = root+25;

	root = root->addNode(25,root);
	root = root->addNode(12,root);
	root = root->addNode(18,root);
	
	root->preOrder();

	
	return 1;
}


