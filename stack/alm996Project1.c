#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

#define MAX_LINE_LENGTH 50


int convertToPostfix(char *infixString, char *postfixString);
int evaluatePostfix(char *postfixString);
// checks to see if there is a missing operand
int operand(char* infixString);


int main()
{
	FILE *inputFile;
	inputFile = fopen("p1Input.txt", "r");
	if(inputFile == NULL){

		perror("Error opening file");
		return -1;
	}


	//This string will hold the infix equations that are read from inputFile, one at a time.
	char infixString[MAX_LINE_LENGTH];


	//Use fgets to read the next line from the inputFile.
	//Store the line into infixString.
	//The while loop repeats until there are no more lines in the file.
	while(fgets(infixString, MAX_LINE_LENGTH, inputFile)!=NULL){

		//If the line is blank, skip it.
		if(infixString[0] == '\n')
			continue;

		
		//postfixString is a string to store the equation from szInfixString converted into postfix.
		char postfixString[MAX_LINE_LENGTH];
		//char temp[60]= "";
		// strcpy(temp,postfixString);
		//postfixString[0] = '\0';
		//Call the convertToPostfix function (that you are to implement below main).
		int returnMessage = convertToPostfix(infixString,postfixString);
		//printf("\n\n\n\n\n\n\n");


		//convertToPostfix should return an integer letting us know if the infix string was in a valid format.
		//If the format is valid (we returned 0), then we call the evalutaePostfix function (that you are to implement below), and print the result of the evalution.
		//If the format is not valid (we returned something other than 0), then we print the corresponding error message.
		switch(returnMessage)
		{

			case 0: //0 means the infix string had no errors.  Go ahead and evaluate the postfix string.
				printf("Postfix string: %s\n",postfixString);
				int result = evaluatePostfix(postfixString);
				printf("It evaluates to %d.\n",result);
				break;
			case 1:  //1 means the infix string is missing a left parenthesis.
				printf("WARNING: Missing left parenthesis.\n");
				break;
			case 2: //2 means the infix string is missing a right parenthesis.
				printf("WARNING: Missing right parenthesis.\n");
				break;
			case 3: // 3 means missing operator.
				printf("WARNING: Missing operator.\n");
				break;
			case 4: //4 means missing operand.
				printf("WARNING: Missing operand.\n");
				break;
			default:
				printf("WARNING: %d.\n", returnMessage);


		}


		printf("\n\n");
	}

	fclose(inputFile);

	return 0;
}


/*******
  int convertToPostfix(char *infixString, char *postfixString)

Input: 
infixString is a character array of length <= MAX_LINE_LENGTH that contains an equation in infix format.
postfixString is a currently empty character array of length <= MAX_LINE_LENGTH that we should fill with a postfix representation of infixString.

Output:
We return an integer based on any errors found in infixString.
If there are no errors, return 0.
If there is a missing (, return 1.
If there is a missing ), return 2.
If there is a missing operator, return 3 (for extra credit).
If there is a missing operand, return 4 (for extra credit).
 *********/
