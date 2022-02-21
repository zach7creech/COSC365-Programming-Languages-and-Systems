/* Author: Zachery Creech
 * COSC365 Spring 2021
 * HW5: Queue.h
 * Header file for Queue data structure. Also contains the implementations of
 * exception classes that handle queue overflow and underflow.
 * 03/05/2021 */

#include <string>

using namespace std;

template<typename T>
class Queue
{
	public:
		Queue(int maxCapacity);
		~Queue();
		void enqueue(T val);
		T dequeue();
		void printQueue();
	protected:
		int maxSize, curSize, front, back;
		T *q;
};

template<typename T>
class QueueOverflowException
{
	public:
		QueueOverflowException(T item) { this->item = item; }
		string getMessage()
		{
			return "queue full: cannot enqueue " + item;
		}
	private:
		T item;
};

class QueueEmptyException
{
	public:
		string getMessage()
		{
			return "queue empty: cannot dequeue";
		}
};

#include "Queue.cpp"
