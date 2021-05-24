#include<iostream>
#include<climits>
#include "../AdjacencyListGraph/graphAL.cpp"
#include "../IncidenceMatrixGraph/graphIM.cpp"
using namespace std;

int minimumVertex(int *dist, bool *visited, int n) 
{
	int min = -1;
              
	for(int i = 0; i < n; i++) 
	{
		if(!visited[i] && (min == -1 || dist[i] < dist[min]))      
		{ 
		    min = i;
		}
	}
	return min;
}

void dijkstraAL(GraphAL *graph, int src) // adjacency list
{
    int vertexes = graph->getNumOfVertexes(); // number of vertexes
    if(vertexes == 0){
        cout<<" Graph is empty!"<<endl;
        return;
    }
    int edges = graph->getNumOfEdges(); // number of edges
	int *distance = new int[vertexes]; // integer array to calculate minimum distance for each vertex                          
	bool *visited = new bool[vertexes]; // boolean array to mark visted/unvisted for each vertex
    int *previous = new int[vertexes]; // integer array of previous vertexes
	
	// set the vertexes with infinity distance and mark them unvisited 
	for(int i = 0; i < vertexes; i++)
	{
		distance[i] = INT_MAX;
		visited[i] = false;
        previous[i] = -1;
	}
	
	distance[src] = 0;   // source vertex distance is set to zero            
	
	for(int i = 0; i < vertexes; i++)                           
	{
		int min = minimumVertex(distance,visited, vertexes); // find minimum vertex
		visited[min] = true; // min with minimum distance included in visited

		for(Node *ver = graph->getList(min); ver; ver = ver->next)                  
		{
			// updating the minimum distance for the particular vertex
			if(!visited[ver->vertex] && (distance[ver->vertex] > distance[min] + ver->edge)){
                distance[ver->vertex] = distance[min] + ver->edge;
                previous[ver->vertex] = min;
            }
		}
	}
    cout<<endl<<" Results of the Dijkstra algorithm for adjacency list: "<<endl;
	cout<<" Vertex\tDistance from source\tPrevious vertex"<<endl;
	for(int i = 0; i < vertexes; i++) //printing             
	{ 
		cout<<" "<<i<<"\t\t"<<distance[i]<<"\t\t"<<previous[i]<<endl;
	}
    cout<<endl;

    delete [] visited;
    delete [] distance;
    delete [] previous;
}

void dijkstraIM(GraphIM *graph, int src) // incidence matrix 
{
    int vertexes = graph->getNumOfVertexes(); // number of vertexes
    if(vertexes == 0){
        cout<<" Graph is empty!"<<endl;
        return;
    }
    int edges = graph->getNumOfEdges(); // number of edges
	int *distance = new int[vertexes]; // integer array to calculate minimum distance for each vertex                          
	bool *visited = new bool[vertexes]; // boolean array to mark visted/unvisted for each vertex
    int *previous = new int[vertexes]; // integer array of previous vertexes
	
	// set the vertexes with infinity distance and mark them unvisited 
	for(int i = 0; i < vertexes; i++)
	{
		distance[i] = INT_MAX;
		visited[i] = false;
        previous[i] = -1;
	}
	
	distance[src] = 0;   // source vertex distance is set to zero            
	
	for(int i = 0; i < vertexes; i++)                           
	{
		int min = minimumVertex(distance,visited, vertexes); // find minimum vertex
		visited[min] = true; // min with minimum distance included in visited

		for(int j = 0; j < edges; j++)                  
		{
			// updating the minimum distance for the particular vertex
			if(graph->findElement(min, j) > 0 && !visited[graph->getEndingVertexOfEdge(j)] && distance[min] != INT_MAX){
                int dist = distance[min] + graph->findElement(min, j);
                if(dist < distance[graph->getEndingVertexOfEdge(j)]){
                    distance[graph->getEndingVertexOfEdge(j)] = dist;
                    previous[graph->getEndingVertexOfEdge(j)] = min;
                }
            }
		}
	}
    cout<<endl<<" Results of the Dijkstra algorithm for incidence matrix: "<<endl;
	cout<<" Vertex\tDistance from source\tPrevious vertex"<<endl;
	for(int i = 0; i < vertexes; i++) //printing             
	{ 
		cout<<" "<<i<<"\t\t"<<distance[i]<<"\t\t"<<previous[i]<<endl;
	}
    cout<<endl;

    delete [] visited;
    delete [] distance;
    delete [] previous;
}