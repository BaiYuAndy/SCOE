#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>

#define N 6
#define MAX 0x3f3f3f3f

using namespace std;

int data[N][N] = { 	{0,10,MAX,MAX,MAX,3},
					{MAX,0,7,5,MAX,MAX},
					{MAX,MAX,0,MAX,MAX,MAX},
					{3,MAX,4,0,7,MAX},
					{MAX,MAX,MAX,MAX,0,MAX},
					{MAX,2,MAX,6,1,0},
				};

vector<int> * setDataInit(int *data,int size){
	vector<int> *init = new vector<int>;

	for(int i=0;i<size;i++){
		init->push_back( *(data+i));
		
	}

	return init;
}

struct node{
		int start;

		int end;
	};

bool inQueue(int node,vector<int> *list){
	bool visit = false;

	if(!list->empty()){
		for(int i=0;i<list->size();i++){
			if(list->at(i) == node){
				visit = true;
				break;
			}
		}
	}
	return visit;
}

int shortNode(vector<int> &nodeList,vector<int>* visitList){
	int i=0;
	int temp = MAX;
	int seq = -1;
	while(i <nodeList.size()){
		if( !inQueue(i,visitList)){
			if(temp > nodeList.at(i) ){
				temp = nodeList.at(i);
				seq = i;
			}
		}
		i++;
	}
	
	return seq;
}

stack<int> roadList; 
int last[N];

vector<int>  * vectorToStack(stack<int> *s){
	stack<int> *des = new stack<int>;
	vector<int> *dev =new vector<int>;

	while(!s->empty()){
		des->push(s->top());
		s->pop();
	}
	while(!des->empty()){
		dev->push_back(des->top());
		des->pop();
	}
	return dev;
}

int sreachRoad(int last[N],int start,int end,stack<int> &road){
	int lastNode = -1;
	for(int i=0;i<N;i++){
		if(end == i){
			lastNode = last[i];
			road.push(lastNode);
		}
	}
	if(lastNode != start){
		lastNode = sreachRoad(last,start,lastNode,road);
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
	cout<<"please input Start node(1-6): ";
	int startPosition = 0;
	cin>>startPosition;
	startPosition--;

	int node = startPosition;

	vector<int> *visitNode = new vector<int>;

	visitNode->push_back(node);

	int seq = node;
	int total = MAX;
	//int lastOne = startPosition;
	
	for(int i=0;i<N;i++){
		last[i] = startPosition;
	}

	while(visitNode->size()<N){

		node = shortNode( (*Graph->at(seq)),visitNode);
		//cout<<node<<endl;
		//bool set =false;
		visitNode->push_back(node);

		for(int i=0;i<(Graph->at(node))->size();i++){
			total = (Graph->at(seq))->at(node) + (Graph->at(node))->at(i);
			if( (Graph->at(seq))->at(i) > total){
				(Graph->at(seq))->at(i) = total;
				
				last[i] = node;
			}
		}
		
	}
	cout<<"every Position value as below : \n"
	for(int i=0;i<(Graph->at(seq))->size();i++){
		cout<<(Graph->at(seq))->at(i)<<"\t";
	}
	
	cout<<"\n";
	/*visitNode seqeue*/
	for(int i=0;i< visitNode->size();i++){
		cout<<visitNode->at(i)+1<<"\t";
	}
	cout<<"\n";
	/*every node last poitition i mean current node [i]value is last node*/
	for(int i=0;i< N;i++){
		cout<<last[i]<<"\t";
	}
	cout<<"\n";

	cout<<"please input End Position(1~6) :";
	int endPosition = 0;
	cin>>endPosition;
	endPosition--;

	stack<int>* listRoad = new stack<int>;
	listRoad->push(endPosition);

	sreachRoad(last,startPosition, endPosition,*listRoad);

	cout<<"the shortest road as below: \n";
	while(!listRoad->empty()){
		cout<<(listRoad->top()+1)<<"-->";
		listRoad->pop();
	}
	
	
	return 1;
}


