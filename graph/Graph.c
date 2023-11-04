#include "Graph.h"


//Given the number of vertices of the graph, malloc the nxn adjacency matrix and initialize every edge to 0 (i.e. the edges aren't there initially).
//Return the address of the graph.
Graph newGraph(int n)
{
    Graph g = (GraphImp*)malloc(sizeof(GraphImp));;
    int i = 0;
    int j = 0;
    int k = 0;

   g->adjacencyM = (int**) malloc( n * sizeof(int*));
    for(i = 0; i<n; i++)
    {
        
       g->adjacencyM[i] = (int*) malloc ( n * sizeof(int));
    }
 
     for(j = 0; j < n; j++)
    {
        for(k = 0; k < n; k++)
        {
        g->adjacencyM[j][k] = 0;
        }
    }
    
    
    return g;
}

//Free the adjacency matrix and then the graph itself.
void freeGraph(Graph g)
{
    int i;
    for(i = 0; i<g->n; i++)
    {
        
       free(g->adjacencyM[i]);
    }
    free(g->adjacencyM);
    free(g);
}

//Add the edge e to the graph g.
void addEdge(Graph g, Edge e)
{
    g->adjacencyM[e.fromVertex][e.toVertex] = 1;
}

//Given graph g and vertex v, scan the adjacency matrix and return the first edge in g such that v is the "fromVertex" of the edge.
//Return NULL if there is no such edge.
Edge firstAdjacent(Graph g, Vertex v)
{
    int i;
    Edge e;
    for (i = 0; i < g->n; i++)
    {
        //printf("HELLOfor1\n");
        if( g->adjacencyM[v][i] == 1)
        {
            //printf("HELLOif1\n");
            e.fromVertex = v;
            e.toVertex = i;
            return e;
            
        }
    }
    //printf("-1 case in first adj\n");
    e.fromVertex = e.toVertex = -1;
    return e;
}

//Given graph g and vertex e, scan the adjacency matrix and return the next edge after e in g such that e.fromVertex is the "fromVertex" of the edge.
//Return NULL if there is no such edge.
Edge nextAdjacent(Graph g, Edge e)
{
    int i;
    for (i = e.toVertex + 1; i < g->n; i++)
    {
        if( g->adjacencyM[e.fromVertex][i] == 1 )
        {
            e.fromVertex = e.fromVertex;
            e.toVertex = i;
            return e;
            
        }
    }
    e.fromVertex = e.toVertex = -1;
    return e;
}

//Print the sequence of vertices on a shortest path in g starting from start and ending at destination.  
//A shortest path should be computed using the Breadth First Search (BFS) algorithm that maintains the parents of each vertex in the shortest path tree as defined in class.  
//BFS can be implemented directly in this function, or you may create a new function for BFS.
void shortestPath(Graph g, Vertex start, Vertex destination)
{
    int i;
    int visited[g->n];
    int parent[g->n];
    Vertex current;
    Edge e;
    
    for(i = 0; i < g->n; i++)
        {
        visited[i] = 0;
        parent[i] = -1;
        }
    
    //printf("HELLO1\n");
    Queue q = newQueue();
    enqueue(q, start);
    visited[start] = 1;
    //printQueue(q->head);
    while ( dequeue(q, &current))
    {
        
        
        
        for ( e = firstAdjacent(g, current); e.toVertex != -1; e = nextAdjacent(g,e))
        {
           // printf("HELLO3\n");
            Vertex temp = e.toVertex;
            //printf("%d\n", e.toVertex);
            if ( visited[temp] == 0)
            {
                //printf("HELLOsdasd\n");
                enqueue(q, temp);
                visited[temp] = 1;
                parent[temp] = current;
            
            }
        }
    }
    
    /*for(i = 0; i < g->n; i++)
        {
        printf("%d ",visited[i] );
        }
         printf("\n");
        for(i = 0; i < g->n; i++)
        {
        printf("%d ",parent[i] );
        }
        //printf("HELLO2\n");
        printQueue(q->head); */
        
    Stack mystack = newStack(g->n);
    current = destination;
    while ( current != -1)
    {
       // printf("HELLO4\n");
        push(mystack, current);
        current = parent[current];
    }
    printStack(mystack, start, destination);
}

void printGraph(Graph g, int n)
{
    int j=0;
    int  k=0;
    for(j = 0; j < n; j++)
    {
        for(k = 0; k < n; k++)
        {
        printf("%d ", g->adjacencyM[j][k]);
        }
        printf("\n");
    }  
}