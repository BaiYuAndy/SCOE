#ifndef _SP_GRAPH_H_
#define _SP_GRAPH_H_

#include <vector>
#include <assert.h>
#include <iostream>
#include <queue>
#include <stack>

#include "SparseGraph.h"

using namespace std;

class shortPath{
	public:
	
	int start;
	vector <int> ord;
	vector <bool> visited;
	vector <int> from;
	
	SparseGraph graph;
	
	void initShortestPath(SparseGraph graph){
		this->graph = graph;
	}
	
	bool hasPath(int w){
		assert(w >= 0 && w < this->graph.n);
		return visited.at(w);
	}
	
	void shortestPath(int s){

        // 算法初始化
		assert (s >= 0 && s < graph.n);
		
		for(int i = 0 ; i < graph.n ; i ++ ){
			this->visited.push_back(false);
			//id.push_back(-1);
		
			from.push_back(-1);
			this->ord.push_back(-1);
		}
        
		this->start = s;
			
		// 无向图最短路径算法, 从s开始广度优先遍历整张图
		queue<int> q;
		q.push( start );
		this->visited.at(start) = true;
        
		this->ord.at(start) = 0;
        
		while( !q.empty() ){
			int v = q.front();
			q.pop();
			
			int i=0;
			vector<vector<int> >::iterator end = graph.g2.end();
		
			for(vector<vector<int> >::iterator begin = graph.g2.begin(); begin != end; begin++){
				
				if(i == v){
					vector<int>::iterator end= (*begin).end();
			
					for(vector<int>::iterator beginsmall= (*begin).begin(); beginsmall != end; beginsmall++){
						
						if( !( (this->visited).at(*beginsmall) )){
							q.push(*beginsmall);
							(this->visited).at(*beginsmall) = true;
							from.at(*beginsmall) = v;
							
							//cout<<*beginsmall<<"\t"<<this->ord.at(*beginsmall)<<endl; 
							this->ord.at(*beginsmall) = this->ord.at(v) + 1;
						}	
					}	
				}
				
			i++;
			}
       }
    }
	
	vector<int> road;
	
	void pathNode(int w){
        assert( hasPath(w)) ;
        stack<int> s ;
        // 通过from数组逆向查找到从s到w的路径, 存放到栈中
        int p = w;
        while( p != -1 ){
            s.push(p);
            p = from.at(p);
        }

        // 从栈中依次取出元素, 获得顺序的从s到w的路径
        // = new Vector<Integer>();
        while( !s.empty() ){
			road.push_back(s.top());
			s.pop();
		}

    }
	
	void shortRoad(int start,int end){
		assert( start>=0 && end< graph.n) ;
		
		shortestPath(start);
		pathNode(end);
		
		cout<<"this is shortest road list :";
		for(int i = 0;i<road.size(); i++){
			cout<<road.at(i)<<"\t";
		}
		
		
		vector<int> listBFS;
		for(int i = 0;i<ord.size(); i++){
			listBFS.push_back(i);
		}
		
		for(int i = 0;i<ord.size(); i++){
			for(int j =0;j<i;j++){
				if(ord.at(j) > ord.at(i)){
					
					int temp = listBFS.at(j);
					listBFS.at(j) = listBFS.at(i);
					listBFS.at(i) = temp;
				}
			}
		}
		
		cout<<"\nthis is Breadth First traversal :";
		for(int i = 0;i<listBFS.size(); i++){
			cout<<listBFS.at(i)<<"\t";
		}
	}
};

#endif
