#include "Queue.h"
#include <math.h>

int main()
{
	Queue line1 = newQueue();
	Queue line2 = newQueue();
	Queue line3 = newQueue();
	int line1Sum = 0; // sum is also a 'wait time'
	int line2Sum = 0;
	int line3Sum = 0;
	int currentTime = 0;
	int customerCount = 0;
	int arriveTime;
	int timeDiff = 0;
	Element e;
	int x = 0;
	int array[200];
	int currentCustomerID1 = 0;
	int currentCustomerID2 = 0;
	int currentCustomerID3 = 0;
	int currentCustomerItems1 = 0;
	int currentCustomerItems2 = 0;
	int currentCustomerItems3 = 0;
	int line1finish = 0;
	int line2finish = 0;
	int line3finish = 0;
	int minusCount1 = 0;
	int minusCount2 = 0;
	int minusCount3 = 0;

	char buffer[ 100 ];
	FILE* fIn = NULL;
	fIn = fopen( "p2Input.txt", "r" );

	if ( fIn == NULL )
	{
		return 1;
	}

	while( fgets( buffer, 1000, fIn)!= NULL )
	{
		sscanf( buffer, "%d%d%d", &arriveTime, &e.shopperID, &e.numberOfItems );
		array[customerCount] = arriveTime;
		//printf("num %d is %d\n", customerCount, array[customerCount]);
		customerCount++;
	}
	rewind(fIn);
	//printf("customer count is %d\n", customerCount);
	while( x != customerCount)
	{
		//printf("x is %d\n", x);
		fgets( buffer, 1000, fIn);
		sscanf( buffer, "%d %d %d", &arriveTime, &e.shopperID, &e.numberOfItems );
		timeDiff = array[x] - currentTime;
		currentTime = arriveTime;
		// printf("time diff %d\n", timeDiff);
		//printf("THE CURRENT TIME IS:  %d\n", currentTime);

		if(line1Sum != 0)
		{

			line1Sum = line1Sum - timeDiff;
			currentCustomerItems1 -= timeDiff;
			line1->head->element.numberOfItems -= timeDiff;

		}
		if(line2Sum != 0)
		{
			line2Sum = line2Sum - timeDiff;
			currentCustomerItems2 -= timeDiff;
			line2->head->element.numberOfItems -= timeDiff;
		}
		if(line3Sum != 0)
		{
			line3Sum = line3Sum - timeDiff;
			currentCustomerItems3 -= timeDiff;
			// printf("current customer 3 items                             %d\n", currentCustomerItems3);
			line3->head->element.numberOfItems -= timeDiff;
		}

		if ( isEmpty(line1) == TRUE)
		{
			enqueue(line1, e);
			line1->foot->element.numberOfItems = line1->foot->element.numberOfItems -1;
			line1Sum = line1Sum + line1->foot->element.numberOfItems;
			currentCustomerID1 = line1->head->element.shopperID;
			currentCustomerItems1 = line1->head->element.numberOfItems;
		}
		else if ( isEmpty(line2) == TRUE )
		{
			enqueue(line2, e);
			line2->foot->element.numberOfItems = line2->foot->element.numberOfItems-1 ;
			line2Sum = line2Sum + line2->foot->element.numberOfItems;
			currentCustomerID2 = line2->head->element.shopperID;
			currentCustomerItems2 = line2->head->element.numberOfItems;
			//printf( "line 2 sum %d \n", line2Sum);
			//printf("customer 2 items : %d\n", currentCustomerItems2);
		}
		else if(isEmpty(line3) == TRUE)
		{
			enqueue(line3, e);
			line3->foot->element.numberOfItems = line3->foot->element.numberOfItems -1;
			line3Sum = line3Sum + line3->foot->element.numberOfItems;
			currentCustomerID3 = line3->head->element.shopperID;
			currentCustomerItems3 = line3->head->element.numberOfItems;
		}
		else if ( line1Sum <= line2Sum && line1Sum<= line3Sum  )
		{
			//printf("customer 1 items 1 : %d\n", currentCustomerItems1);
			enqueue(line1, e);
			line1->foot->element.numberOfItems = line1->foot->element.numberOfItems ;
			line1Sum = line1Sum + line1->foot->element.numberOfItems;
			currentCustomerID1 = line1->head->element.shopperID;
			currentCustomerItems1 = line1->head->element.numberOfItems;
			//printf("customer 1 items  2: %d\n", currentCustomerItems1);
			//printf("line1 head: %d foot: %d \n",line1->head->element.numberOfItems,  line1->foot->element.numberOfItems);
		}
		else if ( line2Sum <= line1Sum && line2Sum<= line3Sum )
		{
			enqueue(line2, e);
			line2->foot->element.numberOfItems = line2->foot->element.numberOfItems ;
			line2Sum = line2Sum + line2->foot->element.numberOfItems;
			currentCustomerID2 = line2->head->element.shopperID;
			currentCustomerItems2 = line2->head->element.numberOfItems;
			//printf( "line 2 sum %d \n", line2Sum);
			//printf("customer 2 items : %d\n", currentCustomerItems2);
		}
		else 
		{
			enqueue(line3, e);
			line3->foot->element.numberOfItems = line3->foot->element.numberOfItems ;
			line3Sum = line3Sum + line3->foot->element.numberOfItems;
			currentCustomerID3 = line3->head->element.shopperID;
			currentCustomerItems3 = line3->head->element.numberOfItems;
		}

		if(line1Sum == 0  && line1->head->element.numberOfItems == 0)
		{
			printf("Shopper %d has finished checking out of line 1 at time %d\n", currentCustomerID1, currentTime);
			dequeue(line1, &e);
		}
		if(x>=1)
		{
			if(line2Sum == 0  && line2->head->element.numberOfItems == 0 )
			{
				printf("Shopper %d has finished checking out of line 2 at time %d\n", currentCustomerID2, currentTime);
				dequeue(line2, &e);
			}
		}
		if(x>=2)
		{
			if(line3Sum == 0  && line3->head->element.numberOfItems == 0)
			{
				printf("Shopper %d has finished checking out of line 3 at time %d\n", currentCustomerID3, currentTime);
				dequeue(line3, &e);
			}
		}
		if(line1Sum != 0)
		{
			//printQueue(line1->head);
			if((line1->head->element.numberOfItems) == 0)
			{
				printf("Shopper %d has finished checking out of line 1 at time %d\n", currentCustomerID1, currentTime);
				dequeue(line1, &e);
			}
			if ( line1->head->element.numberOfItems < 0)
			{
				printf("Shopper %d has finished checking out of line 1 at time %d\n", currentCustomerID1, currentTime - abs(line1->head->element.numberOfItems - minusCount1));
				minusCount1 += 1;
				line1->head->element.numberOfItems = 0;
				dequeue(line1, &e);
			}
			currentCustomerItems1 = line1->head->element.numberOfItems;
		}
		if( line2Sum != 0)
		{
			//printQueue(line2->head);
			if ((line2->head->element.numberOfItems) == 0)
			{
				printf("Shopper %d has finished checking out of line 2 at time %d\n", currentCustomerID2, currentTime);
				dequeue(line2, &e);
			}
			if ( line2->head->element.numberOfItems < 0)
			{
				printf("Shopper %d has finished checking out of line 2 at time %d\n", currentCustomerID2, currentTime - abs(line2->head->element.numberOfItems - minusCount2));
				minusCount2 += 1;
				line2->head->element.numberOfItems = 0;
				dequeue(line2, &e);
			}
			currentCustomerItems2 = line2->head->element.numberOfItems;
		}
		if(line3Sum != 0)
		{
			//printQueue(line3->head);
			if ((line3->head->element.numberOfItems) == 0)
			{
				printf("Shopper %d has finished checking out of line 3 at time %d\n", currentCustomerID3, currentTime - minusCount3);
				dequeue(line3, &e);
			}
			if ( line3->head->element.numberOfItems < 0)
			{

				printf("Shopper %d has finished checking out of line 3 at time %d\n", currentCustomerID3, currentTime - abs(line3->head->element.numberOfItems) - minusCount3);
				minusCount3 += 1;
				line3->head->element.numberOfItems = 0;
				dequeue(line3, &e);

			}
			currentCustomerItems3 = line3->head->element.numberOfItems;
		}
		//printf("customer 3 items 3: %d\n", currentCustomerItems3);
		// printf( "line 1 sum %d \n", line1Sum);
		// printf( "line 2 sum %d \n", line2Sum);
		// printf( "line 3 sum %d \n", line3Sum);


		x++;

	}

	currentTime++;
	//line3Sum = line3Sum - 2;
	line1->head->element.numberOfItems = line1->head->element.numberOfItems -minusCount1;
	line2->head->element.numberOfItems = line2->head->element.numberOfItems -minusCount2;
	line3->head->element.numberOfItems = line3->head->element.numberOfItems -minusCount3;
	
	/* Second while loop to gradually decrement the remaining shopper's items*/
	while ( (line1Sum != 0 && line1finish != 10) || (line2Sum != 0 && line2finish != 10) || (line3Sum != 0 && line3finish != 10)) //isEmpty(line1) != TRUE && isEmpty(line2) != TRUE && isEmpty(line3) !=  TRUE
	{
		//printf( "line 2 sum %d \n", line2Sum);
		//printf("line 1 finish: %d\n",line1finish);
		if (line1->head == NULL)
			line1finish = 10; 

		if ( line1finish != 10)
		{
			if(line1Sum != 0)
			{
				line1Sum--;
				currentCustomerItems1--;
				line1->head->element.numberOfItems--;
			}
			if (line1Sum == 0 &&  line1->head->element.numberOfItems>0)
				while(line1->head->element.numberOfItems != 0){
					line1->head->element.numberOfItems--;
					currentTime++;
				}
			if (line1Sum == 0 &&  line1->head->element.numberOfItems == 0 )
			{

				printf("Shopper %d has finished checking out of line 1 at time %d\n", currentCustomerID1, currentTime);
				dequeue(line1, &e);
				// printf("here 1\n");
				line1finish = 10;
			}
			// printf("here 12\n");
		}

		if(line1finish != 10)
		{
			if(line1Sum != 0)
			{
				//printQueue(line1->head);
				if((line1->head->element.numberOfItems) == 0)
				{
					printf("Shopper %d has finished checking out of line 1 at time %d\n", currentCustomerID1, currentTime);
					dequeue(line1, &e);
					// printf("here 2\n");
				}
				if ( line1->head->element.numberOfItems < 0)
				{
					printf("Shopper %d has finished checking out of line  1 at time %d\n", currentCustomerID1, currentTime - abs(line1->head->element.numberOfItems));
					line1->head->element.numberOfItems = 0;
					dequeue(line1, &e);
					// printf("here 3\n");

				}
				currentCustomerID1 = line1->head->element.shopperID;
				currentCustomerItems1 = line1->head->element.numberOfItems;
			}
		}
		//printf("here 13\n");
		//line 2 finish
		if ( line2finish != 10)
		{
			if(line2Sum != 0)
			{
				line2Sum--;
				currentCustomerItems2--;
				line2->head->element.numberOfItems--;
			}
			if (line2Sum == 0 &&  line2->head->element.numberOfItems>0)
				while(line2->head->element.numberOfItems != 0){
					line2->head->element.numberOfItems--;
					//currentTime++;
				}
			if (line2Sum == 0 &&  line2->head->element.numberOfItems==0 )
			{

				printf("Shopper %d has finished checking out of line 2 at time %d\n", currentCustomerID2, currentTime);
				dequeue(line2, &e);
				line2finish = 10;
			}
		}

		if(line2finish!= 10)
		{
			if(line2Sum != 0)
			{
				//printQueue(line1->head);
				if((line2->head->element.numberOfItems) == 0)
				{
					printf("Shopper %d has finished checking out of line 2 at time %d\n", currentCustomerID2, currentTime);
					dequeue(line2, &e);
				}
				if ( line2->head->element.numberOfItems < 0)
				{
					printf("Shopper %d has finished checking out of line  2 at time %d\n", currentCustomerID2, currentTime - abs(line2->head->element.numberOfItems));
					line2->head->element.numberOfItems = 0;
					dequeue(line2, &e);

				}
				currentCustomerID2 = line2->head->element.shopperID;
				currentCustomerItems2 = line2->head->element.numberOfItems;
			}
		}

		//printf("here 14\n");
		if ( line3finish != 10)
		{
			if(line3Sum != 0)
			{
				line3Sum--;
				currentCustomerItems3--;
				line3->head->element.numberOfItems--;
			}
			if (line3Sum == 0 &&  line3->head->element.numberOfItems>0)
				while(line3->head->element.numberOfItems != 0)
				{
					line3->head->element.numberOfItems--;
					//currentTime++;
				}
			if (line3Sum == 0 &&  line3->head->element.numberOfItems==0 )
			{

				printf("Shopper %d has finished checking out of line 3 at time %d\n", currentCustomerID3, currentTime);
				dequeue(line3, &e);
				line3finish = 10;
			}
		}

		if(line3finish != 10)
		{
			if(line3Sum != 0)
			{
				//printQueue(line1->head);
				if((line3->head->element.numberOfItems) == 0)
				{
					printf("Shopper %d has finished checking out of line 3 at time %d\n", currentCustomerID3, currentTime);
					dequeue(line3, &e);
				}
				if ( line3->head->element.numberOfItems < 0)
				{
					printf("Shopper %d has finished checking out of line  3 at time %d\n", currentCustomerID3, currentTime - abs(line3->head->element.numberOfItems));
					line3->head->element.numberOfItems = 0;
					dequeue(line3, &e);

				}
				currentCustomerID3 = line3->head->element.shopperID;
				currentCustomerItems3 = line3->head->element.numberOfItems;
			}
		}


		//printQueue(line2->head);



		//printf("line 1 finish: %d\n",line1finish);
		//printf("line 2 finish: %d\n",line2finish);
		currentTime = currentTime + 1;
		// printf("current time %d\n", currentTime);
		// printf( "line 1 sum %d \n", line1Sum);
		//printf( "line 1 num items %d \n", line1->head->element.numberOfItems);
		// printf( "line 1 sum %d \n", line1Sum);
		// printf( "line 2 sum %d \n", line2Sum);
		// printf( "line 3 sum %d \n", line3Sum);
	}
	//printf("current time %d\n", currentTime);

	freeQueue(line1);
	freeQueue(line2);
	freeQueue(line3);
	fclose(fIn);
	return 0;
}
