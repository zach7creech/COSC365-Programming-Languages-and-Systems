/* Author: Zachery Creech
 * COSC365 Spring 2021
 * HW5: queue.c
 * This program implements the generic queue data structure as declared in queue.h using C's void *
 * mechanism. It is a cicular queue of a fixed size that is implemented using an array of void *'s.
 * 03/04/2021 */

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct voidQueue
{
	int size, front, back;
	void *c_array[];		
} *Queue;

//user can call this to dynamically allocate a generic Queue, handled internally as an array of void *'s
void *queue_new(int num_items)
{
	if(num_items <= 0)
	{
		fprintf(stderr, "Queue cannot be of size less than or equal to 0\n");
		return NULL;
	}
	
	Queue q = malloc(sizeof(struct voidQueue) + (sizeof(void *) * num_items));
	q->size = num_items;
	q->front = -1;
	q->back = -1;
	return q;
}

//add an object to the back of the queue
void queue_enqueue(void *q, void *item)
{
	Queue thisq = (Queue)q;
	
	if((thisq->front == 0 && thisq->back == thisq->size - 1) || thisq->back == thisq->front - 1)
		fprintf(stderr, "Queue is full\n");
	else if(thisq->front == -1) //if the queue is empty
	{
		thisq->front = 0;
		thisq->back = 0;
		thisq->c_array[0] = item;
	}
	else if(thisq->front != 0 && thisq->back == thisq->size - 1) //if the queue has room in the "front" but none in the back
	{
		thisq->back = 0;
		thisq->c_array[0] = item;
	}
	else //if the queue has space in the back
	{
		thisq->back++;
		thisq->c_array[thisq->back] = item;
	}
}

//remove and return the first element in the queue
void *queue_dequeue(void *q)
{
	Queue thisq = (Queue)q;
	void *item;
	
	if(thisq->front == -1)
	{
		fprintf(stderr, "Queue is empty\n");
		return NULL;
	}
	else 
	{	
		//always get the element and set its place to null
		item = thisq->c_array[thisq->front];
		thisq->c_array[thisq->front] = NULL;

		if(thisq->front == thisq->back) //if there's only one thing in the queue
		{
			thisq->front = -1;
			thisq->back = -1;
		}
		else if(thisq->front == thisq->size - 1) //if "front" is at the back, incrementing it puts it back to 0
			thisq->front = 0;
		else //normal movement of front, incremented by 1
			thisq->front++;
		
		return item;
	}
}

//boolean check if the queue is empty
int queue_isEmpty(void *q)
{
	if(((Queue)q)->front == -1)
		return 1;
	else
		return 0;
}
