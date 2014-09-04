#ifndef LINKLIST_H
#define LINKLIST_H

template<class T>
class ListNode
{
public:
	/// <value>Object that this Container Holds</value>
	T Value;
	/// <value>Pointer to the next Node in the Link List</value>
	ListNode<T>* Next;	
	/// <value>Pointer to the previous Node in the Link List</value>
	ListNode<T>* Previous;
	/// <value>If the Node is empty</value>
	bool emptynode;	
	///<summary> 
	///Constructor
	///</summary>
	///<param name="To">Object</param>
	///<param name="To">Pointer to the next Node</param>
	///<param name="To">Pointer to the previous Node</param>
	inline ListNode(T value,ListNode<T>* next = 0, ListNode<T>* previous = 0)
	{
		Value = value;
		Next = next;
		emptynode = false;
		Previous = previous;
	}
	///<summary> 
	///Constructor for Empty Node
	///</summary>
	///<param name="To">Pointer to Next Node</param>
	inline ListNode(ListNode<T>* next)
	{
		Next = next;
		emptynode = true;
	}

	inline bool operator == (ListNode<T>& other)
	{
		return(Value == other.Value &&
				Next == other.Next &&
				Previous == other.Previous);
	}
	inline bool operator != (ListNode<T>& other)
	{
		return (Value != other.Value ||
				Next != other.Next ||
				Previous != other.Previous);
	}
	inline void operator = (ListNode<T>& other)
	{
		Value == other.Value;
		Next == other.Next;
		Previous == other.Previous;
	}
};
template<class T>
class LinkList
{
private:
	/// <value>Number of Elemets in a Link List</value>
	int mSize;	
	/// <value>Pointer to the First Node in the Link List</value>
	ListNode<T>* mHead;	
	/// <value>Pointer to the Last Node in the Link List</value>
	ListNode<T>* mTail;	
public:	
	///<summary> 
	///Constructor
	///</summary>
	LinkList();
	///<summary> 
	///Destructor
	///</summary>
	~LinkList();	
	///<summary> 
	///Get the First Node in the Link List
	///</summary>
	///<returns>Pointer to the First Node</returns>
	ListNode<T>* GetHead();
	///<summary> 
	///Get the Last Node in the Link List
	///</summary>
	///<returns>Pointer to the Last Node</returns>
	ListNode<T>* GetTail();
	///<summary> 
	///Get the Number of Nodes in the Link List
	///</summary>
	///<returns>Number of Nodes</returns>
	int GetSize();
	///<summary> 
	///Get the value of a Node at a position in the Link List
	///</summary>
	///<param name="index">Position of a Node in the Link List</param>
	///<returns>Value of Node</returns>
	T At(int index);
	///<summary> 
	///Creates a Node infront a position in the Link List
	///that contains the object passed
	///</summary>
	///<param name="value">Object we try to insert into the Link List</param>
	///<param name="index">Position of Node in the Link List</param>
	void Insert(T value, int index);
	///<summary> 
	///Creates a Node at the end of the Link List that contains the Object we passed
	///</summary>
	///<param name="value">Object we try to insert into the Link List</param>
	void Push_Back(T value);
	///<summary> 
	///Creates a Node at the front of the Link List that contains the Object we passed
	///</summary>
	///<param name="value">Object we try to insert into the Link List</param>
	void Push_Front(T value);
	///<summary> 
	///Removes Node at the end of the Link List
	///</summary>
	///<returns>Object we removed from Link List</returns>
	T Pop_Back();
	///<summary> 
	///Removes Node at the front of the Link List
	///</summary>
	///<returns>Object we removed from Link List</returns>
	T Pop_Front();
	///<summary> 
	///Removes Node in the Link List at a position in the Link List
	///</summary>
	///<param name="index">Position of Node in the Link List</param>
	///<returns>Object we removed from Link List</returns>
	T Remove(int index);
	///<summary> 
	///Clear all values in the Link List
	///</summary>
	void Clear();

