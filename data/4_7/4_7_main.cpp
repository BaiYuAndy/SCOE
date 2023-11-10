#include <iostream.h>
#include "LinkedList.h" 

struct Term
{
	double coeff;
	int power;
};

/*	另一种方法
double make(Term, double); 

void main (void)
{
	LinkedList<Term> multinomial;
	Term tmp;

	do
	{
		cout<<"Enter coeff: ";
		cin>>tmp.coeff;
		cout<<"Enter power: ";
		cin>>tmp.power;

		if (multinomial.Size()==0)
			multinomial.InsertAt(tmp);
		else
		{
			int pos=0;
			multinomial.SetPosition(pos);
			while ((tmp.power<multinomial.GetData().power) 
					&& (multinomial.GetPosition()!=multinomial.Size()-1))
			{
				pos++;
				multinomial.SetPosition(pos);
			}
			if (multinomial.GetPosition()!=multinomial.Size()-1)
				multinomial.InsertAt(tmp);
		    else
				multinomial.InsertAfter(tmp);
		}
	}
	while (tmp.power!=0);

	for (int i=0; i<=multinomial.Size()-1; i++)
	{
		multinomial.SetPosition(i);
		cout<<multinomial.GetData().coeff<<"X^"<<multinomial.GetData().power;
		if (i!=multinomial.Size()-1)
			cout<<"+";
	}
	cout<<endl;

	double x;
	do
	{
		double result=0;
		cout<<"Enter X:  ";
		cin>>x;

		for (int i=0; i<=multinomial.Size()-1; i++)
		{
			multinomial.SetPosition(i);
		    result+=make(multinomial.GetData(), x);
		}
		cout<<"Answer is:  "<<result<<"\n"<<endl;
	}
	while (x!=0);
}

double make(Term monomial, double x)
{
	double k=1;
	for (int i=1; i<=monomial.power; i++)
		k*=x;
	k*=monomial.coeff;
	return k;
}
*/

//熊老师要求的解法
const int MAXPower = 20;
void main (void)
{
	LinkedList<Term> multinomial;
	Term tmp;

	do
	{
		cout<<"Enter coeff: ";
		cin>>tmp.coeff;
		cout<<"Enter power: ";
		cin>>tmp.power;

		if (multinomial.Size()==0)
			multinomial.InsertAt(tmp);
		else
		{
			multinomial.SetPosition(0);
			while ((tmp.power<multinomial.GetData().power) 
					&& (multinomial.GetPosition()!=multinomial.Size()-1))
				multinomial.NextNode();
			if (multinomial.GetPosition()!=multinomial.Size()-1)
				multinomial.InsertAt(tmp);
		    else
				multinomial.InsertAfter(tmp);
		}
	}while (tmp.power!=0);

	for (int i=0; i<=multinomial.Size()-1; i++)
	{
		multinomial.SetPosition(i);
		cout<<multinomial.GetData().coeff<<"X^"<<multinomial.GetData().power;
		if (i!=multinomial.Size()-1)
			cout<<"+";
	}
	cout<<endl;

	double x;
	int temp;
	do
	{
		double result = 0;
		cout<<"Enter X:  ";
		cin>>x;
		
		multinomial.SetPosition(0);
		while(multinomial.GetPosition()!=multinomial.Size()-1)
		{
			result += multinomial.GetData().coeff;
			temp = multinomial.GetData().power;
			multinomial.NextNode();
			for (int i=0; i<temp-multinomial.GetData().power; i++)
				result *= x;
		}
		result +=  multinomial.GetData().coeff;
		cout<<"Answer is:  "<<result<<"\n"<<endl;
	}while (x!=0);
}
