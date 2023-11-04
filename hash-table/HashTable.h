#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

//Defining the maximum team name length.
#define MAX_NAME_LENGTH 50

//TRUE and FALSE constants
#define TRUE 1
#define FALSE 0


//Defining an Element to be the data for a team.
typedef struct
{
    char teamName[MAX_NAME_LENGTH];
    int wins;
    int losses;
} Element;

//Defining a HashTableEntry to contain an Element and an integer to manage chaining.
typedef struct
{
	Element key;
	int chainIndex;
} HashTableEntry;


//Defining the a struct for a Hash Table Implementation.
typedef struct
{
	int n;
	//The size of the array to store all the data.

	HashTableEntry *hashTable;
	//Pointer that we will use to dynamically allocate an array for our Hash Table.
	
} HashTableImp;


//Defining a HashTable to be a HashTableImp Pointer.
typedef HashTableImp *HashTable;



/*****FUNCTION PROTOTYPES**********/

//Malloc a new HashTableImp, malloc the hashTable to be an array of HashTableEntrys of size n, 
//initialize each iChainIndex to be -2 (indicating that the spot is empty), 
//and return a pointer to the HashTableImp.
HashTable newHashTable(int n);


//Free the HashTable h.
void freeHashTable(HashTable h);


//Given a string, convert it into an integer to be used in either
//the division method or the midsquare method.
int stringToInt(char *stringToConvert);


//Given a key value, use the division method to find a 
//valid index for hashTable.
int divisionMethod(int key, int n);


//Given a key value, use the midsquare method to find a 
//valid index for hashTable.
int midsquareMethod(int key, int n);


//Insert e into our HashTable h by using stringToInt to convert the team name
//into an integer and then passing that integer to one of the division or 
//midsquare method functions.  If this entry is not occupied, insert it there
//and change the corresponding iChainIndex to be -1.  If there is a collision,
//use open chaining to find an open location for e, and update the iChainIndex
//values accordingly.
void put(HashTable h, Element e);


// Return a pointer to the key struct contain the data that matches teamName
//if it exists. If it does not exist, return NULL.
Element* get(HashTable h, char *teamName);

