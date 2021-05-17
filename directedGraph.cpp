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
        for(int j = 0; j<numOfEdges; j++){ // change to numOfVertexes for adjacency matrix
            cout<<setw(5)<<graph[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
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

int DirectedGraph::getStartingVertexOfEdge(int j){
    if(j > numOfEdges - 1) return -1;

    for(int i = 0; i<numOfVertexes; i++){
        if(graph[i][j] > 0)
            return i;
    }
    return -1;
}

int DirectedGraph::getEndingVertexOfEdge(int j){
    if(j > numOfEdges - 1) return -1;
    
    for(int i = 0; i<numOfVertexes; i++){
        if(graph[i][j] < 0)
            return i;
    }
        return -1;
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

void dijkstra(DirectedGraph *graph, int src) // adjacency matrix 
{
    int vertexes = graph->getNumOfVertexes();
	int *distance = new int[vertexes]; // integer array to calculate minimum distance for each vertex                          
	bool *visited = new bool[vertexes];// boolean array to mark visted/unvisted for each vertex
	
	// set the vertexes with infinity distance
	// except for the initial vertex and mark
	// them unvisited.  
	for(int i = 0; i < vertexes; i++)
	{
		distance[i] = INT_MAX;
		visited[i] = false;
	}
	
	distance[src] = 0;   // source vertex distance is set to zero            
	
	for(int i = 0; i < vertexes; i++)                           
	{
		int min = minimumVertex(distance,visited, vertexes); // vertex not yet included
		visited[min] = true;// min with minimum distance included in visited

		for(int j = 0; j < vertexes; j++)                  
		{
			// updating the minimum distance for the particular vertex
			if(graph->findElement(min, j) != 0 && !visited[j]){
                int dist = distance[min] + graph->findElement(min, j);
                if(dist < distance[j]){
                    distance[j] = dist;
                }
            }
		}
	}
    cout<<"Results of the Dijkstra algorithm: "<<endl;
	cout<<"Vertex\tDistance from source"<<endl;
	for(int i = 0; i < vertexes; i++) //printing             
	{ 
		cout<<i<<"\t\t"<<distance[i]<<endl;
	}

    delete [] visited;
    delete [] distance;
}

void bellman_ford(DirectedGraph *graph, int src){
    int vertexes = graph->getNumOfVertexes();
    int edges = graph->getNumOfEdges();
	int *distance = new int[vertexes]; // integer array to calculate minimum distance for each vertex  
    int *previous = new int[vertexes]; // integer array of previous vertexes

    // set the vertexes with infinity distance
    for(int i = 0; i < vertexes; i++)
	{
		distance[i] = INT_MAX;
        previous[i] = 0;
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

    delete [] distance;
    delete [] previous;
}

int main(){
    DirectedGraph *graph = new DirectedGraph();

    graph->fillGraphFromFile();
    graph->printGraph();

    // dijkstra(graph, 0);
    bellman_ford(graph, 0);

    // cout<<graph->getStartingVertexOfEdge(6)<<endl;
    // cout<<graph->getEndingVertexOfEdge(6)<<endl;

    delete graph;

    return 0;
}