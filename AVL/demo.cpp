#include <iostream>
#include "demo.h"
#include <ctime>

using namespace std;

int main(){
	Node *root = NULL;
	/*int a[10] ={14,78,8,90,21,43,3,12,1,24};
	

	for(int i=0;i<10;i++){
		root = root->insertNode(root,a[i]);
	}*/

	srand(unsigned(time(0)));

	const int MAX = 10000000;
	const int MIN = 100;

	for(int i=0;i<100000;i++){
		int a = rand()%(MAX-MIN+1)+MIN;

		root=root->insertNode(root,a);
	}

	
	/*root = root->insertNode(root,9);
	root = root->insertNode(root,4);

	root = root->delNodeByValue(root,8);
	root = root->delNodeByValue(root,43);
	root = root->delNodeByValue(root,21);

	root->preOrder(root);
	cout<<"\n";
	root->middleOrder(root);
	cout<<"\n";

	root = root->delNodeByValue(root,14);*/

	//Node *pCur = root->searchNode(root,21);

	/*root->preOrder(root);
	cout<<"\n";
	root->middleOrder(root);
	cout<<"\n";*/

	return 1;

}