int convertToPostfix(char *infixString, char *postfixString)
{
	int i = 0;
	int p = 0;
	int size = 50;
	Stack s = newStack(size);
	Element e;
	int l;
	int r;
	int error4;

	printf("Current infixString: %s", infixString);
	while (infixString[i] != '\0')
	{


		error4 = operand(infixString);
		if(error4 == 4)
			return 4;


		if(infixString[i]<58 && infixString[i]>47)
		{
			postfixString[p] = infixString[i];
			p++;
		}

		if (infixString[i] == '(')
		{
			e.operation = '(';
			push(s, e);

			for (r=0; infixString[r]!='\0';   r++)
			{
				if (infixString[r] == ')')
					break;
				if (infixString[r+1] == '\0')
					return 2;
			}                                

		}
		else if(infixString[i] == ')')
		{
			while (topElement(s).operation != '(')
			{
				//printf(") working\n");
				e.operation = pop(s).operation;
				// printf("character : %c", e.operation);
				postfixString[p] = e.operation;
				//printf("other paren met, popping between");
				//pop and output operators from stack until we see a ( on stack , and pop the (
				p++;
				if (isEmpty(s) == 1)
				{
					//printf("error no left (' ( ') paren\n");
					return 1;
				} 

			}
			pop(s);// if no second paren give error
		}
		if ( infixString[i] == '*' || infixString[i]== '/' || infixString[i] ==  '+' || infixString[i] == '-' )
		{	
			if( infixString[i] == '*'){
				e.operation = '*';

				if ( isEmpty(s) == 1 || topElement(s).operation == '(')
				{
					push(s,e);
				}
				else if(topElement(s).operation == '*' || topElement(s).operation == '/'  )
				{
					if (s->count >= 2)
					{
						for(l=0; l<2; l++)
						{
							if(topElement(s).operation != '(')
							{
								postfixString[p] = pop(s).operation;
								p++;
							}
						}

						push(s,e);
					}
					else{
						postfixString[p] = pop(s).operation;
						p++;
						push(s,e);
					}
				}
				else if(topElement(s).operation == '+' || topElement(s).operation == '-'  )
				{
					push(s,e);
				}
			}
			else if( infixString[i] == '/')
			{
				e.operation = '/';

				if ( isEmpty(s) == 1 || topElement(s).operation == '(')
				{
					push(s,e);
				}
				else if(topElement(s).operation == '*' || topElement(s).operation == '/'  )
				{
					if (s->count >= 2)
					{
						for(l=0; l<2; l++)
						{
							if(topElement(s).operation != '(')
							{
								postfixString[p] = pop(s).operation;
								p++;
							}
						}
						push(s,e);
					}
					else{
						postfixString[p] = pop(s).operation;
						p++;
						push(s,e);
					}
				}
				else if(topElement(s).operation == '+' || topElement(s).operation == '-'  )
				{
					push(s,e);
				}
			}
			else if( infixString[i] == '+')
			{
				e.operation = '+';

				if ( isEmpty(s) == 1 || topElement(s).operation == '(')
				{
					push(s,e);
				}
				else  if(topElement(s).operation == '*' || topElement(s).operation == '/'  )
				{
					if (s->count >= 2)
					{
						for(l=0; l<2; l++)
						{
							if(topElement(s).operation != '(')
							{
								postfixString[p] = pop(s).operation;
								p++;
							}
						}
						push(s,e);
					}
					else{
						postfixString[p] = pop(s).operation;
						p++;
						push(s,e);
					}
				}
				else  if(topElement(s).operation == '+' || topElement(s).operation == '-'  )
				{
					if (s->count >= 2)
					{
						postfixString[p] = pop(s).operation;
						p++;

						push(s,e);
					}
					else{
						postfixString[p] = pop(s).operation;
						p++;
						push(s,e);
					}
				}
			}
			else if( infixString[i] == '-')
			{
				e.operation = '-';

				if ( isEmpty(s) == 1 || topElement(s).operation == '(')
				{
					push(s,e);
				}
				else  if(topElement(s).operation == '*' || topElement(s).operation == '/'  )
				{
					if (s->count >= 2)
					{
						for(l=0; l<2; l++)
						{
							if(topElement(s).operation != '(')
							{
								postfixString[p] = pop(s).operation;
								p++;
							}
						}
						push(s,e);
					}
					else{
						postfixString[p] = pop(s).operation;
						p++;
						push(s,e);
					}
				}
				else  if(topElement(s).operation == '+' || topElement(s).operation == '-'  )
				{
					if (s->count >= 2)
					{
						for(l=0; l<2; l++)
						{
							if(topElement(s).operation != '(')
							{
								postfixString[p] = pop(s).operation;
								p++;
							}
						}
						push(s,e);
					}
					else{
						postfixString[p] = pop(s).operation;
						p++;
						push(s,e);
					}
				}
			}

		}
		postfixString[p] = '\0';

		//printf("post string %s\n", postfixString);

		i++;
	}
	while(isEmpty(s) == 0){
		if(topElement(s).operation == '(')
			break;
		postfixString[p] = pop(s).operation;
		p++;
	}

	//printf("temp is: %s post ius: %s\n", temp, postfixString);
	postfixString[p] = '\0';
	// printf("%s", postfixString);

	freeStack(s);
	return 0;
}



/************
  evaluatePostfix(char *postfixString)

Input:
postfixString is a string of length <= MAX_LINE_LENGTH that contains an equation in postfix representation.
If your convertToPostfix() function is correct, this string should be in a valid postfix format.

Output:
Return an integer representing what the postfix equation evaluated to.
 ************/
int evaluatePostfix(char *postfixString)
{
	int i = 0;
	int numB=0;
	int numT=0;
	int result;

	Stack s = newStack(MAX_LINE_LENGTH);
	Element e;
	//printf("post string %s\n", postfixString);
	do{

		if (postfixString[i]<58 && postfixString[i]>47)
		{
			e.operand = postfixString[i] - '0';
			push(s,e);
		}
		else{
			e.operation = postfixString[i];
		}

		if ( postfixString[i] == '*' ||  postfixString[i]== '/' ||  postfixString[i] ==  '+' ||  postfixString[i] == '-' )
		{
			numT =  pop(s).operand;
			numB =  pop(s).operand;
			//printf("numB: %d numT: %d\n", numB, numT);
			e.operation = postfixString[i];
			// push(s, e);
			if( postfixString[i] == '*')
			{
				// printf("mult\n");
				e.operand =  numB * numT;
				push(s, e);
			}
			else if(postfixString[i] == '/')
			{//printf("div \n");
				e.operand =  numB / numT;
				push(s, e);
			}
			else if(postfixString[i] == '+')
			{//printf("add   \n");
				e.operand =  numB + numT;
				push(s, e);
			}
			else if(postfixString[i] == '-')
			{//printf("sub \n");
				e.operand =  numB - numT;
				push(s, e);
			}

		}

		i++;


	} while( postfixString[i]!='\0');
	//printf("post string is %s\n", postfixString);

	result = pop(s).operand;
	freeStack(s);
	//e.operand = 5;
	//push(s, e);
	return result;
}