	inline bool operator == (LinkList<T>& other)
	{
		return(mSize == other.mSize &&
				mHead == other.mHead &&
				mTail == other.mTail);
	}
	inline bool operator != (LinkList<T>& other)
	{
		return (mSize != other.mSize ||
				mHead != other.mHead ||
				mTail != other.mTail);
	}
	inline void operator = (LinkList<T>& other)
	{
		mSize = other.mSize;
		mHead = other.mHead;
		mTail = other.mTail;
	}
};
template<class T>
class ListIterator
{
private:
	/// <value>Pointer to the Link List we are Iterating Through</value>
	LinkList<T>* mList;
	/// <value>Pointer current Node in the Link List</value>
	ListNode<T>* mNode;	
	/// <value>Position in the Link List</value>
	int mIndex;	
public:
	///<summary> 
	///Constructor
	///</summary>
	///<param name="iterlist">Pointer to Link List</param>
	///<param name="begin">Start of Link List</param>
	ListIterator(LinkList<T>* iterlist, bool begin = true);
	///<summary> 
	///Destructor
	///</summary>
	~ListIterator();
	///<summary> 
	///Get an Iterator that points to the first Node in the Link List
	///</summary>
	///<returns>Iterator that points to the first Node</returns>
	ListIterator<T> Begin();
	///<summary> 
	///Get an Iterator that points to the last Node in the Link List
	///</summary>
	///<returns>Iterator that points to the last Node</returns>
	ListIterator<T> End();
	///<summary> 
	///Get the value of Node Iterator points too
	///</summary>
	///<returns>Value of Node</returns>
	T Value();
	///<summary> 
	///Check if the Iterator Points to a Node at  Index
	///</summary>
	///<param name="To">Position of a Node in Link List</param>
	///<returns>If at Index</returns>
	bool IsAt(int index);
	///<summary> 
	///Check if the Iterator points to the first Node in Link List
	///</summary>
	///<returns>If at First Node</returns>
	bool IsBegin();
	///<summary> 
	///Check if the Iterator points to the last Node in Link List
	///</summary>
	///<returns>If at last Node</returns>
	bool IsEnd();
	///<summary> 
	///Check if the Iterator is Null
	///</summary>
	///<returns>If Null</returns>
	bool IsNuLL();
	///<summary> 
	///Move to the Next Node in the Link List
	///</summary>
	void Next();
	///<summary> 
	///Move to the Previous Node in the Link List
	///</summary>
	void Previous();
	///<summary> 
	///Remove Node that this Iterator points to from the Link List and return the value of that Node. 
	///(You cant use the Iterator again unless you Increment the Node as a Fake Node is Created that Points back to the Link List)
	///</summary>
	///<returns>Value of Node</returns>
	T Remove();
	
	inline bool operator == (ListIterator<T>& other)
	{
		return(mList == other.mList &&
				mIndex == other.mIndex &&
				mNode == other.mNode);
	}
	inline bool operator != (ListIterator<T>& other)
	{
		return (mList != other.mList ||
				mIndex != other.mIndex ||
				mNode != other.mNode);
	}
	inline void operator = (ListIterator<T>& other)
	{
		mList = other.mList;
		mIndex = other.mIndex;
		mNode = other.mNode;
	}
	inline void operator ++ ()
	{
		Next();
	}
	inline void operator -- ()
	{
		Previous();
	}
};

