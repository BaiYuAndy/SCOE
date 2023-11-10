#include "linkedlist.h"

template <class T>
class LinkedSet: public LinkedList<T>
{
	public:
		int Find( T& );
};

template <class T>
int LinkedSet<T>::Find(T& item)
{
	for (int i=0; i<Size(); i++)
	{
		SetPosition(i);
		if (GetData()==item) return i;
	}
	return -1;
}

template <class T>
LinkedSet<T> *Union(LinkedSet<T> &x, LinkedSet<T> &y)
{
	static LinkedSet<T> tmp;
	int n = x.Size();
	int m = y.Size();

	for (int i=0; i<n; i++)
	{
		x.SetPosition(i);
		T a = x.GetData();
		tmp.InsertAfter(a);
	}

	for ( i=0; i<m; i++)
	{
		y.SetPosition(i);
		T a = y.GetData();
		int k = x.Find(a);
		if (k==-1)
		{	
			tmp.SetPosition(x.Size()-1);
			tmp.InsertAfter(a);
		}
	}

	return &tmp;
}

template <class T>
LinkedSet<T> *Intersection(LinkedSet<T> &x, LinkedSet<T> &y)
{
	LinkedSet<T> *tmp = new LinkedSet<T>;
	int n = x.Size();
	int m = y.Size();

	for (int i=0; i<m; i++)
	{
		y.SetPosition(i);
		T a = y.GetData();
		int k = x.Find(a);
		if (k!=-1)
		{	
			tmp->SetPosition(x.Size()-1);
			tmp->InsertAfter(a);
		}
	}

	return tmp;
}