/* Author: Zachery Creech
 * COSC365 Spring 2021
 * HW5: Queue.cpp
 * This is the implementation of the generic circular Queue data structure defined in
 * Queue.h.
 * 03/05/2021 */

#include <iostream>

//generic Queue data structure implemented with an ArrayList
//supports a few functions including enqueue, dequeue, and printQueue()
template<typename T>
Queue<T>::Queue(int maxCapacity)
{
	if(maxCapacity <= 0)
	{
		cerr << "Queue cannot be of size less than or equal to 0" << endl;
		return;
	}

	//instantiate the queue to size maxCapacity
	q = new T[maxCapacity];
	maxSize = maxCapacity;
	curSize = 0;
	front = -1;
	back = -1;
}

template<typename T>
Queue<T>::~Queue()
{
	delete[] q;
}

//add an object to the back of the queue
template<typename T>
void Queue<T>::enqueue(T val)
{
	if((front == 0 && back == maxSize - 1)	|| back == front - 1)
	{
		throw QueueOverflowException<T>(val);
	}
	else 
	{	
		curSize++;
		if(front == -1) //if the queue is empty
		{
			front = 0;
			back = 0;
			q[0] = val;
		}
		else if(front != 0 && back == maxSize - 1) //if the queue has room in the "front" but none in the back
		{
			back = 0;
			q[0] = val;
		}
		else //if the queue has space in the back
		{
			back++;
			q[back] = val;
		}
	}
}

//remove and return the first element in the queue
template<typename T>
T Queue<T>::dequeue()
{
	T item;
	
	if(front == -1)
	{
		throw QueueEmptyException();
	}
	else
	{
		//always get the element and update the size
		item = q[front];
		curSize--;
		if(front == back) //if there's only one thing in the queue
		{
			front = -1;
			back = -1;
		}
		else if(front == maxSize - 1) //if "front" is at the back, incrementing it puts it back to 0
			front = 0;
		else //normal movement of front, incremented by 1
			front++;

		return item;
	}
}

//print the contents of the queue from front to back
template<typename T>
void Queue<T>::printQueue()
{
	int i = front;
	int toPrint = curSize;

	while(toPrint > 0)
	{
		cout << q[i] << endl;
		i++;
		toPrint--;
		if(i == maxSize)
			i = 0;
	}
}
