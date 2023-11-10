#include <iostream>

using namespace std;

int main(){

	int *a = new int();

	*a = 9;

	int *b = new int();

	b=a;

	*a = 10;

	cout<<*a<<*b;

	return 1;
}