template<class T>
LinkList<T>::LinkList()
	: mSize(0),	mHead(0), mTail(0)
{
}
template<class T>
LinkList<T>::~LinkList()
{
	int iter = 0;
	ListNode<T>* nextptr = mHead;	
	/**< Go through Every point in the Link List and delete them */
	while(iter != mSize)
	{
		ListNode<T>* ptr = nextptr;
		nextptr = nextptr->Next;
		delete ptr;
		iter++;
	}
}
template<class T>
void LinkList<T>::Clear()
{
	mSize = 0;
	mHead = 0;
	mTail = 0;
}
template<class T>
T LinkList<T>::At(int index)
{									
	/**< check that the index is in range of the link list */
	if(index > (mSize - 1) || index < 0)
	{
		return (mHead->Value);
	}
	int iter;
	ListNode<T>* ptr;
	/**< Check if the iter is closer to the start or the end and then do operation based on it */
	if(index <= (mSize / 2))
	{
		iter = 0;		
		ptr = mHead;	
		/**< while we arnt at the index go to the next node in the link list */
		while( iter != index)
		{
			ptr = ptr->Next;
			iter++;
		}
		return (ptr->Value);	
	}
	else
	{
		iter = mSize - 1;	
		ptr = mTail;	
		/**< While we arnt at the index go to the previous node in the link list */
		while( iter != index)
		{
			ptr = ptr->Previous;
			iter--;
		}
		return (ptr->Value);
	}
}
template<class T>
T LinkList<T>::Remove(int index)
{
	/**< Check that the index is in range of the link list */
	if(index > (mSize - 1) || index < 0)
	{
		return 0;
	}
	else if(mHead == mTail)
	{
		return Pop_Front();
	}
	int iter;
	ListNode<T>* ptr;
	/**< Check if the iter is closer to the start or the end and then do operation based on it */
	if(index <= (mSize / 2))
	{
		iter = 0;
		ptr = mHead;	
		/**< while we arnt at the index go to the next node in the link list */
		while( iter != index)
		{
			ptr = ptr->Next;
			iter++;
		}
	}
	else
	{
		iter = mSize - 1;
		ptr = mTail;		
		/**< While we arnt at the index go to the previous node in the link list */
		while( iter != index)
		{
			ptr = ptr->Previous;
			iter--;
		}
	}
	ListNode<T>* next = ptr->Next;			
	ListNode<T>* previous = ptr->Previous;
	T value;
	/**< If its tail node make the previous node point to 0 get the value of the node, delete it and return the value */
	if(next == 0)
	{
		previous->Next = 0;			
		mTail = previous;
		value = ptr->Value;
		delete ptr;
	}/**< If its Head node make the next node point to 0 get the value of the node, delete it and return the value */
	else if( previous == 0)		
	{
		next->Previous = 0;
		mHead = next;
		value = ptr->Value;
		delete ptr;
	}/**< make the node point around the node we are on, get the value of the node, delete it and return the value */
	else						
	{
		next->Previous = previous;
		previous->Next = next;
		value = ptr->Value;
		delete ptr;
	}
	mSize--;			
	return value;
}
template<class T>
int LinkList<T>::GetSize()
{
	return mSize;
}
template<class T>
void LinkList<T>::Insert(T value, int index)
{
	/**< check that the index is in range of the link list */
	if(index > mSize || index < 0)
	{
		return;
	}
	if(index == 0)
	{
		Push_Front(value);
		return;
	}
	if(index == GetSize())
	{
		Push_Back(value);
		return;
	}
	int iter;
	ListNode<T>* ptr;
	/**< Check if the iter is closer to the start or the end and then do operation based on it */
	if(index <= (mSize / 2))
	{
		iter = 0;		
		ptr = mHead;				
		/**< while we arnt at the index go to the next node in the link list */
		while( iter != index)
		{
			ptr = ptr->Next;
			iter++;
		}
	}
	else
	{
		iter = mSize - 1;		
		ptr = mTail;			
		/**< While we arnt at the index go to the previous node in the link list */
		while( iter != index)
		{
			ptr = ptr->Previous;
			iter--;
		}
	}
	/**< Incement size and create new node and add it to the chain of Nodes */
	mSize++;
	ListNode<T>* newNode = new ListNode<T>(value,ptr,ptr->Previous);
	ptr->Previous->Next = newNode;
	ptr->Previous = newNode;
}
template<class T>
void LinkList<T>::Push_Back(T value)
{
	mSize++;				
	/**< If empty list just creat a node and set head and tail to node */
	if(mHead == 0)
	{
		mTail = new ListNode<T>(value);
		mHead = mTail;
	}/**< Create new node set the tails next to the new node the set the tail to our new node */
	else		
	{
		ListNode<T>* newNode = new ListNode<T>(value,0,mTail);
		mTail->Next = newNode;
		mTail = newNode;
	}
}
template<class T>
void LinkList<T>::Push_Front(T value)
{
	mSize++;								
	/**< If empty list just creat a node and set head and tail to node */
	if(mHead == 0)
	{
		mHead = new ListNode<T>(value);
		mTail = mHead;
	}/**< Create new node set the head previous to the new node the set the head to our new node */
	else	
	{
		ListNode<T>* newNode = new ListNode<T>(value,mHead,0);
		mHead->Previous = newNode;
		mHead = newNode;
	}
}
template<class T>
T LinkList<T>::Pop_Back()
{
	ListNode<T>* ptr;
	T returner;
	/**< Check if the list is empty and return null if it is */
	if(mTail == 0)
	{
		return 0;
	}
	else if(mHead == mTail)
	{
		ptr = mTail;
		returner = ptr->Value;
		mTail = mHead = 0;
	}/**< Set pointer to our tail node, get the value of the node, get ride of link from previous node to this node then set the tail to previous node*/
	else		
	{
		ptr = mTail;
		returner = ptr->Value;
		mTail->Previous->Next = 0;
		mTail = ptr->Previous;
	}			
	/**< Decement size and delete the node */
	mSize--;	 	
	delete ptr;				
	return returner;
}
template<class T>
T LinkList<T>::Pop_Front()
{
	ListNode<T>* ptr;
	T returner;
	/**< Check if the list is empty and return null if it is */
	if(mHead == 0)
	{
		return 0;
	}
	else if(mHead == mTail)
	{
		ptr = mHead;
		returner = ptr->Value;
		mTail = mHead = 0;
	}/**< Set pointer to our head node, get the value of the node, get ride of link from next node to this node then set the head to previous node*/
	else		
	{
		ptr = mHead;
		returner = ptr->Value;
		mHead->Next->Previous = 0;
		mHead = ptr->Next;
	}
	/**< Decement size and delete the node */
	mSize--;	 		
	delete ptr;				
	return returner;
}
template<class T>
ListNode<T>* LinkList<T>::GetHead()
{
	return mHead;
}
template<class T>
ListNode<T>* LinkList<T>::GetTail()
{
	return mTail;
}


