/*this is simulate to calcutor*/
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef struct hit{
	int seq;
	char ch;
}HD;

int set(char *ch){
	
	int data = -1;
	if( *ch<58 && *ch>47){
		
		data = *ch-48;
 
	}
	return data;
}

int transferInter(char *ch){
	int data = 0;
	int i=0;
	
	while(*(ch+i)!='\0')
			i++;

	int size = i;
	
	i=0;
	while(i<size){
		if(size-i-1>0){			
			data += set((ch+i))*(pow(10,(size-i-1)));
			
		}
		else
			data += set((ch+i));
		i++;

	}
	return data;
}

int run(int begin,int end,char *run){
	int data = 0;
	//cout<<*run<<endl;
	switch(*run){
		case 43:
			data = begin+end;
			break;
		case '*':
			data = begin*end;
			break;
		case 45:
			data = begin-end;
			break;
		case 47:
			data = begin/end;
	}

	return data;
}

int func(vector<char *> list,int first,int last){
	int value =0;
	if( (last-first)==2 ) {

		int begin = transferInter(list.at(first));
		int end = transferInter(list.at(last));
		
		value = run(begin,end,list.at( (last+first)/2) );
	}
	else if((last-first)>2 ){
		vector<HD *> buffer;
		HD *pool;
		for(int i=first;i<=last;i++){
			if(*list.at(i) == '+'
				||*list.at(i) == '-'
				||*list.at(i) == '*'
				||*list.at(i) == '/'){
				pool=(struct hit *)malloc(sizeof(struct hit));
				pool->seq =i;
				pool->ch = *list.at(i);
				buffer.push_back(pool);
			}
		}

		int i = buffer.size()-1;
		
		int mid = 0,rd=0;
		while(i>=0){
			if(buffer.at(i)->ch == '+'
				||buffer.at(i)->ch == '-'){
				mid = i;
				break;
			}
			i--;
		}
		
		value = run( func(list,first,(buffer.at(mid)->seq -1)),
					func(list,(buffer.at(mid)->seq+1),last),
					(list.at(buffer.at(mid)->seq) ) );
			
	}
	else if(first == last){
		
		value = transferInter(list.at(first));
	}

	return value;
}

char* transferChar(int a){
	double i=(double)a;
	int n =9;
	double sbuffer;
	long fsbuffer;
	int bassbuffer =0;
	char *cup = new char[1024];
	char c[2] = {0};
	bool Btrue = true;
	int B=0;
	while(Btrue){
		double N;
		N = i;

		N=N/pow(10,B);
		B++;
		if(N<1)
			break;
	}
	n= --(--B);
	while((n+2)>1){
		bassbuffer = bassbuffer +(int)sbuffer*(pow(10,n+1));
		fsbuffer = sbuffer;
		sbuffer = pow(10,n);
		sbuffer = i/sbuffer;
		if(sbuffer!=0){
			if(fsbuffer !=0){
				sbuffer = (int)(i-bassbuffer)/pow(10,n);
				c[0] = (int)sbuffer+48;
				strcat(cup,c);
			}
			else{
				c[0]=(int)sbuffer+48;
				strcpy(cup,c);
			}
		}
		--n;
	}
	return cup;
}

vector<char*> setList(vector<char*> list){
	int i=list.size()-1;
	bool bracket =false;
	stack<char *> buffer;
	int length=0;
	while(i>=0){
		if(*list.at(i) == ')' && !bracket){
			
			bracket=true;
		}
		else if(bracket && *list.at(i) == ')'){
			while(!buffer.empty()){
				buffer.pop();
				length = 0;
			}
		}
		else if(bracket && *list.at(i)!='('){
			buffer.push(list.at(i));
			length++;
		}
		else if(bracket && *list.at(i)=='(')
			break;
		i--;
	}
	int first = i;

	vector<char *> subList;
	i = 0;
	while(i<length){
		subList.push_back(buffer.top());
		buffer.pop();
		i++;
	}

	int data = func(subList,0,length-1);
	//
	char* value;
	value = transferChar(data);

	queue<char *> queueList;
	i=0;
	bracket = false;
	while(i<list.size()){
		if(i<first || i>(first+length+1)){
			queueList.push(list.at(i));
		}
		else if(!bracket){
			bracket = true;
			queueList.push(value);
		}
		i++;
	}
	list.clear();
	if(list.empty()){
		i=0;
		while(i<queueList.size()){
			list.push_back(queueList.front());
			queueList.pop();
		}
	}
	return list;
}

bool doseBracket(vector<char *> list){
	bool bracketExist = false;
	int i=0;
	while(i<list.size()){
		if(*list.at(i) == ')'){
			bracketExist = true;
			break;
		}
		i++;
	}
	return bracketExist;
}


int main(){
	
	const char* str ="(((1+22)*(12+1))-24/2)*(2+1)";;
	vector<char *> list;

	bool bracketIs = false;
	int i=0,j=0;
	char *ch;

	while(*(str+i)!='\0'){
		if(*(str+i) !=' '){
			if(*(str+i) =='+'||*(str+i) =='-'
				||*(str+i) =='*'||*(str+i) =='/'
				||*(str+i) =='('||*(str+i) ==')'){
				if(i!=0){
					j++;
					*(ch+j) ='\0';
				}
				j=0;

				bracketIs = true;
				ch = (char *)malloc(sizeof(char));
				*ch = *(str+i);

				list.push_back(ch);
				
			}
			else if(bracketIs){
				
				ch = new char();
				*(ch+j) = *(str+i);
				if(bracketIs)
					list.push_back(ch);
				j++;
				bracketIs = false;
			}
			else if(!bracketIs){
				if(i==0)
					ch = new char();
				*(ch+j) = *(str+i);
				j++;
				if(i==0)
					list.push_back(ch);
			}

		}
		i++;
	}
	
	while(doseBracket(list)){
		list = setList(list);
	}

	int value =0;
	value = func(list,0,list.size()-1);

	cout<<"value="<<value;

	return 1;
}

