#include <iostream>
#include <vector>
#include <stack>

#define N 7

using namespace std;

int data[N][N] = { 	{0,1,1,-1,-1,1,-1},
					{1,0,-1,-1,-1,-1,-1},
					{1,-1,0,-1,-1,-1,-1},
					{-1,-1,-1,0,1,1,-1},
					{-1,-1,-1,1,0,1,1},
					{1,-1,-1,1,1,0,-1},
					{-1,-1,-1,-1,1,-1,0},
				};

vector<int> * setDataInit(int *data,int size){
	vector<int> *init = new vector<int>;

	for(int i=0;i<size;i++){
		init->push_back( *(data+i));
		
	}

	return init;
}

bool inQueue(int node,vector<int> &list){
	bool visit = false;

	if(!list.empty()){
		for(int i=0;i<list.size();i++){
			if(list.at(i) == node){
				visit = true;
				break;
			}
		}
	}
	return visit;
}

stack<int> roadList; 
int last[N];
int fromPosition(vector< vector<int>* > *Graph,vector<int> &visitNode,int seqeue){
	int nextPosition = -1;
	for(int i=0;i<N;i++){
		if( (Graph->at(seqeue))->at(i) == 1 
			&& !inQueue(i,visitNode) ){
			nextPosition = i;
			visitNode.push_back(i);
			roadList.push(i);
			last[i] = seqeue;
		}
	}
	
	return nextPosition;
}

int sreachRoad(int last[N],int end,stack<int> &road){
	int lastNode = -1;
	for(int i=0;i<N;i++){
		if(end == i){
			lastNode = last[i];
			road.push(lastNode);
		}
	}
	if(lastNode > 0){
		lastNode = sreachRoad(last,lastNode,road);
	}

	return lastNode;
}

int main(){

	vector< vector<int>* > *Graph;

	Graph = new vector<vector<int>* >; 

	for(int i=0;i<N;i++){
		Graph->push_back(setDataInit( data[i],N));
	}
	
	/*for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			cout<<(Graph->at(i))->at(j)<<"\t";
		cout<<"\n";
	}*/
	int node = 0;

	vector<int> *visitNode = new vector<int>;

	visitNode->push_back(0);

	while( visitNode->size() < N){
		node = fromPosition(Graph,*visitNode,node);
		if(node == -1){
			node = roadList.top();
			roadList.pop();
		}
	}

	cout<<"breadth-first search as below: \n";
	for(int i=0;i<visitNode->size();i++){
		cout<<visitNode->at(i)<<"\t";
	}
	cout<<"\n";

	/*for(int i=0;i<N;i++){
		cout<<last[i]<<"\t";
	}*/

	stack<int>* listRoad = new stack<int>;
	listRoad->push(6);

	sreachRoad(last,6,*listRoad);

	cout<<"the shortest road as below: \n";
	while(!listRoad->empty()){
		cout<<listRoad->top()<<"\t";
		listRoad->pop();
	}

	return 1;
}


