#ifndef _TREE_H_
#define _TREE_H_

#undef main

const int data[10] = {8,7,3,5,2,6,10,9,4,1};

bool hitIn(vector<int> data,int hit){
	bool in = false;
	int i=0;
	while(i<10){
		if(hit ==data.at(i)){
			hit = true;
			break;
		}
	}
	return in;
}

typedef struct heapNode{
	int data;

	struct heapNode * leftNode;
	struct heapNode * rightNode;
}HD;

HD * creatHeap(int data,HD *heap){
	//cout<<data<<endl;
	if(heap==NULL){
		heap = (HD *)malloc(sizeof(HD));


		heap->data = data;
		heap->leftNode = NULL;
		heap->rightNode =NULL;
	}
	if(data>heap->data){
		heap->rightNode=creatHeap(data,heap->rightNode);
	}
	else if(data<heap->data){
		heap->leftNode=creatHeap(data,heap->leftNode);
	}
	else
		heap->data = data;

	return heap;
}

vector<vector<int> >* levelOrder(HD *root){
	vector<vector<int> > *res;

	res = new vector<vector<int> >;

	queue<HD*> q;

	if(root ==NULL)
		return res;
	q.push(root);
	vector<int> v;
	while(!q.empty()){
		v.clear();

		int size =q.size();
		while(size--){
			HD* temp=q.front();
			v.push_back(temp->data);
			if(temp->leftNode)
				q.push(temp->leftNode);
			if(temp->rightNode)
				q.push(temp->rightNode);
			q.pop();
		}
		res->push_back(v);
	}
	return res;
}

#endif