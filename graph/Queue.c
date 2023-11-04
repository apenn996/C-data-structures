#include "Queue.h"
Queue newQueue()
{
	Queue list = (QueueImp*)malloc(sizeof(QueueImp));
	list->head = NULL;
	list->foot = NULL;
	return list;

}


//Free each node that remains in the Queue and then free q itself.
void freeQueue(Queue q)
{
	while ( q->head != NULL)
	{
            NodeLL* temp = q->head;
            q->head = q->head->next;
            free(temp);
		
	}
	free(q);
}


//Allocate a new node and store "value" as the Element in the node.  Return the address of the node.
NodeLL *allocateNode(Element value)
{
	NodeLL* newNode = NULL;
	newNode = (NodeLL*)malloc(sizeof(NodeLL));

	if(newNode == NULL)
		printf("Error allocating a new node\n");
	newNode->next = NULL;
	newNode->element = value;
	return newNode;

}


//Call allocateNode() to get a new node that contains "value" and append it to the "foot end" of the queue.  Make sure to consider "edge cases" (e.g., when the queue is currently empty).
void enqueue(Queue q, Element value)
{
	if ( isEmptyQueue(q) == TRUE){
		q->head = allocateNode(value);
		q->foot = q->head;
	}
	else{
		q->foot->next = allocateNode(value);
		q->foot = q->foot->next;
	}
}

void printQueue(NodeLL *p)
{
	if (p==NULL)
	{
		printf("empty\n");
		return;
	}
	printf("(%d) ", p->element);
	printQueue(p->next);
}
//Remove the node at the "head" end of the queue, and return the value of the element stored in this node through an element e that is passed by reference.
//Functionally return TRUE (1) if the dequeue was successful and return FALSE (0) if it was not successful (i.e., the queue was empty).
//Remember to consider any "edge cases" (e.g., when the queue becomes empty after this dequeue).
int dequeue(Queue q, Element *e)
{

	if (q->foot == NULL){
		//printf("the queue is already empty\n");
		////q->foot->element.shopperID = 0;
		////q->foot->element.numberOfItems = 0;
		return 0;
	}
	else if (q->head == q->foot){
		*e = q->head->element;
		q->head = NULL;
		q->foot = NULL;
		return 1;
	}
	else
	{
		NodeLL *temp = q->head;
		q->head = q->head->next;
		*e = temp->element;
		free(temp);
		return 1;
	}

}


//Return the value of the element stored in the first node of the queue without removing the node itself (similar to topElement() for Stacks).
//Return the value through e that is passed by reference, and return TRUE (1) if the call was successful and return FALSE (0) if it was not successful (i.e., the queue was empty).
int frontElement(Queue q, Element *e)
{
	if(isEmptyQueue(q)==TRUE)
		return FALSE;
	else 
	{
            *e = q->head->element;
		//q->head->element.shopperID = e->shopperID;
		//printf("%d\n", q->head->element.shopperID);
		return TRUE;
	}
}


//Return TRUE (1) if the queue is empty, otherwise return FALSE (0).
int isEmptyQueue(Queue q)
{
	if(q->head == NULL)
		return TRUE;
	else 
		return  FALSE;

}