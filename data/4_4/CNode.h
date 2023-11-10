template<class T>
class CNode
{
	private:
		CNode<T> *next;
	public:
		T data;
		CNode(void);
		CNode(const T& item);
		~CNode(void);
		void InsertAfter(CNode<T> *ptr);
		CNode<T> *DeleteAfter(void);
		CNode<T> *NextNode(void);
};

template<class T>
CNode<T> :: CNode(void)
{
	next = this;
}

template<class T>
CNode<T> :: CNode(const T& item)
{
	next = this;
	data = item;
}

template<class T>
CNode<T> :: ~CNode(void)
{}

template<class T>
void CNode<T> :: InsertAfter(CNode<T> *ptr)
{
	ptr->next = next;
	next = ptr;
}

template<class T>
CNode<T> *CNode<T> :: DeleteAfter(void)
{
	CNode<T> *tmpPtr;
	if (next == this) return NULL;
	tmpPtr = next;
	next = next -> next;
	return tmpPtr;
}

template<class T>
CNode<T> *CNode<T> :: NextNode(void)
{
	return next;
}