int operand(char* infixString)
{
	int i =0;
	int z;
	int mOp;
	int num1 =0 ;
	int whileCount;
	int m;
	int allClear;
	while (infixString[i] != '\0')
	{
		mOp = 0;
		m=0;
		num1 = 0;
		if (infixString[i]<58 && infixString[i]>47)
		{
			z = i;
			// printf("z: %d i: %d\n", z, i);


			if(infixString[z+1] == '\0')
			{ 
				//  printf("last operand in string\n");

				while(infixString[z]!='\0')
				{
					//  printf("while 1 \n");



					if(infixString[z] == '+' || infixString[z] == '*' || infixString[z] == '/' || infixString[z] == '-' )
						mOp++;
					//printf("mOp: %d\n", mOp);
					m=z;
					while(infixString[m]>58 || infixString[m]<47 || infixString[m] == ' ' || infixString[i]<58 && infixString[i]>47)
					{
						// whileCount++;
						m--;
						if(infixString[m] == '+' || infixString[m] == '*' || infixString[m] == '/' || infixString[m] == '-' )
							mOp++;
						if (mOp >= 2 && num1<mOp){
							//  printf("returning error 2 - 2\n");
							return 4;}
						if(infixString[m]<58 && infixString[m]>47)
						{
							allClear = 1 ;
							// printf("all clear reached\n");
							break;
						}
						//if ( whileCount >= 50)
						//  return 4;

					}

					if(infixString[z]<58 && infixString[z]>47)
					{
						num1 = 1;
						if(mOp == 1){
							break;
							// printf("breaking mOp=1 - 1\n");
						}
						if(mOp >=2 ){
							// printf("returning error 4 - 1\n");
							return 4;
						}

					} 
					if(infixString[z] == '\0')
						break;
					if (allClear==1)
						break;
					z--;
				}   
			}
			else if(infixString[z+1] != '\0')
			{

				if(num1 == 0){
					// printf("entered num1 =0");
					while(infixString[m]>58 || infixString[m]<47 || infixString[m] == ' ' || infixString[i]<58 && infixString[i]>47)
					{
						// whileCount++;
						m--;
						if(infixString[m] == '+' || infixString[m] == '*' || infixString[m] == '/' || infixString[m] == '-' )
							mOp++;
						if (mOp >= 2 ){
							// printf("returning error 2 - 2\n");
							return 4;}
						if(infixString[m]<58 && infixString[m]>47)
						{
							allClear = 1 ;
							// printf("all clear reached\n");
							break;
						}
						//if ( whileCount >= 50)
						//  return 4;
						if ((infixString[m]>58 || infixString[m]<47 || infixString[m] == ' ' || infixString[i]<58 && infixString[i]>47) == 0)
							return 4;
					}
					mOp = 0;
					m=0;
					num1 =0;
				}


				// printf("not last operand in string\n");
				while(infixString[z]!='\0')
				{
					// printf(" z is : %d\n", z);
					// printf("while 2 \n");
					// printf("character is: %c\n", infixString[z]);
					if(infixString[z] == '+' || infixString[z] == '*' || infixString[z] == '/' || infixString[z] == '-' )
						mOp++;
					if(infixString[z]<58 && infixString[z]>47)
						num1 = num1+1;

					//printf("mOp: %d\n\n", mOp);
					// printf("num1: %d\n", num1);
					m=z;
					//printf("%d\n", num1);
					while( infixString[m]!='\0'){
						//printf(" 12 1 12 \n");
						//whileCount++;
						// printf("infix is %c\n", infixString[m]);
						m++;
						//  printf("mOp: %d\n", mOp);
						// printf("num1: %d\n", num1);
						if (infixString[m]=='\0' && num1<=mOp)
							return 4;
						if(infixString[m] == '+' || infixString[m] == '*' || infixString[m] == '/' || infixString[m] == '-' )
							mOp++;
						if (mOp >= 2 && num1<mOp){
							//printf("returning error 2 - 2\n");
							return 4;}
						if(infixString[m]<58 && infixString[m]>47)
						{
							allClear = 1 ;
							//printf("all clear reached\n");
							break;

						}
						//printf("right before while count check\n");
						// if ( whileCount >= 50)
						// return 4;
						//printf("right after while count check\n");
					}
					//printf("right after while count check 2\n");

					if(mOp >=2 )
					{

						//printf("returning error 4 - 2\n");
						return 4;
					}

					if(infixString[z] == '\0')
						break;
					if (allClear==1)
						break;
					z++;
				}// while loop   
			}

		}
		return 0;
	}
}
