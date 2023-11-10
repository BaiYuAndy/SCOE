#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <cassert>

#define N 6;

using namespace std;

class Graph{
	public:
	
	int n;//节点数
	
	vector<vector<int> > g2;
	vector<int> g;
	
	int maxValue;
	
	vector<int> visited;
	vector<int> road;
	
	int getListValue(int v,int w){
		//assert (v >= 0 && v < n) ;
		//assert (w >= 0 && w < n );
		int value = -1;
		vector<vector<int> >::iterator end = this->g2.end();
		
		int i = 0,j;
		
		for(vector<vector<int> >::iterator begin = this->g2.begin(); begin != end; begin++) {
			j=0;
	
			vector<int>::iterator end= (*begin).end();
           
			for(vector<int>::iterator beginsmall= (*begin).begin(); beginsmall != end; beginsmall++){
	
				if(i==v && j==w){
					//return *beginsmall;
					value = *beginsmall;
					break;
				}
				j++;
			}
			
			i++;
		}
		return value;
	}
	
	void showTable(){
		vector<vector<int> >::iterator end = this->g2.end();
		int i = 0,j;
		for(vector<vector<int> >::iterator begin = this->g2.begin(); begin != end; begin++) {
			i++;
			j=0;
		
			vector<int>::iterator end= (*begin).end();
           
			for(vector<int>::iterator beginsmall= (*begin).begin(); beginsmall != end; beginsmall++){
				j++;
		
				cout<<*beginsmall<<"\t";
			}
			cout<<endl;
		}
	}
};

int roadNodeValue[6][6]={
	0,7,9,-1,-1,14,	
	7,0,10,15,-1,-1,
	9,10,0,11,-1,2,	
	-1,15,11,0,6,-1,
	-1,-1,-1,6,0,9,
	14,-1,2,-1,9,0,
};

int getMax(int roadNodeValue[6][6]){
	int max = 0;
	
	for(int i = 0;i<6;i++){
		for(int j=0;j<6;j++){
			if(roadNodeValue[i][j] >0)
				max +=roadNodeValue[i][j];
		}
	}
	
	return max+1;
};

void transferMatirx(int roadNodeValue[6][6],int input){
	
	assert(input<6 && input > 0);
	
	int temp = 0;
	
	for(int i = 0;i<6;i++){
		for(int j=0;j<6;j++){
			if(input == j){
				temp = roadNodeValue[i][j];
				roadNodeValue[i][j] = roadNodeValue[i][0];
				roadNodeValue[i][0] = temp;
			}
		}
	}
};

bool wholeVisted(Graph graph){
	
	bool all = true;
	
	int i = 0;
	
	while(i < graph.n){
		if(graph.visited.at(i) == -1)
			all = false;
		
			i++;
	}
	
	return all;
	
}

bool hitStartNode(vector<int>* startList,int node){

	bool hit = false;

	for(int i=0;i<startList->size();i++){
		if(node == startList->at(i)){
			hit = true;
			break;
		}

	}

	return hit;
}

int getCapNode(vector< vector<int> > roadList,int size,int node){
	int roadLength = (roadList.size())-1;
	int capNode = 0;
	for(int i=roadLength;i>=0;i--){
		//cout<<roadList[i][size];
		if(roadList[i][size] ==node){
			capNode = i;
			break;
		}
	}
	return capNode;
}

