#include "Stack.h"


Stack newStack(int maximumStackSize)
{
	Stack s = (StackImp*) malloc(sizeof(StackImp));
	s->maxSize = maximumStackSize;
	s->count = 0;
	s->stackElements = (Element*) malloc (sizeof(Element) * s->maxSize);
	return s;

}

void freeStack(Stack s)
{
    free(s);
   
    free(s->stackElements);

}

void push(Stack s, Element e)
{
    if (s->count >= s->maxSize)
    {
        printf("The stack is already full\n");
    }
    else
    {
        
        //printf("pushed %c\n ", e.operation);
       
        s->stackElements[s->count] = e;
        s->count= s->count + 1;
       // printf("%d",s->count);
    }
}

Element pop(Stack s)
{
    Element N;
    Element e = s->stackElements[s->count-1];
    s->stackElements[s->count-1] = N;
    if (isEmpty(s)==1)
    {
        //printf("The stack is already empty(pop)\n");
       
    }
    else
    {
       // printf("pop value ---%c---\n", e.operation);
        s->count = s->count - 1;
       return e;
       // return e;
    }
}

int isEmpty(Stack s)
{
    if (s->count == 0)
        return 1;
    else 
        return 0;
}

Element topElement(Stack s)
{
    if (isEmpty(s) == 1 )
    {
        printf("Error: the stack is empty\n");
        return s->stackElements[1];
    }
    else
    {
	//s->stackElements[0].operand = 5;
	//s->stackElements[0].operation = '-';
        //printf("top element count  = %d\n",s->count);
        //printf
	return s->stackElements[s->count-1];
    }




}



