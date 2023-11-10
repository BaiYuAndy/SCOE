#include "3_4.h"
#include <iostream>

using namespace std;

template <class T>
ostream& operator<< ( ostream& cout, LinearList<T> &l)
{
	int n = l.ListLength();
	
	for ( int i=0; i<n; i++)
	{
		T x = l.getElem(i);
		cout<<x<<"\t";
		
	}

	cout << endl;
	return cout;
}

int main( void )
{
	LinearList<char> list;
	char ch;

	cout<<"please input data * mean end input: "<<endl;
	for ( int i=0;;i++)
	{
		cin>>ch;
		if (ch == '*') break;
		else list.insertElem( ch, i);
	}
	
	list.reverseList();
	cout<<list;
	
	
	/*LinearList<int> list;
	int data[10] = {9,3,4,1,2,6,7,5,8,0};
	list.assgin(data,10);
	cout<<list;
	
	int temp =11;
	list.insertElem(temp,0);
	cout<<list;

	temp =15;
	list.insertElem(temp,11);
	cout<<list;
	
	list.reverseList();
	cout<<list;*/

	return 0;
}

