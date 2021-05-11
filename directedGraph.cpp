#include<iostream>
#include<iomanip>
#include<fstream>
#include<climits>
#include "directedGraph.h"
using namespace std;

DirectedGraph::DirectedGraph(){
    this->numOfVertexes = 0;
    this->numOfEdges = 0;
    this->graph = nullptr;
}

DirectedGraph::~DirectedGraph(){
    for(int i = 0; i<numOfVertexes; i++) delete [] graph[i];
    delete [] graph;
}

void DirectedGraph::printGraph(){
    if(numOfVertexes == 0){
        cout<<"Graph is empty!"<<endl;
        return;
    }

    for(int i = 0; i<numOfVertexes; i++){
        for(int j = 0; j<numOfEdges; j++){
            cout<<setw(5)<<graph[i][j];
        }
        cout<<endl;
    }
}

void DirectedGraph::setNumOfEdges(int num){
    this->numOfEdges = num;
}

void DirectedGraph::setNumOfVertexes(int num){
    this->numOfVertexes = num;
}

int DirectedGraph::getNumOfEdges(){
    return numOfEdges;
}

int DirectedGraph::getNumOfVertexes(){
    return numOfVertexes;
}

int DirectedGraph::findElement(int n, int m){
    return graph[n][m];
}

void DirectedGraph::fillGraphFromFile(){
    if(numOfVertexes != 0){
        cout<<"Graph is not empty"<<endl;
        return;
    }

    fstream in;
    in.open("graph.txt", ios::in);

    if(in.good()){
        int numberOfEdges, numberOfVertexes;
        in>>numberOfEdges>>numberOfVertexes;

        graph = new int *[numberOfVertexes];

        for(int i = 0; i<numberOfVertexes; ++i){
            graph[i] = new int [numberOfEdges];
            for(int j = 0; j<numberOfEdges; ++j)
                graph[i][j] = 0;                    //filling the array with zeros
        }

        int vertexStart, vertexEnd, distanceValue;

        for(int i = 0; i<numberOfEdges; i++){
            in>>vertexStart>>vertexEnd>>distanceValue;
            graph[vertexStart][i] = distanceValue;
            graph[vertexEnd][i] = -1;
        }

        setNumOfEdges(numberOfEdges);
        setNumOfVertexes(numberOfVertexes);

        in.close();
    }
    else{
        cout<<"Cannot open graph.txt"<<endl;
    }
}

int minimumDist(int dist[], bool visited[], int n) 
{
	int min = INT_MAX, index;
              
	for(int i=0;i<n;i++) 
	{
		if(visited[i]==false && dist[i]<=min)      
		{
			min=dist[i];
			index=i;
		}
	}
	return index;
}

void dijkstra(DirectedGraph *graph, int src) // adjacency matrix 
{
    int n = graph->getNumOfVertexes();
	int *dist = new int[n]; // integer array to calculate minimum distance for each vertex                          
	bool *visited = new bool[n];// boolean array to mark visted/unvisted for each vertex
	
	// set the vertexes with infinity distance
	// except for the initial vertex and mark
	// them unvisited.  
	for(int i = 0; i<n; i++)
	{
		dist[i] = INT_MAX;
		visited[i] = false;	
	}
	
	dist[src] = 0;   // Source vertex distance is set to zero.             
	
	for(int i = 0; i<n; i++)                           
	{
		int m = minimumDist(dist,visited, n); // vertex not yet included.
		visited[m] = true;// m with minimum distance included in visited.
		for(int i = 0; i<n; i++)                  
		{
			// Updating the minimum distance for the particular node.
			if(!visited[i] && graph->findElement(m,i) && dist[m]!=INT_MAX && dist[m]+graph->findElement(m,i)<dist[i])
				dist[i]=dist[m]+graph->findElement(m,i);
		}
	}
	cout<<"Vertex\t\tDistance from source"<<endl;
	for(int i = 0; i<n; i++)                      
	{ //Printing
		// char str=65+i; // Ascii values for pritning A,B,C..
		cout<<i<<"\t\t\t"<<dist[i]<<endl;
	}
}

int main(){
    DirectedGraph *graph = new DirectedGraph();
    graph->printGraph();
    graph->fillGraphFromFile();
    graph->printGraph();

    dijkstra(graph, 0);

    return 0;
}