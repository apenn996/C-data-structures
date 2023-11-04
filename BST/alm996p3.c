#include "BinarySearchTree.h"
#include <time.h>

int main()
{
	BinarySearchTree Tree = newBinarySearchTree();
	Queue line1 = newQueue();
	char inputString[30];
	int accountNum = 0;
	double accountBal = 0.0;
	Element e;
	NodeT* p;
	NodeLL* p2;
	double time1;
	double time2;
	clock_t t2;
	clock_t t1;

	FILE* fIn = NULL;
	fIn = fopen("largeInput.txt","r");
	if( fIn == NULL)
		return 1;

	printf("BEGINNING OF BINARY SEARCH TREE OUTPUT\n");
	t1 = clock();
	/* BINARY SEARCH TREE IMPLEMENTATION FOR LARGE INPUT*/    
	while( fscanf(fIn, "%s", inputString) != EOF ){

		if (strcmp(inputString,"CREATE")==0){

			fscanf(fIn, "%d", &accountNum);
			//printf("hello 1\n");
			e.accountNumber = accountNum;
			//printf("hello 2\n");
			insert(&(Tree->root),  e);
			//printf("hello 3\n");
		}
		if (strcmp(inputString,"SALE")==0){

			fscanf(fIn, "%d", &accountNum);
			fscanf(fIn, "%lf", &accountBal);
			p = search(Tree->root, accountNum);
			p->element.accountBalance = p->element.accountBalance + accountBal;  

		}
		if (strcmp(inputString,"PRINT")==0){

			fscanf(fIn, "%s", inputString);
			if (strcmp(inputString,"PREORDER")==0)
				printPreOrder(Tree->root);
			else if (strcmp(inputString,"INORDER")==0)
				printInOrder(Tree->root);

		}   
	}
	t1 = clock() - t1;
	time1 = ((double)t1)/CLOCKS_PER_SEC;
	rewind(fIn);

	printf("END OF BINARY SEARCH TREE OUTPUT\n\n");
	printf("\n\n");
	printf("BEGINNING OF SINGLY LINKED LIST OUTPUT\n");
	/* QUEUE IMPLEMENTATION FOR EXTRA CREDIT*/
	t2 = clock();    
	while( fscanf(fIn, "%s", inputString) != EOF ){

		if (strcmp(inputString,"CREATE")==0){

			fscanf(fIn, "%d", &accountNum);
			//printf("hello 1\n");
			e.accountNumber = accountNum;
			//printf("hello 2\n");
			enqueue(line1, e);
			//printf("hello 3\n");
		}
		if (strcmp(inputString,"SALE")==0){

			fscanf(fIn, "%d", &accountNum);
			fscanf(fIn, "%lf", &accountBal);
			p2 = searchQueue(line1->head, accountNum);
			p2->element.accountBalance = p2->element.accountBalance + accountBal;  

		}
		if (strcmp(inputString,"PRINT")==0){

			fscanf(fIn, "%s", inputString);
			if (strcmp(inputString,"PREORDER")==0)
				printQueue(line1->head);
			else if (strcmp(inputString,"INORDER")==0)
				printQueue(line1->head);

		}   
	}
	t2 = clock() - t2;
	time2 = ((double)t2)/CLOCKS_PER_SEC;
	
	printf("END OF SINGLY LINKED LIST OUTPUT\n\n");

	printf("The binary search tree implementation took a total of %.2lf seconds\n", time1);
	printf("The singly linked list implementation took a total of %.2lf seconds\n\n", time2);
	printf("The difference in the running times is %.2lf seconds\n\n", time2-time1);
	



	// printf("end of file\n");
	freeQueue(line1);
	freeBinarySearchTree(Tree);
	fclose(fIn);
	return 0;
}
