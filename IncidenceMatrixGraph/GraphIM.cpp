#include<iostream>
#include<iomanip>
#include<fstream>
#include<climits>
#include "graphIM.h"
using namespace std;

GraphIM::GraphIM(){
    this->numOfVertexes = 0;
    this->numOfEdges = 0;
    this->graph = nullptr;
    this->weight = 0;
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
    cout<<"Graph weight: "<<weight<<endl;
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

void GraphIM::addEdge(int ver, int edge, int dist){
    graph[ver][edge] = dist; 
    if(dist > 0) weight += dist;
}

void GraphIM::fillGraphFromFile(bool directed){
    if(numOfVertexes != 0){
        cout<<"Graph is not empty"<<endl;
        return;
    }

    fstream in;
    in.open("../graph.txt", ios::in);
    if(!in.good()) in.open("graph.txt", ios::in);

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
            this->addEdge(vertexStart, i, distanceValue);
            if(directed) distanceValue *= -1;
            this->addEdge(vertexEnd, i, distanceValue);
            if(!directed) weight -= distanceValue;
        }

        setNumOfEdges(numberOfEdges);
        setNumOfVertexes(numberOfVertexes);

        in.close();
    }
    else{
        cout<<"Cannot open graph.txt"<<endl;
    }
}

// int main(){
//     GraphIM *graph = new GraphIM();

//     graph->fillGraphFromFile();
//     graph->printGraph();

//     dijkstra(graph, 0);
//     bellman_ford(graph, 0);

//     delete graph;

//     return 0;
// }