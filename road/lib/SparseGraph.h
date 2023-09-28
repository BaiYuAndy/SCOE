#ifndef _S_GRAPH_H_
#define _S_GRAPH_H_

#include <vector>
#include <assert.h>
#include <iostream>

#include "DenseGraph.h"

using namespace std;

class SparseGraph {
	public:
		int n;// 节点数
		
		int m;// 边数
		
		bool directed;// 是否为有向图
		
		vector<int> g;// 图的具体数
		vector < vector<int> > g2;
		
		vector <bool> visited;
		vector <int> id;
		
		vector <int> from;
		


    // 构造函数
	void initSparseGraph( int node ,bool directed){
        assert( node >= 0);
		
        this->n = node;
        this->m = 0;  
        this->directed = directed;
        
		// g初始化为n个空的vector, 表示每一个g[i]都为空, 即没有任和边
		int i =0;
	
		while(i<node){
			
			cout<<"For node "<<i<<" input directed: ";
			
			int direct;
			
			cin>>direct;
			
			if(direct > -1 && direct< n)
				(this->g).push_back(direct);
			else{
				(this->g2).push_back(this->g);
				
				this->g.clear();
				
				i++;
			}

		}
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
	
	bool hasEdge(int v,int w){
		assert (v >= 0 && v < n) ;
		assert (w >= 0 && w < n );
		
		bool hitPosition = false;
		
		vector<vector<int> >::iterator end = this->g2.end();
		int i = 0,j;
		for(vector<vector<int> >::iterator begin = this->g2.begin(); begin != end; begin++) {
			j=0;
		
			vector<int>::iterator end= (*begin).end();
			
			for(vector<int>::iterator beginsmall= (*begin).begin(); beginsmall != end; beginsmall++){
		
				if( i==v && *beginsmall==w )
					hitPosition = true;
				
				j++;
			}
			
			i++;
		}
		
		return hitPosition;
	}
	
	void addEdge( int v, int w ){
        assert (v >= 0 && v < n) ;
        assert (w >= 0 && w < n) ;
        
		int i=0;
		vector<vector<int> >::iterator end = this->g2.end();
		
		for(vector<vector<int> >::iterator begin = this->g2.begin(); begin != end; begin++) {
		
			if(i ==v){
				
				(*begin).push_back(w);
				
				
				break;
			}
			
			i++;
		}
        
		if( v != w && !directed ){
			i=0;
			vector<vector<int> >::iterator end = this->g2.end();
		
			for(vector<vector<int> >::iterator begin = this->g2.begin(); begin != end; begin++) {
		
				if(i ==w){
					
					(*begin).push_back(v);
					
					
					break;
				}
			
			i++;
			}
		}
        
		(this->m)++;
    }
	
	void adjMatirxTable(DenseGraph *graph){
		for(int v = 0 ; v < this->n ; v ++ ){
			for(int i = 0 ; i < this->n ; i ++ ){
				if( graph->hasEdge(v,i) )
					this->g.push_back(i);
			}
		
			this->g2.push_back(this->g);
			this->g.clear();
		}
	}
	
	vector<int> dfsSort;
	
	void dfsGraph(int v){
			visited.at(v) = true;
			id.at(v) = ccount;

			int i=0;
			vector<vector<int> >::iterator end = this->g2.end();
		
			for(vector<vector<int> >::iterator begin = this->g2.begin(); begin != end; begin++){
				if(i == v){
				
					vector<int>::iterator end= (*begin).end();
			
					for(vector<int>::iterator beginsmall= (*begin).begin(); beginsmall != end; beginsmall++){
		
						if( !visited.at(*beginsmall) ){
							//cout<<*beginsmall<<"\t";
							//from.pop_back();
							from.at(*beginsmall) = v;
							
							dfsSort.push_back(*beginsmall);
							dfsGraph(*beginsmall);
						}
					
				}
				
			}
			//cout<<"\nlist: "<<i<<endl;
			i++;
		}
	}
	
	void components(){
    // 算法初始化
		ccount = 0;
		
		int i;
		for( i = 0 ; i < this->n ; i ++ ){
			visited.push_back(false);
			id.push_back(-1);
			
			from.push_back(-1);
			//ord.push_back(-1);
		}
    // 求图的联通分量
		for( i = 0 ; i < this->n ; i++ ){
			if( !visited.at(i) ){
				dfsGraph(i);
				ccount++;
			}
		}
	}
	
	private:
		int ccount;

};


#endif 
