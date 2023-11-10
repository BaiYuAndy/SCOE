#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <cmath>

#define N 10

using namespace std;

class Heap{
public:
	int size;
	int length;
	vector<int> list;
	//queue<int>	seq;

	Heap(){
		size =0;
		list.push_back(0);
		length =0;
	}
	~Heap(){

	}

	void shitUp(int data);
	void shitDown(int size);

	void shitDown(int num,int size);

	void erase();

	void createHeap(int size);

	void sortHeap(int size);
};

void Heap::shitUp(int data){
	assert(size>=0);
	if(size ==0){
		list.push_back(data);
		size++;
	}
	else{
		list.push_back(data);
		size = (list.size()-1);

		while(size>1){

			int i= (size)/2;
			
			if(list.at(i)<data){
				int temp =list.at(i);
				list.at(i) = data;
				list.at(size) = temp;
			}
			data = list.at(i);
			size =i;
		}
	}
}

void Heap::shitDown(int size){

	int temp = list.at(1);
	list.at(1) = list.at(size);

	list.at(size) = temp;

	size--;
	
	if(size>0){
	
		int i=1,j=0;

		int length = log2(size)+1;
	
		while(i<length){
			j=0;
			if(list.at(i)<list.at(2*i)){
				int temp = list.at(2*i);
				list.at(2*i) = list.at(i);
				list.at(i) =temp;
				j=2*i;
			}
			
			if(2*i+1 <=size){

				if(list.at(i)<list.at((2*i)+1)){
					int temp = list.at(2*i+1);
					list.at(2*i+1) = list.at(i);
					list.at(i) =temp;
					j=2*i+1;
				}
			}
			if(j==0)
				break;
			else
				i=j;
		}

	}
}

void Heap::erase(){

	int temp = list.at(1);
	list.at(1) = list.at(size);

	list.erase(list.begin()+size);

	size--;
	
	if(size>0){
	
		int i=1,j=0;

		int length = log2(size)+1;
	
		while(i<length){
			j=0;
			if(list.at(i)<list.at(2*i)){
				int temp = list.at(2*i);
				list.at(2*i) = list.at(i);
				list.at(i) =temp;
				j=2*i;
			}
			
			if(2*i+1 <=size){

				if(list.at(i)<list.at((2*i)+1)){
					int temp = list.at(2*i+1);
					list.at(2*i+1) = list.at(i);
					list.at(i) =temp;
					j=2*i+1;
				}
			}
			if(j==0)
				break;
			else
				i=j;
		}

	}
}

void Heap::shitDown(int num,int size){
	assert(size>0 && num>=0 && num<=size);

	int i;
	i=num;

	int data = list.at(num);

	while( (2*i)<=size){
		if(2*i+1 <=size){

			if(list.at(2*i) > list.at(2*i+1)){
				if(list.at(2*i) > data){
					int temp = list.at(2*i);
					list.at(2*i) = data;
					list.at(num) = temp;
					
					num = 2*i;
				}
				
				else
					break;
			}
			else{
				if(list.at(2*i+1) > data){
					int temp = list.at(2*i+1);
					list.at(2*i+1) = data;
					list.at(num) = temp;
					
					num = 2*i+1;
				}
				
				else
					break;
			}

		}
		else{
			if(list.at(2*i) > data){
				int temp = list.at(2*i);
				list.at(2*i) = data;
				list.at(num) = temp;
				
				num = 2*i;
			}
			else
				break;
		}
		i=num;
	}
}

void Heap::createHeap(int size){
	int i=0;

	assert(size>0);
	i= size/2;
	
	while(i>0 ){
		shitDown(i,size);
		
		i--;
	}
}

void Heap::sortHeap(int size){
	
	while(size>0){
		shitDown(size);
		size--;
	}
}

void showList(vector<int> & list){
	int i=1;
	cout<<list.size()-1<<endl;
	while(i < list.size()){
		cout<<list.at(i)<<"\t";
		i++;
	}
	cout<<"\n";
}

int main(){

	//cout<<"hello make file";

	int data[N]={15,17,19,13,22,16,28,30,41,62};

	Heap heap;
	int i=0;
	while(i<10){
		heap.list.push_back(data[i]);
		i++;
	}

	showList((heap.list));

	heap.shitUp(33);
	heap.shitUp(23);

	showList((heap.list));
	
	heap.createHeap(12);
	showList((heap.list));
	
	heap.sortHeap(12);
	
	showList((heap.list));

	heap.erase();
	showList((heap.list));

	return 0;
}



