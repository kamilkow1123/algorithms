#include<iostream>
#include<iomanip>
#include<fstream>
#include<climits>
#include "graphIM.h"
using namespace std;

GraphIM::GraphIM(){ //initialize the graph with zeros and null
    this->numOfVertexes = 0;
    this->numOfEdges = 0;
    this->graph = nullptr;
    this->weight = 0;
}

GraphIM::~GraphIM(){ //release the memory allocated for the graph
    for(int i = 0; i<numOfVertexes; i++) delete [] graph[i];
    delete [] graph;
}

void GraphIM::printGraph(){
    if(numOfVertexes == 0){ //if the graph is empty, print that and return
        cout<<" Graph is empty!"<<endl;
        return;
    }
    cout<<"    ";
    for(int j = 0; j < numOfEdges; j++){
        cout<<setw(5)<<j;
    }
    cout<<endl<<"    ";
    for(int j = 0; j < numOfEdges*5 + 3; j++){
        cout<<"-";
    }
    cout<<endl;

    for(int i = 0; i<numOfVertexes; i++){
        cout<<" "<<i<<" |";
        for(int j = 0; j<numOfEdges; j++){
            cout<<setw(5)<<graph[i][j];
        }
        cout<<endl;
    }
    cout<<endl<<" Graph weight: "<<weight<<endl<<endl;
}

void GraphIM::setNumOfEdges(int num){ //set the number of edges
    this->numOfEdges = num;
}

void GraphIM::setNumOfVertexes(int num){ //set the number of vertices
    this->numOfVertexes = num;
}

int GraphIM::getNumOfEdges(){ //get the number of edges
    return numOfEdges;
}

int GraphIM::getNumOfVertexes(){ //get the number of vertices
    return numOfVertexes;
}

int GraphIM::findElement(int n, int m){ //return the value from the array's given indexes
    return graph[n][m];
}

int GraphIM::getStartingVertexOfEdge(int j){ //return the index of the starting vertex of given edge
    if(j > numOfEdges - 1) return -1; //return -1 if the given edge is not in the graph

    for(int i = 0; i<numOfVertexes; i++){
        if(graph[i][j] > 0) //the vertex that we are looking for must have value greater than 0
            return i;
    }
    return -1; //return -1 if nothing has been found
}

int GraphIM::getEndingVertexOfEdge(int j){ //return the index of the ending vertex of given edge
    if(j > numOfEdges - 1) return -1; //return -1 if the given edge is not in the graph

    for(int i = 0; i<numOfVertexes; i++){
        if(graph[i][j] < 0) //the ending vertices have negative values
            return i;
    }
    return -1; //return -1 if nothing has been found
}

int GraphIM::getEndingVertexOfUndirectedEdge(int j, int currentVertex){ //return the index of the ending vertex of the given undirected edge
    if(j > numOfEdges - 1) return -1; //return -1 if the given edge is not ing the graph

    for(int i = 0; i<numOfVertexes; i++){
        if(i == currentVertex) continue; //in undirected graph there is no separation between the starting and ending vertex so we need to skip the vertex that we came from
        if(graph[i][j] > 0) //the vertex that we are looking for must have value greater than 0
            return i;
    }
    return -1; //return -1 if nothing has been found
}

bool GraphIM::checkIfEdgeExists(int v1, int v2){ //checking if the edge between given vertices exists
    for(int i = 0; i < this->numOfEdges; i++){
        if(graph[v1][i] > 0 && graph[v2][i] != 0)
            return true; //return true if the edge exists
    }
    return false; //return false if there is no edge between given vertices
}

void GraphIM::addVertexes(int vertexes){ //initialize the incidence matrix with the given number of vertices - no edges yet
    this->graph = new int *[vertexes]; //create array of arrays for the vertices
    this->numOfVertexes = vertexes; //set the number of vertices in the graph
    for(int i = 0; i<numOfVertexes; i++){
        this->graph[i] = new int[0]; //set the vertexes arrays - no edges yet so they're empty
    }
}

void GraphIM::addUndirectedEdge(int ver1, int ver2, int dist){
    for(int i = 0; i < this->numOfVertexes; i++){
        graph[i] = (int*) realloc(graph[i], (this->numOfEdges + 1)*sizeof(int)); //reallocating the arrays for the new edge
        graph[i][this->numOfEdges] = 0; //filling the new edge with zeros
    }

    graph[ver1][this->numOfEdges] = dist; //setting the value of the edge for the starting vertex
    graph[ver2][this->numOfEdges] = dist; //setting the value of the edge for the ending vertex - edge is undirected so the value is the same as for the starting vertex
    this->weight += dist; //increase weight of the graph
    this->numOfEdges += 1; //increase number of edges
}

void GraphIM::addDirectedEdge(int ver1, int ver2, int dist){
    for(int i = 0; i < this->numOfVertexes; i++){
        graph[i] = (int*) realloc(graph[i], (this->numOfEdges + 1)*sizeof(int)); // reallocing the arrays for the new edge
        graph[i][this->numOfEdges] = 0; // filling the new edge with zeros
    }

    graph[ver1][this->numOfEdges] = dist; //setting the value of the edge for the starting vertex
    graph[ver2][this->numOfEdges] = -1*dist; //setting the value of the edge for the ending vertex - edge is directed so the value is negative
    this->weight += dist; //increase weight of the graph
    this->numOfEdges += 1; //increase number of edges
}

void GraphIM::fillGraphFromFile(bool directed){
    if(numOfVertexes != 0){ //if the graph is not empty, print that and return
        cout<<" Graph is not empty"<<endl;
        return;
    }

    fstream in;
    in.open("../graph.txt", ios::in); //open the file with the description of the edges
    if(!in.good()) in.open("graph.txt", ios::in); //if opening failed try in different location

    if(in.good()){ //if the file opened correctly, fill the graph
        int numberOfEdges, numberOfVertexes;
        in>>numberOfEdges>>numberOfVertexes; //get number of edges and number of vertices from the file

        this->addVertexes(numberOfVertexes); //initialize graph by adding vertices without edges

        int vertexStart, vertexEnd, distanceValue;

        for(int i = 0; i<numberOfEdges; i++){
            in>>vertexStart>>vertexEnd>>distanceValue; //get the description od the edge from the file

            if(directed) this->addDirectedEdge(vertexStart, vertexEnd, distanceValue); //if the graph ought to be directed - add directed edge
            else this->addUndirectedEdge(vertexStart, vertexEnd, distanceValue); //if the graph ought to be undirected - add undirected edge
        }
        cout<<" Successfully filled matrix!"<<endl; //filled the graph from file
        in.close();
    }
    else{
        cout<<" Cannot open graph.txt"<<endl; //opening the file failed
    }
}