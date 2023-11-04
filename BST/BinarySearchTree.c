#include "BinarySearchTree.h"

BinarySearchTree newBinarySearchTree(){

	BinarySearchTree Tree = (BinarySearchTreeImp*)malloc(sizeof(BinarySearchTreeImp));
	Tree->root = NULL;

	return Tree;
}

void freeBinarySearchTree(BinarySearchTree tree)
{
	freeBinarySearchTreeNode(tree->root);
	free(tree);
}

void freeBinarySearchTreeNode(NodeT* p)
{
	if (p == NULL)
		return;
	freeBinarySearchTreeNode(p->left);
	freeBinarySearchTreeNode(p->right);
	free(p);
}

NodeT *allocateNode(Element value){

	NodeT* newNode = NULL;
	newNode = (NodeT*)malloc(sizeof(NodeT));
	if (newNode == NULL)
		printf("error allocating node\n");
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->element = value;
	newNode->element.accountBalance = 0.0;
	return newNode;
}

NodeT *search(NodeT *p, int searchValue)
{
	if (p == NULL)
		return NULL;
	if (searchValue == p->element.accountNumber)
		return p;
	if ( searchValue < p->element.accountNumber)
		return search(p->left, searchValue);
	else
		return search(p->right, searchValue);
}

int insert(NodeT **pp, Element value){

	if (*pp == NULL)
	{
		*pp = allocateNode(value);
		return TRUE;

	}

	if(value.accountNumber == (*pp)->element.accountNumber){
		printf("An account with the number %d already exists\n", value.accountNumber);
		return FALSE;
	}
	if(value.accountNumber < (*pp)->element.accountNumber)
		return insert(&((*pp)->left ) , value);
	else
		return insert(&((*pp)->right) , value);
}

void printInOrder(NodeT *p){

	if (p == NULL)
		return;
	printInOrder(p->left);
	printf("%d %.2lf\n", p->element.accountNumber, p->element.accountBalance);
	printInOrder(p->right);


}

void printPreOrder(NodeT *p){

	if (p == NULL)
		return;
	printf("%d %.2lf\n", p->element.accountNumber, p->element.accountBalance);
	printPreOrder(p->left);
	printPreOrder(p->right);
}



// QUEUE FUNTIONS
Queue newQueue()
{
	Queue list = (QueueImp*)malloc(sizeof(QueueImp));
	list->head = NULL;
	list->foot = NULL;
	return list;

}


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


NodeLL *allocateNodeQ(Element value)
{
	NodeLL* newNode = NULL;
	newNode = (NodeLL*)malloc(sizeof(NodeLL));

	if(newNode == NULL)
		printf("Error allocating a new node\n");
	newNode->next = NULL;
	newNode->element = value;
	return newNode;

}


void enqueue(Queue q, Element value)
{
	if ( isEmpty(q) == TRUE){
		q->head = allocateNodeQ(value);
		q->foot = q->head;
	}
	else{
		q->foot->next = allocateNodeQ(value);
		q->foot = q->foot->next;
	}
}

void printQueue(NodeLL *p)
{
	if (p == NULL)
	{
		printf("\n");
		return;
	}
	printf("%d %.2lf \n", p->element.accountNumber, p->element.accountBalance);
	printQueue(p->next);
}

NodeLL *searchQueue(NodeLL *p, int searchValue)
{
	if (p == NULL)
	{
		//printf("\n");
		return;
	}
	if (searchValue == p->element.accountNumber)
		return p;
	if ( searchValue != p->element.accountNumber)
		return searchQueue(p->next, searchValue);

}


int isEmpty(Queue q)
{
	if(q->head == NULL)
		return TRUE;
	else 
		return  FALSE;

}
