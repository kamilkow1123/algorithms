#include<iostream>
#include<climits>
#include "../AdjacencyListGraph/graphAL.cpp"
#include "../IncidenceMatrixGraph/graphIM.cpp"
using namespace std;

int minimumVertex(int *dist, bool *visited, int n){ //return the minimum vertex in the graph
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

int **dijkstraAL(GraphAL *graph, int src) //adjacency list
{
    int vertexes = graph->getNumOfVertexes(); //number of vertexes
    if(vertexes == 0){
        cout<<" Graph is empty!"<<endl;
        return nullptr;
    }
    int edges = graph->getNumOfEdges(); //number of edges
	int *distance = new int[vertexes]; //integer array to calculate minimum distance for each vertex
	bool *visited = new bool[vertexes]; //boolean array to mark visted/unvisted for each vertex
    int *previous = new int[vertexes]; //integer array of previous vertexes
    int **results = new int*[vertexes]; //array for results

	//set the vertexes with infinity distance and mark them unvisited
	for(int i = 0; i < vertexes; i++)
	{
		distance[i] = INT_MAX;
		visited[i] = false;
        previous[i] = -1;
        results[i] = new int[2];
	}

	distance[src] = 0;   //source vertex distance is set to zero

	for(int i = 0; i < vertexes; i++)
	{
		int min = minimumVertex(distance,visited, vertexes); //find minimum vertex
		visited[min] = true; //min with minimum distance included in visited

		for(Node *ver = graph->getList(min); ver; ver = ver->next)
		{
			//updating the minimum distance for the particular vertex
			if(!visited[ver->vertex] && (distance[ver->vertex] > distance[min] + ver->edge)){
                distance[ver->vertex] = distance[min] + ver->edge;
                previous[ver->vertex] = min;
            }
		}
	}

    for(int i = 0; i < vertexes; i++) //filling the results
    {
        if(distance[i] > INT_MAX/2 || distance[i] < -INT_MAX/2){
            results[i][0] = -2; //no path
            results[i][1] = -2; //no path
        }
        else{
            results[i][0] = distance[i];
            results[i][1] = previous[i];
        }
    }

    delete [] visited;
    delete [] distance;
    delete [] previous;

    return results;
}

int **dijkstraIM(GraphIM *graph, int src) //incidence matrix
{
    int vertexes = graph->getNumOfVertexes(); //number of vertexes
    if(vertexes == 0){
        cout<<" Graph is empty!"<<endl;
        return nullptr;
    }
    int edges = graph->getNumOfEdges(); //number of edges
	int *distance = new int[vertexes]; //integer array to calculate minimum distance for each vertex
	bool *visited = new bool[vertexes]; //boolean array to mark visted/unvisted for each vertex
    int *previous = new int[vertexes]; //integer array of previous vertexes
    int **results = new int*[vertexes]; //array for results

	//set the vertexes with infinity distance and mark them unvisited
	for(int i = 0; i < vertexes; i++)
	{
		distance[i] = INT_MAX;
		visited[i] = false;
        previous[i] = -1;
        results[i] = new int[2];
	}

	distance[src] = 0;   //source vertex distance is set to zero
	for(int i = 0; i < vertexes; i++)
	{
		int min = minimumVertex(distance,visited, vertexes); //find minimum vertex
		visited[min] = true; //min with minimum distance included in visited

		for(int j = 0; j < edges; j++)
		{
			//updating the minimum distance for the particular vertex
			if(graph->findElement(min, j) > 0 && !visited[graph->getEndingVertexOfEdge(j)] && distance[min] != INT_MAX){
                int dist = distance[min] + graph->findElement(min, j);
                if(dist < distance[graph->getEndingVertexOfEdge(j)]){
                    distance[graph->getEndingVertexOfEdge(j)] = dist;
                    previous[graph->getEndingVertexOfEdge(j)] = min;
                }
            }
		}
	}

    for(int i = 0; i < vertexes; i++) //filling the results
    {
        if(distance[i] > INT_MAX/2 || distance[i] < -INT_MAX/2){
            results[i][0] = -2; //no path
            results[i][1] = -2; //no path
        }
        else{
            results[i][0] = distance[i];
            results[i][1] = previous[i];
        }
    }

    delete [] visited;
    delete [] distance;
    delete [] previous;

    return results;
}