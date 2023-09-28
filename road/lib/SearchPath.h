#ifndef _SP_GRAPH_H_
#define _SP_GRAPH_H_

#include <vector>
#include <stack>
#include <queue>
#include <assert.h>
#include <iostream>

#include "SparseGraph.h"

using namespace std;


class SearchPath{
	public:
		SparseGraph graph;
		
		//vector<bool> visited;
		
		vector<int> res;
		
		bool hasPath(int w,SparseGraph graph){
			//cout<<w;
			assert(w >= 0 && w < graph.n);
			return graph.visited.at(w);
		}
	
		void pathSreach(int w,SparseGraph graph){

			assert(hasPath(w,graph) );
	
			stack<int> mystack;
			// 通过from数组逆向查找到从s到w的路径, 存放到栈中
			int p = w;
			while( p != -1 ){
				mystack.push(p);
				p = graph.from.at(p);
			}
	
			// 从栈中依次取出元素, 获得顺序的从s到w的路径
			//int temp;
			while( !mystack.empty() ){
				//temp = mystack.top();
				res.push_back( mystack.top() );
				mystack.pop();
			}
	
			//return res;
		}
		
		int start;
		vector <int> ord;
		vector <bool> visited;
		vector <int> from;
		
		void shortestPath(int s , SparseGraph graph){

        // 算法初始化
			assert (s >= 0 && s < graph.n);
		
			int i;
			for( i = 0 ; i < graph.n ; i ++ ){
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
	
	void pathNode(int w,SparseGraph graph){
		
        assert( hasPath(w,graph)) ;
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
		
}; 

#endif 
