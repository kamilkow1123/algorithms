#include<iostream>
#include<iomanip>
#include<fstream>
#include<climits>
#include "GraphIM.h"
using namespace std;

GraphIM::GraphIM(){
    this->numOfVertexes = 0;
    this->numOfEdges = 0;
    this->graph = nullptr;
}

GraphIM::~GraphIM(){
    for(int i = 0; i<numOfVertexes; i++) delete [] graph[i];
    delete [] graph;
}

void GraphIM::printGraph(){
    if(numOfVertexes == 0){
        cout<<"Graph is empty!"<<endl;
        return;
    }

    for(int i = 0; i<numOfVertexes; i++){
        for(int j = 0; j<numOfEdges; j++){ // change to numOfVertexes for adjacency matrix
            cout<<setw(5)<<graph[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}

void GraphIM::setNumOfEdges(int num){
    this->numOfEdges = num;
}

void GraphIM::setNumOfVertexes(int num){
    this->numOfVertexes = num;
}

int GraphIM::getNumOfEdges(){
    return numOfEdges;
}

int GraphIM::getNumOfVertexes(){
    return numOfVertexes;
}

int GraphIM::findElement(int n, int m){
    return graph[n][m];
}

int GraphIM::getStartingVertexOfEdge(int j){
    if(j > numOfEdges - 1) return -1;

    for(int i = 0; i<numOfVertexes; i++){
        if(graph[i][j] > 0)
            return i;
    }
    return -1;
}

int GraphIM::getEndingVertexOfEdge(int j){
    if(j > numOfEdges - 1) return -1;
    
    for(int i = 0; i<numOfVertexes; i++){
        if(graph[i][j] < 0)
            return i;
    }
        return -1;
}

void GraphIM::fillGraphFromFile(){
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
            graph[vertexStart][i] = distanceValue; // graph[vertexStart][vertexEnd] for adjacency matrix
            graph[vertexEnd][i] = -1*distanceValue; // comment this for adjacency matrix
        }

        setNumOfEdges(numberOfEdges);
        setNumOfVertexes(numberOfVertexes);

        in.close();
    }
    else{
        cout<<"Cannot open graph.txt"<<endl;
    }
}

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

void dijkstra(GraphIM *graph, int src) // incidence matrix 
{
    int vertexes = graph->getNumOfVertexes(); // number of vertexes
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
    cout<<"Results of the Dijkstra algorithm: "<<endl;
	cout<<"Vertex\tDistance from source\tPrevious vertex"<<endl;
	for(int i = 0; i < vertexes; i++) //printing             
	{ 
		cout<<i<<"\t\t"<<distance[i]<<"\t\t"<<previous[i]<<endl;
	}
    cout<<endl;

    delete [] visited;
    delete [] distance;
    delete [] previous;
}

void bellman_ford(GraphIM *graph, int src){
    int vertexes = graph->getNumOfVertexes(); // number of vertexes
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
            cout<<"Negative cycle detected!"<<endl;
            return;
        }
    }

    cout<<"Results of the Bellman-Ford algorithm: "<<endl;
	cout<<"Vertex\tDistance from source\tPrevious vertex"<<endl;
	for(int i = 0; i < vertexes; i++) //printing             
	{ 
		cout<<i<<"\t\t"<<distance[i]<<"\t\t"<<previous[i]<<endl;
	}
    cout<<endl;

    delete [] distance;
    delete [] previous;
}

int main(){
    GraphIM *graph = new GraphIM();

    graph->fillGraphFromFile();
    graph->printGraph();

    dijkstra(graph, 0);
    bellman_ford(graph, 0);

    delete graph;

    return 0;
}