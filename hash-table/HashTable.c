#include "HashTable.h"

HashTable newHashTable(int n)
{
    int i;
    HashTable h = (HashTableImp*)malloc(sizeof(HashTableImp));
    h->hashTable = (HashTableEntry*)malloc(sizeof(HashTableEntry) * n);
    h->n = n;
    //printf("%d\n", h->n);
    for (i=0; i<n; i++){
        
    h->hashTable[i].chainIndex = -2;

    
    }
    return h;
}


//Free the HashTable h.
void freeHashTable(HashTable h)
{
    free(h->hashTable);
    free(h);
}


//Given a string, convert it into an integer to be used in either
//the division method or the midsquare method.
int stringToInt(char *stringToConvert)
{
    int i = 0;
    int hashSum = 0;
    for(i=0; i< (strlen(stringToConvert)); i++)
    {
        
        if (stringToConvert[i] != '\r' && stringToConvert[i] != '\n' &&  stringToConvert[i] != '\0')
            hashSum += stringToConvert[i];
        
    }

    return hashSum;
}


//Given a key value, use the division method to find a 
//valid index for hashTable.
int divisionMethod(int key, int n)
{
    return key % n;
}


//Given a key value, use the midsquare method to find a 
//valid index for hashTable.
int midsquareMethod(int key, int n)
{
    int square = key * key;
    return ((square / (n/10)) % n);
}


//Insert e into our HashTable h by using stringToInt to convert the team name
//into an integer and then passing that integer to one of the division or 
//midsquare method functions.  If this entry is not occupied, insert it there
//and change the corresponding iChainIndex to be -1.  If there is a collision,
//use open chaining to find an open location for e, and update the iChainIndex
//values accordingly.
void put(HashTable h, Element e)
{
    int stringSum = stringToInt(e.teamName);
    int index = midsquareMethod(stringSum, h->n);
    
    if(h->hashTable[index].chainIndex == -2)
    {
        h->hashTable[index].key = e;
        h->hashTable[index].chainIndex = -1;
    }
    else
    {
        int k = 7;
        int endofChain = index;
        while (h-> hashTable[endofChain].chainIndex !=-1)
        {
            endofChain = h->hashTable[endofChain].chainIndex;
        }
        int myNewIndex = endofChain +k;
        while( h->hashTable[myNewIndex].chainIndex != -2)
        {
            myNewIndex = (myNewIndex + k) % h->n;
        }
        h->hashTable[myNewIndex].key = e;
        h->hashTable[myNewIndex].chainIndex = -1;
        h->hashTable[endofChain].chainIndex = myNewIndex;
    }
}


// Return a pointer to the key struct contain the data that matches teamName
//if it exists. If it does not exist, return NULL.
Element* get(HashTable h, char *teamName)
{
   int stringSum = stringToInt(teamName);
  // printf("hello6\n");
    int index = midsquareMethod(stringSum, h->n);
   // printf("hello7\n");
    while(strcmp(h->hashTable[index].key.teamName, teamName ) != 0 && h->hashTable[index].chainIndex != -1){
        index = h->hashTable[index].chainIndex;
    }
    if(strcmp(h->hashTable[index].key.teamName, teamName ) == 0)
        return &(h->hashTable[index].key);
    else
        return NULL;
}