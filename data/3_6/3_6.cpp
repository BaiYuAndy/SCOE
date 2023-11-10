#include <iostream>
using namespace std;

#include "stack.h"

void main( void )
{
	char *data = new char[20];
	Stack<char> sptr;

	cout<<"please input the expression"<<endl;
	cin>>data;

	int i=0;
	while (1)
	{
		switch (data[i])
		{
		    case '+':
		    case '-':
					while ((! sptr.isEmpty()) && (sptr.getTop() != '('))
					{
				      cout << sptr.getTop()<<" ";
				      sptr.pop();
			   	    }
				    sptr.push(data[i]);
					break;
		    case '*':
		    case '/':
				    if ((sptr.getTop()=='*') || (sptr.getTop()=='/')) 
					{
						cout << sptr.getTop()<<" ";
						sptr.pop();
					}
					sptr.push(data[i]);
				    break;
		    case '(':
					sptr.push(data[i]);
					break;
		    case ')':
					while (sptr.getTop() != '(' )
					{
						cout << sptr.getTop()<<" ";
						sptr.pop();
					}
					sptr.pop();
					break;
			case '\0':
					while (!sptr.isEmpty())
					{
						cout << sptr.getTop()<<" ";
						sptr.pop();
					}
					cout<<endl;
					exit(1);
			default:
                    cout<< data[i] <<" ";
					break;
		}
		i++;
	}
}