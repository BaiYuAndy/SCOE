const int defaultsize =20;

template <class T>
class Stack
{
	private:
		int top;
		T *elements;
		int MaxSize;
	public:
		Stack(int MaxSize=defaultsize);
		~Stack(void){ delete [] elements;}
		int push(const T& item);
		T pop(void);
		T getTop(void);
		void MakeEmpty(void){ top=-1;}
		bool isEmpty(void) const { return bool(top==-1);}
		bool isFull(void) const { return bool(top==MaxSize-1);}
};

template <class T>
Stack<T>::Stack(int s)
{
	MaxSize=s;
	elements=new T[MaxSize];
	top=-1;
}

template <class T>
int Stack<T>::push(const T& item)
{
	if (!isFull())
	{
		elements[++top]=item;
		return 0;
	}
	else return -1;
}

template <class T>
T Stack<T>::pop(void)
{
	if (!isEmpty()) return elements[top--];
	else return NULL;
}

template <class T>
T Stack<T>::getTop(void)
{
	if (!isEmpty()) return elements[top];
	else return NULL;
}