#include <iostream>
using namespace std;
#include "stack.h"

void main(void)
{
	Stack<char> bracket;
	char * data = new char[20];

	cout<<"please input the expression:"<<endl;
	cin>>data;

	for (char *p=data; *p; p++)
	{
		if (*p=='(') bracket.push(*p);
		else if (*p==')')
			{
				if (bracket.isEmpty()) 
				{
					cerr<<"error:È±×óÀ¨ºÅ!"<<endl;
					return;
				}
				else bracket.pop();
			}
	}

	if (!bracket.isEmpty()) cerr<<"error:È±ÓÒÀ¨ºÅ!"<<endl;
	else cout<<"right!"<<endl;
}