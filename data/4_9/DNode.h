template<class T>
class DNode
{
	private:
		DNode<T> *next;
		DNode<T> *prev;
	public:
		T data;
		DNode(void);
		DNode(const T& item);
		~DNode(void);
		T GetData(void)const;
		void InsertBefore(DNode<T> *ptr);
		void InsertAfter(DNode<T> *ptr);
		DNode<T> *DeleteAt(void);
		DNode<T> *NextNode(void);
		DNode<T> *PrevNode(void);
};

template<class T>
DNode<T> :: DNode(void)
{
	next = prev = this;
}

template<class T>
DNode<T> :: DNode(const T& item)
{
	next = prev = this;
	data = item;
}

template<class T>
DNode<T> :: ~DNode(void)
{}

template<class T>
void DNode<T> :: InsertBefore(DNode<T> *ptr)
{
	ptr->next = this;
	ptr->prev = prev;
	prev->next = ptr;
	prev = ptr;
}

template<class T>
void DNode<T> :: InsertAfter(DNode<T> *ptr)
{
	ptr->next = next;
	ptr->prev = this;
	next->prev = ptr;
	next = ptr;
}

template<class T>
DNode<T> *DNode<T> :: DeleteAt(void)
{
	if (next == this) return NULL;
	next -> prev = prev;
	prev -> next = next;
	return this;
}

template<class T>
DNode<T> *DNode<T> :: PrevNode(void)
{
	return prev;
}

template<class T>
DNode<T> *DNode<T> :: NextNode(void)
{
	return next;
}

template<class T>
T DNode<T>::GetData(void)const
{
	return this->data;
}