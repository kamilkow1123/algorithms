#include<iostream>
#include<climits>
#include "../AdjacencyListGraph/graphAL.h"
#include "../IncidenceMatrixGraph/graphIM.h"
using namespace std;

int **bellmanFordAL(GraphAL *graph, int src){ //adjacency list
    int vertexes = graph->getNumOfVertexes(); //number of vertexes
    if(vertexes == 0){
        cout<<" Graph is empty!"<<endl;
        return nullptr;
    }
    int edges = graph->getNumOfEdges(); //number of edges
	int *distance = new int[vertexes]; //integer array to calculate minimum distance for each vertex
    int *previous = new int[vertexes]; //integer array of previous vertexes
    bool stop;
    int **results = new int*[vertexes]; //array for results

    //set the vertexes with infinity distance and previous vertexes with -1
    for(int i = 0; i < vertexes; i++)
	{
		distance[i] = INT_MAX;
        previous[i] = -1;
        results[i] = new int[2];
	}

    distance[src] = 0;   //source vertex distance is set to zero

    for(int i = 0; i < vertexes-1; i++){
        stop = true;
        for(int j = 0; j < vertexes; j++){
            for(Node *ver = graph->getList(j); ver; ver = ver->next){
                //updating the minimum distance for the particular vertex
                if((distance[j] != INT_MAX) && (distance[ver->vertex] > distance[j] + ver->edge)){
                    distance[ver->vertex] = distance[j] + ver->edge;
                    previous[ver->vertex] = j;
                    stop = false;
                }
            }
        }
        if(stop) break;
    }

    //Detect negative cycle
    for(int j = 0; j < vertexes; j++){
        for(Node *ver = graph->getList(j); ver; ver = ver->next){
            if((distance[j] != INT_MAX) && (distance[ver->vertex] > distance[j] + ver->edge)){
                cout<<" Negative cycle detected!"<<endl;
                return nullptr;
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

    delete [] distance;
    delete [] previous;

    return results;
}

int **bellmanFordIM(GraphIM *graph, int src){
    int vertexes = graph->getNumOfVertexes(); // number of vertexes
    if(vertexes == 0){
        cout<<" Graph is empty!"<<endl;
        return nullptr;
    }
    int edges = graph->getNumOfEdges(); //number of edges
	int *distance = new int[vertexes]; //integer array to calculate minimum distance for each vertex
    int *previous = new int[vertexes]; //integer array of previous vertexes
    int **results = new int*[vertexes]; //array for results

    //set the vertexes with infinity distance
    for(int i = 0; i < vertexes; i++)
	{
		distance[i] = INT_MAX;
        previous[i] = -1;
        results[i] = new int[2];
	}

    distance[src] = 0;   //source vertex distance is set to zero

    for(int i = 0; i < vertexes-1; i++){
        for(int j = 0; j < edges; j++){
            int u = graph->getStartingVertexOfEdge(j);
            int v = graph->getEndingVertexOfEdge(j);
            int w = graph->findElement(u, j);
            if(distance[u] != INT_MAX && distance[u] + w < distance[v]){
                distance[v] = distance[u] + w;
                previous[v] = u;
            }
        }
    }

    //detect negative cycle
    for(int j = 0; j < edges; j++){
        int u = graph->getStartingVertexOfEdge(j);
        int v = graph->getEndingVertexOfEdge(j);
        int w = graph->findElement(u, j);
        if(distance[u] != INT_MAX && distance[u] + w < distance[v]){
            cout<<" Negative cycle detected!"<<endl;
            return nullptr;
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

    delete [] distance;
    delete [] previous;

    return results;
}