#include "Graph.h"


int main()
{
	
        FILE* fIn = NULL;
        int numVertices;
        int numEdges;
        int i = 0;
        int numSP = 0;
        Vertex fromVertex = 0;
        Vertex toVertex = 0;
        char buffer[ 100 ];
        Edge e;
        
	fIn = fopen("p4Input.txt","r");
	if( fIn == NULL)
        {
		return 1;
        }
         
        if(fgets( buffer, 100, fIn) != NULL)
        {
            sscanf( buffer, "%d", &numVertices);
        }
         
        Graph g = newGraph(numVertices);
        g->n = numVertices;
        

        if(fgets( buffer, 100, fIn) != NULL)
        {
            sscanf( buffer, "%d", &numEdges);
	}
        
        //printf("%d\n", numVertices);
	//printf("%d\n", numEdges);
        
        while (i < numEdges)
        {
            if ( fgets ( buffer, 100, fIn ) != NULL)
            {
                sscanf(buffer, "%d %d", &e.fromVertex, &e.toVertex);
            }
            
            addEdge(g, e);
            i++;
        }
        
         if(fgets( buffer, 100, fIn) != NULL)
        {
            sscanf( buffer, "%d", &numSP);
	}
        //printf("%d\n", numSP);
        //printGraph(g, numVertices);
        
        i=0;    
        while (i < numSP)
            
        {
            if ( fgets ( buffer, 100, fIn ) != NULL)
            {
                sscanf(buffer, "ShortestPath: %d %d", &e.fromVertex, &e.toVertex);
                shortestPath( g, e.fromVertex, e.toVertex);
            }
            //printf("%d %d\n", e.fromVertex, e.toVertex);
            i++;
        }
        
        
        freeGraph(g);
        fclose(fIn);
	return 0;
}


