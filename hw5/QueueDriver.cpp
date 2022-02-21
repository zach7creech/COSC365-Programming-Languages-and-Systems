/* Author: Zachery Creech
 * COSC365 Spring 2021
 * HW5: QueueDriver.cpp
 * This program reads in commands and strings from stdin to fill a generic circular queue
 * data structure. The queue is implemented as declared in the Queue.h file. 
 * 03/05/2021 */

#include "Queue.h"

int main()
{
	int n;
	string command, input;

	//get max number of elements and create a queue of that size
	cin >> n;

	Queue<string> *q = new Queue<string>(n);

	//read input word by word, execute specified command on each line
	
	while(cin >> command)
	{
		if(command == "enqueue")
		{
			cin >> input;
			try
			{
				q->enqueue(input);
			}
			catch(QueueOverflowException<string> qoe)
			{
				cerr << qoe.getMessage() << endl;	
			}
		}
		else if(command == "dequeue")
		{
			try
			{
				cout << "dequeue: " << q->dequeue() << endl;
			}
			catch(QueueEmptyException qee)
			{
				cerr << qee.getMessage() << endl;
			}
		}
		else if(command == "print")
		{
			cout << "queue contents" << endl;
			q->printQueue();
		}
	}

	delete q;

	return 0;
}
