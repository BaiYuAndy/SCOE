#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>

#define N 5
#define MAX 0x3f3f3f3f

using namespace std;

int data[N][N] = { 	{0,4,MAX,5,MAX},
					{MAX,0,1,MAX,6},
					{2,MAX,0,3,MAX},
					{MAX,MAX,1,0,2},
					{1,MAX,MAX,4,0},

				};

/*{ 	{0,10,MAX,MAX,MAX,3},
					{MAX,0,7,5,MAX,MAX},
					{MAX,MAX,0,MAX,MAX,MAX},
					{3,MAX,4,0,7,MAX},
					{MAX,MAX,MAX,MAX,0,MAX},
					{MAX,2,MAX,6,1,0},
				};*/

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

void sreachRoad(vector< vector<int>* > *Graph,int start,int end,stack<int> &road){
	int inter = (Graph->at(start))->at(end);

	// -1 mean there is no inter node during start to end road
	if(inter != -1){
		road.push(inter);
		sreachRoad(Graph,start,inter,road);
	}
	
}

int main(){

	vector< vector<int>* > *Graph;

	Graph = new vector<vector<int>* >; 

	for(int i=0;i<N;i++){
		Graph->push_back(setDataInit( data[i],N));
	}
	
	int visit[N][N];
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			visit[i][j] = -1;
	}

	vector< vector<int>* > *visitRoad;

	visitRoad = new vector<vector<int>* >; 

	for(int i=0;i<N;i++){
		visitRoad->push_back(setDataInit( visit[i],N));
	}

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(j!=i){
			for(int k=0;k<N;k++){
					if(j!=k){
						int distance = (Graph->at(j))->at(i) + (Graph->at(i))->at(k);
	
						if(distance < (Graph->at(j))->at(k)){

							(Graph->at(j))->at(k) = distance;
							(visitRoad->at(j))->at(k) = i;
						}
					}
				}
			}
		}
	}

	cout<<"all value table as below: \n";
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			if((Graph->at(i))->at(j) == MAX)
				cout<<"MAX"<<"\t";
			else
				cout<<(Graph->at(i))->at(j)<<"\t";
		cout<<"\n";
	}
	/*
	cout<<"\n";
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			if((visitRoad->at(i))->at(j) == MAX)
				cout<<"MAX"<<"\t";
			else
				cout<<(visitRoad->at(i))->at(j)<<"\t";
		cout<<"\n";
	}
	*/
	cout<<"\n";

	cout<<"please input Start node(1~5): ";
	int startPosition = 0;
	cin>>startPosition;
	startPosition--;

	cout<<"please input End Position(1~5) :";
	int endPosition = 0;
	cin>>endPosition;
	endPosition--;

	stack<int>* listRoad = new stack<int>;
	listRoad->push(endPosition);

	sreachRoad(visitRoad,startPosition, endPosition,*listRoad);

	listRoad->push(startPosition);

	cout<<"the shortest road as below: \n";
	while(!listRoad->empty()){
		cout<<(listRoad->top()+1);
		if(listRoad->size() !=1)
			cout<<"-->";
		listRoad->pop();
	}
	
	return 1;
}


