#include<iostream>
#include<climits>
#include "../AdjacencyListGraph/graphAL.h"
#include "../IncidenceMatrixGraph/graphIM.h"
using namespace std;

void bellmanFordAL(GraphAL *graph, int src, bool printResult){
    int vertexes = graph->getNumOfVertexes(); // number of vertexes
    if(vertexes == 0){
        cout<<" Graph is empty!"<<endl;
        return;
    }
    int edges = graph->getNumOfEdges(); // number of edges
	int *distance = new int[vertexes]; // integer array to calculate minimum distance for each vertex  
    int *previous = new int[vertexes]; // integer array of previous vertexes
    bool stop;

    // set the vertexes with infinity distance
    for(int i = 0; i < vertexes; i++)
	{
		distance[i] = INT_MAX;
        previous[i] = -1;
	}

    distance[src] = 0;   // source vertex distance is set to zero      

    for(int i = 0; i < vertexes-1; i++){
        stop = true;
        for(int j = 0; j < vertexes; j++){
            for(Node *ver = graph->getList(j); ver; ver = ver->next){
                // updating the minimum distance for the particular vertex
                if((distance[j] != INT_MAX) && (distance[ver->vertex] > distance[j] + ver->edge)){
                    distance[ver->vertex] = distance[j] + ver->edge;
                    previous[ver->vertex] = j;
                    stop = false;
                }
            }
        }
        if(stop) break;
    }

    // Detect negative cycle
    for(int j = 0; j < vertexes; j++){
        for(Node *ver = graph->getList(j); ver; ver = ver->next){
            if((distance[ver->vertex] > distance[j] + ver->edge)){
                cout<<" Negative cycle detected!"<<endl;
                return;
            }
        }
    }

    if(printResult){
        cout<<endl<<" Results of the Bellman-Ford algorithm for adjacency list: "<<endl;
        cout<<" Vertex\tDistance from source\tPrevious vertex"<<endl;
        for(int i = 0; i < vertexes; i++) //printing             
        { 
            cout<<" "<<i<<"\t\t"<<distance[i]<<"\t\t"<<previous[i]<<endl;
        }
        cout<<endl;
    }

    delete [] distance;
    delete [] previous;
}

void bellmanFordIM(GraphIM *graph, int src, bool printResult){
    int vertexes = graph->getNumOfVertexes(); // number of vertexes
    if(vertexes == 0){
        cout<<" Graph is empty!"<<endl;
        return;
    }
    int edges = graph->getNumOfEdges(); // number of edges
	int *distance = new int[vertexes]; // integer array to calculate minimum distance for each vertex  
    int *previous = new int[vertexes]; // integer array of previous vertexes

    // set the vertexes with infinity distance
    for(int i = 0; i < vertexes; i++)
	{
		distance[i] = INT_MAX;
        previous[i] = -1;
	}

    distance[src] = 0;   // source vertex distance is set to zero      

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

    // Detect negative cycle
    for(int j = 0; j < edges; j++){
        int u = graph->getStartingVertexOfEdge(j);
        int v = graph->getEndingVertexOfEdge(j);
        int w = graph->findElement(u, j);
        if(distance[u] != INT_MAX && distance[u] + w < distance[v]){
            cout<<" Negative cycle detected!"<<endl;
            return;
        }
    }

    if(printResult){
        cout<<endl<<" Results of the Bellman-Ford algorithm for incidence matrix: "<<endl;
        cout<<" Vertex\tDistance from source\tPrevious vertex"<<endl;
        for(int i = 0; i < vertexes; i++) //printing             
        { 
            cout<<" "<<i<<"\t\t"<<distance[i]<<"\t\t"<<previous[i]<<endl;
        }
        cout<<endl;
    }

    delete [] distance;
    delete [] previous;
}