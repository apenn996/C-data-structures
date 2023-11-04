#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>


//#define constant values
#define TRUE 1
#define FALSE 0


//typedef for the Element struct which constains a c string to store a URL in the BrowserList
typedef struct
{
	int accountNumber;
	double accountBalance;
} Element;


//Typedef for a node in the doubly linked list (has next and previous pointers).
typedef struct NodeT
{
	Element element;
	struct NodeT *left;
	struct NodeT *right;
} NodeT;

//Typedef for a binary search tree implementation.  
//Contains a pointer to the root node of the tree.
typedef struct
{
	NodeT *root;
} BinarySearchTreeImp;

typedef BinarySearchTreeImp *BinarySearchTree;


/*****Prototypes*******/

//Malloc a new BinarySearchTreeImp and return it's address.
BinarySearchTree newBinarySearchTree();


//Free the BinarySearchTree and any nodes that still exist in the tree.
void freeBinarySearchTree(BinarySearchTree tree);

void freeBinarySearchTreeNode(NodeT* p);

//Allocate a new node and store "value" as the Element in the node.  Return the address of the node.
NodeT *allocateNode(Element value);

//Recursive algorithm for searching for a node with key value equal to searchValue.  Return a pointer to the node if you find it or return NULL if it does not exist.
NodeT *search(NodeT *p, int searchValue);

//Create a node to store the given Element and add it as a leaf in the BinarySearchTree.  Do not worry about balancing the tree for this project.
//Return true if the insert worked successfully, and return false if the node already existed in the tree.
int insert(NodeT **pp, Element value);

//Recursivly print the key values of all nodes in the subtree rooted at p in increasing order.
void printInOrder(NodeT *p);

//Recursivly print the key values of all nodes in the subtree rooted at p according to a preorder traversal.
void printPreOrder(NodeT *p);







// QUEUE FUNCTIONS



//Typedef for a node a linked list.
typedef struct NodeLL
{
	Element element;
	struct NodeLL *next;
} NodeLL;

//Typedef for a queue implementation.  
//Contains a pointer to the first node in the list and the last node in the list (head and foot respectively).
typedef struct
{
	NodeLL *head;
	NodeLL *foot;
} QueueImp;

typedef QueueImp *Queue;


/*****Prototypes*******/

//Malloc a new QueueImp, set the head and foot pointers to NULL, and return it's address.
Queue newQueue();


//Free each node that remains in the Queue and then free q itself.
void freeQueue(Queue q);

//prints out Queue
void printQueue(NodeLL *p);

//Allocate a new node and store "value" as the Element in the node.  Return the address of the node.
NodeLL *allocateNodeQ(Element value);


//Call allocateNode() to get a new node that contains "value" and append it to the "foot end" of the queue.  Make sure to consider "edge cases" (e.g., when the queue is currently empty).
void enqueue(Queue q, Element value);

NodeLL *searchQueue(NodeLL *p, int searchValue);


//Remove the node at the "head" end of the queue, and return the value of the element stored in this node through an element e that is passed by reference.
//Functionally return TRUE (1) if the dequeue was successful and return FALSE (0) if it was not successful (i.e., the queue was empty).
//Remember to consider any "edge cases" (e.g., when the queue becomes empty after this dequeue).
int dequeue(Queue q, Element *e);


//Return the value of the element stored in the first node of the queue without removing the node itself (similar to topElement() for Stacks).
//Return the value through e that is passed by reference, and return TRUE (1) if the call was successful and return FALSE (0) if it was not successful (i.e., the queue was empty).
int frontElement(Queue q, Element *e);


//Return TRUE (1) if the queue is empty, otherwise return FALSE (0).
int isEmpty(Queue q);
