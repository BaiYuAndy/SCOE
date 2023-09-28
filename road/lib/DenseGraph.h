#ifndef _D_GRAPH_H_
#define _D_GRAPH_H_

#include <vector>
#include <assert.h>
#include <iostream>

using namespace std;

class DenseGraph{
	private:
		int n;//节点数
		int m;//边数
		bool directed;//是否是有向图
		
	public:
	
		/*替代二维数组，存储路径**/
		vector <bool> g;
		vector < vector<bool> > g2;
		
	
		DenseGraph(){
			this->n = 0;
			this->m = 0;
			
			this->directed = 1;
		}
		
		void initDenseGraph(int n, bool directed){
			assert( n >=0);
			
			this->n = n;
			this->m = 0;
			
			this->directed = directed;
		}
		
		//~DenseGraph();
	
		bool getMatirxPosition(int v,int w){
			bool newBeginSmall = false;
			assert (v >= 0 && v < n) ;
			assert (w >= 0 && w < n );
			
			vector<vector<bool> >::iterator end = this->g2.end();
			int i = 0,j;
			for(vector<vector<bool> >::iterator begin = this->g2.begin(); begin != end; begin++) {
				j=0;
		
				vector<bool>::iterator end= (*begin).end();
            
				for(vector<bool>::iterator beginsmall= (*begin).begin(); beginsmall != end; beginsmall++){
		
					if(i==v && j==w){
						//return *beginsmall;
						newBeginSmall = *beginsmall;
					}
					j++;
				}
				
				i++;
			}
			return newBeginSmall;
		}
	
		
		bool hasEdge( int v , int w ){
			assert (v >= 0 && v < n) ;
			assert (w >= 0 && w < n );
			
			bool hasEdge = getMatirxPosition(v,w);

			return hasEdge;
		}
		void showMatrix(){
			vector<vector<bool> >::iterator end = this->g2.end();
			int i = 0,j;
			for(vector<vector<bool> >::iterator begin = this->g2.begin(); begin != end; begin++) {
				i++;
				j=0;
		
				vector<bool>::iterator end= (*begin).end();
            
				for(vector<bool>::iterator beginsmall= (*begin).begin(); beginsmall != end; beginsmall++){
					j++;
		
					cout<<*beginsmall<<"\t";
				}
				cout<<endl;
			}
		}
	
		void addEdge( int v , int w ){
			assert (v >= 0 && v < n );
			assert (w >= 0 && w < n );
			
			if( hasEdge( v , w ))
				return;
			
			vector<vector<bool> >::iterator end = this->g2.end();
			int i = 0,j;
			for(vector<vector<bool> >::iterator begin = this->g2.begin(); begin != end; begin++) {			
				j=0;
		
				vector<bool>::iterator end= (*begin).end();
            
				for(vector<bool>::iterator beginsmall= (*begin).begin(); beginsmall != end; beginsmall++){
		
					if(i==v && j==w)
						*beginsmall = true;
					
					j++;
				}
				
				i++;
			}
			
			if( !this->directed ){
				vector<vector<bool> >::iterator end = this->g2.end();
				int i = 0,j;
				for(vector<vector<bool> >::iterator begin = this->g2.begin(); begin != end; begin++) {
					
					j=0;
			
					vector<bool>::iterator end= (*begin).end();
				
					for(vector<bool>::iterator beginsmall= (*begin).begin(); beginsmall != end; beginsmall++){
			
						if(i==w && j==v)
							*beginsmall = true;
						
						j++;
					}
					
					i++;
				}
			}
			(this->m)++;
		}
		
		
};

#endif 

