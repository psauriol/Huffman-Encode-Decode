#include <iostream>
#include <cstddef>
#include <new>
using namespace std;


template<class ItemType>
struct Qnode
{
	ItemType item;
	int priorityNum;
	Qnode<ItemType>* Qnext;
};

template<class ItemType>
class Queue
{
public:
	Queue();
	//Pre-Condition: 
	//Function: Constructs the Queue
	//Post-Condition: Queue and components are initialize

	~Queue();
	//Pre-Condition: Queue is initialized
	//Function: Deconstructs Queue
	//Post-Condition: Queue is deconstructed

	Queue(const Queue &acopy);
	//Pre-Condition: Queue has something to copy
	//Function: Copies the Queue
	//Post-Condition: the Queue is copied

	void operator = (const Queue &acopy);
	//Pre-Condition: Queue has something to set = to
	//Function: Sets Queue equal to another Queue
	//Post-Condition: Queue is equal to another 

	bool IsEmpty();
	//Pre-Condition: Queue is intialized
	//Function: Returns true if nothing is in the Queue
	//Post-Condition: returns bool true if Queue is empty

	void MakeEmpty();
	//Pre-Condition: Queue is initialized
	//Function: removes all nodes from the Queue
	//Post-Condition: Queue is empty

	bool IsFull();
	//Pre-Condition: Queue is initialized
	//Function: returns true if Queue is full
	//Post-Condition: returns true is Queue is full

	void EnQueue(ItemType item, int priorityNum);
	//Pre-Condition: Queue is initialzed
	//Function: Adds a node to the Queue
	//Post-Condition: Queue has one more node

	void DeQueue(ItemType& item);
	//Pre-Condition: Queue is initialized
	//Function: removes a node from the Queue
	//Post-Condition: Queue has one less node

	unsigned int LengthIs() const;
	//Pre-Condition: Queue is initialized
	//Function: returns the length of the Queue
	//Post-Condition: length variable is returned

private:
	unsigned int Qsize;
	Qnode<ItemType>* Qfront;//end
	Qnode<ItemType>* Qrear;//start
	
};

template<class ItemType>
Queue<ItemType>::Queue()
{
	Qrear = NULL;
	Qfront = NULL;
	Qsize = 0;
}

template<class ItemType>
Queue<ItemType>::~Queue()
{
	MakeEmpty();
}

template<class ItemType>
Queue<ItemType>::Queue(const Queue& acopy)
{

}

template<class ItemType>
void Queue<ItemType>::operator = (const Queue& acopy)
{

}

template<class ItemType>
bool Queue<ItemType>::IsEmpty()
{
	return(Qsize == 0);
}

template<class ItemType>
void Queue<ItemType>::MakeEmpty()
{
	Qnode<ItemType>* temp;
	while(Qfront != NULL)
	{
		temp = Qfront;
		Qfront = Qfront->Qnext;
		delete [] temp;
	}
	Qrear = NULL;
}

template<class ItemType>
bool Queue<ItemType>::IsFull()
{
	//Qnode<ItemType>* temp = new Qnode<ItemType>;
	//if( temp == NULL)
	//{
	//	return true;
	//}
	//else
	//{
	//	delete temp;
	//	return false;
	//}
	Qnode<ItemType>* temp;
	try
	{
		temp = new Qnode<ItemType>;
		return(false);
	}
	catch(bad_alloc exception)
	{
		return(true);
	}
	delete [] temp;
}

template<class ItemType>
void Queue<ItemType>::EnQueue(ItemType item, int priorityNum)
{
	if(!IsFull())
	{
		Qnode<ItemType>* newQnode = new Qnode<ItemType>;
		newQnode->item = item;
		newQnode->priorityNum = priorityNum;
		newQnode->Qnext = NULL;

		if(IsEmpty())
		{
			Qfront = newQnode;
			Qrear = newQnode;
		}
		else
		{
			Qnode<ItemType>* tPtr = Qfront;
			Qnode<ItemType>* trailPtr;
			while(tPtr != NULL && newQnode->priorityNum >= tPtr->priorityNum)
			{//keep moving bakc until everythign wiht higher(lower number) priority is in front of it
				trailPtr = tPtr;
				tPtr = tPtr->Qnext;

			}

			if(tPtr == NULL)
			{
				Qrear->Qnext = newQnode;
				Qrear = newQnode;
			}
			else
			{

				newQnode->Qnext = tPtr;
				if(tPtr == Qfront)
				{
					Qfront = newQnode;
				}
				else
				{
					trailPtr->Qnext = newQnode;
				}
			}
		}
		Qsize++;
	}
}

template<class ItemType>
void Queue<ItemType>::DeQueue(ItemType& item)
{
	if(!IsEmpty())
	{
		Qnode<ItemType>* temp;
		temp = Qfront;
		Qfront = Qfront->Qnext;
		if(Qfront == NULL)
		{
			Qrear = NULL;
		}
		item = temp->item;
		delete temp;
		Qsize--;
	}
}

template<class ItemType>
unsigned int Queue<ItemType>::LengthIs() const
{
	return(Qsize);
}