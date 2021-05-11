#include<iostream>
#include<iomanip>
#include<fstream>
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

int main(){
    DirectedGraph *graph = new DirectedGraph();
    graph->printGraph();
    graph->fillGraphFromFile();
    graph->printGraph();
    return 0;
}