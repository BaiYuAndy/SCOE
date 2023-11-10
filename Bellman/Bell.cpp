#include<iostream>
#include<vector>
#include<stdlib.h>
#include<stack>

using namespace std;
#define MAX 0x3f3f3f3f

#define N 6

int data[N][N]={ {0,	10,	MAX,MAX,MAX, 8},
				 {MAX,	0,	MAX,2,	MAX,MAX},
				 {MAX,	1,	0,	MAX,MAX,MAX},
				 {MAX,	MAX,-2,	0,	MAX,MAX},
				 {MAX,	-4,	MAX,-1,	0, 	MAX},
				 {MAX,	MAX,MAX,MAX, 1,	0},
				};

int dataInit[N];


//vector< vector<int>* > *Graph;

//vector<int> *A; 

vector<int> * setDataInit(int *data,int size){
	vector<int> *init = new vector<int>;

	for(int i=0;i<size;i++){
		init->push_back( *(data+i));
		
	}

	return init;
}

typedef struct Edge{
	int start;
	int end;
}ED;

//vector<vector<int> > list;

void edgeVisit(int end,vector<vector<int> >& list){

	if(!list.empty()){
		int i=0;
		while(i<list.size()){
			for(int j=0;j<(list.at(i)).size();j++){
				if((list.at(i)).back() == end){
					list.erase(list.begin()+i);
					break;
				}
			}	
			i++;
		}
	}	
}

bool visitRoad(int start,int end,vector<vector<int> >& list){
	bool visit = false;

	if(!list.empty()){
		for(int i=0;i<list.size();i++){
			for(int j=0;j<(list.at(i)).size();j++){
				if( (list.at(i)).at(j) == start ){
					if( (list.at(i)).back() == end ){
						visit = true;
						break;
					}
				}
			}
		}
	}

	return visit;
}

void show(vector<int> *A){
	for(int i=0;i<N;i++){
		if(A->at(i) <MAX)
			cout<<A->at(i)<<"\t";
		else
			cout<<"INFINITY";
	}
	cout<<"\n";
}

vector<int>& bell(vector<int> *A,vector< vector<int>* > *Graph,vector<vector<int> > &list){
	for(int k=0;k<N;k++){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if( A->at(j) > ( (Graph->at(i))->at(i) +(Graph->at(i))->at(j) ) 
					&& i!=j
					&& A->at(i)!=MAX ){//this node does not connect to S in this loop
	
					A->at(j) = (Graph->at(i))->at(i) +(Graph->at(i))->at(j);
					(Graph->at(j))->at(j) = A->at(j); 
	
					edgeVisit(j,list);
					vector<int> road;
					
					road.push_back(i);
					road.push_back(j);
	
					list.push_back(road);
				}
			}
		}
	}
	return *A;
}

int main(){

	vector< vector<int>* > *Graph;

	Graph = new vector<vector<int>* >; 

	for(int i=0;i<N;i++){
		Graph->push_back(setDataInit( data[i],N));
	}

	vector<int> *A; 

	for(int i=0;i<N;i++){
		if(i==0)
			dataInit[0] = 0;
		else
			dataInit[i] = MAX;
	}

	A = setDataInit(dataInit,N);

/*for(int k=0;k<N;k++){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
		
			if( A->at(j) > ( (Graph->at(i))->at(i) +(Graph->at(i))->at(j) ) 
				&& i!=j
				&& A->at(i)!=MAX ){//this node does not connect to S in this loop

				A->at(j) = (Graph->at(i))->at(i) +(Graph->at(i))->at(j);
				(Graph->at(j))->at(j) = A->at(j); 

				edgeVisit(j);
				vector<int> road;
				
				road.push_back(i);
				road.push_back(j);

				list.push_back(road);
			}
		
		}
	}
}*/
	vector<vector<int> > list;
	A =&bell(A,Graph,list);
	show(A);
	
	stack<int> road;

	int i=list.size()-1;
	while(i >=0 ){
		for(int j=(list.at(i)).size()-1; j>=0;j--){
			//cout<<(list.at(i)).at(j)<<"\t";

			if(j== (list.at(i)).size()-1)
				road.push( (list.at(i)).at(j));
		}
		//cout<<"\n";		
		i--;
	}
	
	road.push(0);

	while(!road.empty()){
		cout<<road.top()<<"\t";
		road.pop();
	}

	/*cout<<"\n";

	for(int k=0;k<N;k++){
		for(int i=0;i<N;i++){
			if( (Graph->at(k))->at(i) <MAX )
				cout<<(Graph->at(k))->at(i)<<"\t\t";
			else
				cout<<"INFINITY\t";
		}
		cout<<"\n";
	}
	*/
	return 0;
}



