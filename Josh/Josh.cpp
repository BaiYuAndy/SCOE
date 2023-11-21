#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>

#define N 4
#define INF 0x3f3f3f3f

using namespace std;

int data[N][N] = { 	{0,-5,2,3},
					{INF,0,4,INF},
					{INF,INF,0,1},
					{INF,INF,INF,0},

				};

/*{ 	{0,4,INF,5,INF},
					{INF,0,1,INF,6},
					{2,INF,0,3,INF},
					{INF,INF,1,0,2},
					{1,INF,INF,4,0},

				};*/

class Graph{

private:
	vector<vector<int>* > *distanceList;

public:
	void setDataInit(int *data,int size);

	void showDistanceValue();

	Graph(){
		this->distanceList = new vector<vector<int>* >; 
	}

	void floydWarshall();

	void Dijkstra(int seq);

	int shortNode(vector<int> &nodeList,vector<int>* visitList);

	bool inQueue(int node,vector<int> *list);

	vector<int>& bellMan(vector<int> *A);

	void joshCalutor(vector<int> &A);

	void clear(){
		distanceList->clear();
	}
};

void Graph::setDataInit(int *data,int size){
	vector<int> *init = new vector<int>;

	for(int i=0;i<size;i++){
		init->push_back( *(data+i));
		
	}
	distanceList->push_back(init);
}


void Graph::showDistanceValue(){
	cout<<"all value table as below: \n";
	for(int i=0;i<distanceList->size();i++){
		for(int j=0;j< (distanceList->at(i))->size();j++)
			if((distanceList->at(i))->at(j) == INF)
				cout<<"INF"<<"\t";
			else
				cout<<(distanceList->at(i))->at(j)<<"\t";
		cout<<"\n";
	}
}

void Graph::floydWarshall(){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(j!=i){
			for(int k=0;k<N;k++){
					if(j!=k){
						int distance = (distanceList->at(j))->at(i) + (distanceList->at(i))->at(k);
	
						if(distance < (distanceList->at(j))->at(k)){

							(distanceList->at(j))->at(k) = distance;
							//(visitRoad->at(j))->at(k) = i;
						}
					}
				}
			}
		}
	}
}

bool Graph::inQueue(int node,vector<int> *list){
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

int Graph::shortNode(vector<int> &nodeList,vector<int>* visitList){
	int i=0;
	int temp = INF;
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

void Graph::joshCalutor(vector<int>& A){
	for(int i=0;i<distanceList->size();i++){
		for(int j=0;j<(distanceList->at(i))->size();j++){
			if((distanceList->at(i))->at(j) !=INF)
				(distanceList->at(i))->at(j) = ((distanceList->at(i))->at(j)+A.at(i)-A.at(j));
		}
	}
}

void Graph::Dijkstra(int seq){

	int node = seq;

	vector<int> *visitNode = new vector<int>;

	visitNode->push_back(node);

	int total = INF;

	while(visitNode->size()<N){

		node = this->shortNode( (*distanceList->at(seq)), visitNode);

		visitNode->push_back(node);
		
		for(int i=0;i<(distanceList->at(node))->size();i++){
			total = (distanceList->at(seq))->at(node) + (distanceList->at(node))->at(i);
			if( (distanceList->at(seq))->at(i) > total){
				(distanceList->at(seq))->at(i) = total;
				
			}
		}
	}
	
}

vector<int>& Graph::bellMan(vector<int> *A){//in default start node is 0
	for(int k=0;k<N;k++){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if( A->at(j) > ( (distanceList->at(i))->at(i) +(distanceList->at(i))->at(j) ) 
					&& i!=j
					&& A->at(i)!=INF ){//this node does not connect to S in this loop
	
					A->at(j) = (distanceList->at(i))->at(i) +(distanceList->at(i))->at(j);
					(distanceList->at(j))->at(j) = A->at(j); 
				}
			}
		}
	}
	return *A;
}

void show(vector<int> *A){
	for(int i=0;i<N;i++){
		if(A->at(i) <INF)
			cout<<A->at(i)<<"\t";
		else
			cout<<"INFINITY";
	}
	cout<<"\n";
}

int main(){

	Graph *graph = new Graph();

    int (*p)[N] = data;

    for(int i=0;i<N;i++){

    	graph->setDataInit(*(p+i),N);
    }

    //graph->floydWarshall();

    //graph->Dijkstra(0);

    vector<int> *A = new vector<int>; 

	for(int i=0;i<N;i++){
		if(i==0){
			A->push_back(i);
		}
		else
			A->push_back(INF);
	}

	A =&(graph->bellMan(A));
	show(A);

	graph->clear();
	for(int i=0;i<N;i++){

    	graph->setDataInit(*(p+i),N);
    }
    
    graph->joshCalutor(*A);

    graph->showDistanceValue();

    graph->Dijkstra(0);

    graph->showDistanceValue();

	return 1;

}