int main(){
	
	Graph graph;
	
	//cout<<"node total : ";
	int nodeTotal = 6;
	//cin>>nodeTotal;
	
	graph.n = nodeTotal;
	
	int (*p)[6];//二维数组
	p = roadNodeValue;
	
	int max = getMax(p);
	
	vector<vector<int> > list;
	
	vector<int> valueOrder;
	
	cout<<"please input start node :";
	int input;
	cin>>input;
	
	for(int v = 0 ; v < nodeTotal ; v ++ ){
		for(int i = 0 ; i < nodeTotal ; i ++ ){
			
			if(roadNodeValue[v][i] == -1)
				graph.g.push_back(max);
			else
				graph.g.push_back(roadNodeValue[v][i]);
			
		}
		
		graph.visited.push_back(-1);
		
		//nodeOrder.push_back(-1);
		valueOrder.push_back(max);
		
		graph.road.push_back(max);
		
		graph.g2.push_back(graph.g);
		graph.g.clear();
	}
	
	//graph.showTable();
	
	int startNode = input;
	
	valueOrder.at(startNode) = 0;
	
	vector<int> nodeOrder;
	//add code in sep 27
	vector<int> startList;//from start node to node
	vector< vector<int> > roadList;// define for start to every node short list
	vector<int> temp;// node part input in it
	
	while( !wholeVisted(graph) ){
	
		if(nodeOrder.size() < nodeTotal)
			nodeOrder.push_back(startNode);
	
		graph.visited.at(startNode) = 1;
	
		graph.road.at(startNode) = 0;
	
		vector<vector<int> >::iterator end = graph.g2.end();
	
		int i = 0;
	
		for(vector<vector<int> >::iterator begin = graph.g2.begin(); begin != end; begin++){
		
			if(startNode == i){
				
				vector<int>::iterator end= (*begin).end();
				
				int j = 0;
				
				for(vector<int>::iterator beginsmall= (*begin).begin(); beginsmall != end; beginsmall++){
					
					if(*beginsmall >0 && *beginsmall < max){
						
						if(*beginsmall < valueOrder.at(j)){
							
							if(i == input){
								graph.road.at(j) = *beginsmall;
								
								valueOrder.at(j) = graph.road.at(j);
								
								//cout<<"start: "<<i<<"\t"<<j<<"\t";
								startList.push_back(j);
							}
							else if( *beginsmall + valueOrder.at(i) < valueOrder.at(j)){
								
								graph.road.at(j) = *beginsmall + graph.road.at(i);
								valueOrder.at(j) = *beginsmall + valueOrder.at(i);
								
								//cout<<"node: "<<i<<"\t"<<j<<"\t";
								temp.clear();
								temp.push_back(i);
								temp.push_back(j);
								roadList.push_back(temp);
							}
							
						}
					}
					
					j++;
				}
				
			}
			
			i++;				
		}	
			int k = 0;
			int maxTempValue = max;
			while(k<valueOrder.size()){
				if(graph.visited.at(k) == -1){
					if(maxTempValue > valueOrder.at(k)){
						maxTempValue = valueOrder.at(k);
						startNode = k;
					}
				}
			
				k++;
			}
	}
	
	/*int i = 0;
	
	while(i<nodeTotal){
			cout<<i<<"\t"<<valueOrder.at(i)<<endl;
		i++;
	}

*/
	//
	int tempSize = temp.size()-1;
	int hitTime=0;

	while(hitTime<6 ){

		int capLength = getCapNode(roadList, tempSize,hitTime);
	
		vector<int> middleNodeList;
		int useNode = -1;
		int useEndNode = -1;
		int roadLength = capLength;//(roadList.size()- 1);
		
		for(int i=roadLength;i>=0;i--){
			//int tempSize
			for(int j=temp.size()-1;j>=0;j--){
				if(roadList[i][0] !=useNode){
					
					if((roadList[i][j]!= useEndNode) && (i==roadLength||(roadList[i][tempSize]==useEndNode) ) ){
						middleNodeList.push_back(roadList[i][j]);	
					}
						if(j==temp.size()-1)
							useNode = roadList[i][j];
						else if(j ==0)
							useEndNode = roadList[i][j];
				}
			}
		}

		if(hitTime ==  middleNodeList.at(0)){
			cout<<"To node "<<middleNodeList.at(0)<<" road:";
			cout<<input<<"\t";
			for(int i=middleNodeList.size()-1;i>=0;i--)
				cout<<middleNodeList.at(i)<<"\t";
			cout<<"value is :"<<valueOrder.at(middleNodeList.at(0));

			middleNodeList.clear();
			cout<<endl;
		}
	
		else{
			cout<<"To node "<<hitTime<<" road:"<< input<<"\t"<<hitTime<<"\t"<<"value is :"<<valueOrder.at(hitTime);
			cout<<endl;
		}
		
		hitTime++;
		
	}

	/*cout<<"run node list is :";
	for(int i = 0;i< nodeOrder.size();i++)
		cout<<nodeOrder.at(i)<<"\t";*/
	return 0;	
}





