#ifndef NODE_CLASS
#define NODE_CLASS

template <class T>
class Node
{
    private:
		// next is the address of the following node
        Node<T> *next;
    public:
    	// the data is public
        T data;
    
		// constructor
        Node (const T& item, Node<T>* ptrnext = NULL);
        
        // list modification methods
        void InsertAfter(Node<T> *p);
        Node<T> *DeleteAfter(void);

        Node<T>* DeleteNode(T data);
        
        // obtain the address of the next node
        Node<T> *NextNode(void) const;

		void Reverse(Node<T> *&p);
};

// constructor. initialize data and pointer members
template <class T>
Node<T>::Node(const T& item, Node<T>* ptrnext) : 
		 data(item), next(ptrnext)
{}
  
// return value of private member next
template <class T>
Node<T> *Node<T>::NextNode(void) const
{
    return next;
} 

// insert a node p after the current one
template <class T>
void Node<T>::InsertAfter(Node<T> *p)
{
	// p points to successor of the current node, 
	// and current node  points to p.
    p->next = next;
    next = p;
}

// delete the node following current and return its address
template <class T>
Node<T> *Node<T>::DeleteAfter(void)
{
	// save address of node to be deleted
    Node<T> *tempPtr = next;

	// if there isn't a successor, return NULL
    if (next == NULL)
        return NULL;
        
	// current node points to successor of tempPtr.
    next = tempPtr->next;
    
	// return the pointer to the unlinked node
    return tempPtr;
}

//set data as node value for delete node in list
template <typename T>
Node<T>* Node<T>::DeleteNode(T data){
	Node<T> *tempPtr = this;

	if(data == this->data){
	
		tempPtr = tempPtr->next;
		return tempPtr;
	}
	else{
		Node<T> *lastPtr = tempPtr->next;

		while(lastPtr->data !=data && lastPtr->next!=NULL){
			tempPtr = lastPtr;
			lastPtr = tempPtr->next;

		}
		if(lastPtr->next!=NULL){
			tempPtr->next = lastPtr->next;
		}
		else if(lastPtr->data == data){
			tempPtr->next = NULL;
		}
		delete lastPtr;

		return this;
	}

}

// reverse list as P
template<typename T>
void Node<T>::Reverse( Node<T> *&p)
{
    Node<T> *ptr1,*ptr2;
	
	ptr1 = p->next;
	p->next = NULL;

	while (ptr1)
	{
		ptr2 = ptr1 -> next;
		ptr1 -> next = p;
		p = ptr1;
		ptr1 = ptr2;
	}
	delete ptr1;
	delete ptr2;
}

#endif  // NODE_CLASS