template<class T>
ListIterator<T>::ListIterator(LinkList<T>* iterlist, bool begin)
	: mList(iterlist)
{
	/**< If we want it at the first node then make the node point to the head pointer and the index 0 */
	if(begin)
	{
		mNode = mList->GetHead();
		mIndex = 0;
	}/**< If we want it at the last node then make the node point to the tail pointer and the index size minus 1 */
	else	
	{
		mNode = mList->GetTail();
		mIndex = mList->GetSize() - 1;
	}
}
template<class T>
ListIterator<T>::~ListIterator()
{
}
template<class T>
ListIterator<T> ListIterator<T>::Begin()
{
	return ListIterator<T>(mList);
}
template<class T>
ListIterator<T> ListIterator<T>::End()
{
	return ListIterator<T>(mList,false);
}
template<class T>
void ListIterator<T>::Next()
{
	/**< Check if Node is 0 */
	if(mNode == 0)
	{
		return;
	}
	/**< If it is a empty node then go to the next node then delete the empty node */
	if(mNode->emptynode)
	{
		ListNode<T>* emptynode = mNode;
		mNode = mNode->Next;
		delete emptynode;
	}/**< If isnt a empty node then go to next node and incrament the index */
	else	
	{
		mNode = mNode->Next;
		mIndex++;
	}
}
template<class T>
void ListIterator<T>::Previous()
{
	/**< Check if Node is 0 */
	if(mNode == 0)
	{
		return;
	}
	/**< If it is a empty node then go to the previous node then delete the empty node */
	if(mNode->emptynode)
	{
		ListNode<T>* emptynode = mNode;
		mNode = mNode->Previous;
		delete emptynode;
	}/**< If isnt a empty node then go to previous node and incrament the index */
	else	
	{
		mNode = mNode->Previous;
		mIndex--;
	}
}
template<class T>
T ListIterator<T>::Value()
{
	/**< Check if Node is 0 */
	if(mNode == 0)
	{
		return 0;
	}
	return mNode->Value;
}
template<class T>
T ListIterator<T>::Remove()
{
	/**< set the Node to an empty node that points to the next node in the link list */
	/**< remove the node from the link list at the index we are currently at and return the Value of the Node we remove*/
	mNode = new ListNode<T>(mNode->Next);;
	return mList->Remove(mIndex);								
}
template<class T>
bool ListIterator<T>::IsAt(int index)
{
	return(index == mIndex)
}
template<class T>
bool ListIterator<T>::IsBegin()
{
	return(mIndex == 0);
}
template<class T>
bool ListIterator<T>::IsEnd()
{
	return(mIndex == mList->GetSize() - 1);
}
template<class T>
bool ListIterator<T>::IsNuLL()
{
	return(mNode == 0);
}
#endif