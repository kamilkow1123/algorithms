#include<iostream>
#include<iomanip>
#include<fstream>
#include<climits>
#include "graphAL.h"
using namespace std;

GraphAL::GraphAL(){ //initialize the graph with zeros and null
    this->array = nullptr;
    this->numOfVertexes = 0;
    this->numOfEdges = 0;
    this->weight = 0;
}

GraphAL::~GraphAL(){ //release the memory allocated for the graph
    Node *temp, *temp2;
    for(int i = 0; i < numOfVertexes; i++){
        temp2 = array[i];
        while(temp2){
            temp = temp2;
            temp2 = temp2->next;
            delete temp;
        }
    }

    delete [] array;
}

void GraphAL::printGraph(){
    if(numOfVertexes == 0){ //if the graph is empty, print that and return
        cout<<" Graph is empty!"<<endl;
        return;
    }

    Node *temp;

    // cout<<endl;
    for(int i = 0; i < numOfVertexes; i++){
        cout<<" ["<<i<<"] = ";
        temp = array[i];
        while(temp){
            cout<<setw(3)<<"("<<temp->vertex<<":"<<temp->edge<<")";
            if(temp->next) cout<<setw(4)<<"->";
            temp = temp->next;
        }
        cout<<endl;
    }
    cout<<endl<<" Graph weight: "<<weight<<endl<<endl;
}

void GraphAL::setNumOfEdges(int num){ //set the number of edges
    this->numOfEdges = num;
}

void GraphAL::setNumOfVertexes(int num){ //set the number of vertices
    this->numOfVertexes = num;
}

int GraphAL::getNumOfEdges(){ //get the number of edges
    return numOfEdges;
}

int GraphAL::getNumOfVertexes(){ //get the number of vertices
    return numOfVertexes;
}

Node *GraphAL::getList(int ver){ //return the first node of the list - vertex and its neighbours
    return array[ver];
}

void GraphAL::addVertexes(int vertexes){ //initialize neighbourhood lists with null - vertexes without edges
    this->array = new Node *[vertexes]; //create array of empty lists

    for(int i = 0; i<vertexes; i++) this->array[i] = nullptr; //set the lists to null

    this->numOfVertexes = vertexes; //set the number of vertices in the graph
}

void GraphAL::addDirectedEdge(int ver1, int ver2, int dist){
    Node *temp = new Node(ver2, dist); //create new node - connection between two vertices
    temp->next = array[ver1]; //place new node at the beginning of the list
    this->array[ver1] = temp; //set new node as the beginning of the list
    this->weight += dist; //increase weight of the graph
    this->numOfEdges += 1; //increase number of edges
}

void GraphAL::addUndirectedEdge(int ver1, int ver2, int dist){
    Node *temp = new Node(ver2, dist); //create new node - connection between two vertices
    temp->next = array[ver1]; //place new node at the beginning of the list
    this->array[ver1] = temp; //set new node as the beginning of the list

    //repeat that with swapped vertices - so the edge is undirected
    Node *temp2 = new Node(ver1, dist);
    temp2->next = array[ver2];
    this->array[ver2] = temp2;
    this->weight += dist; //increase weight of the graph
    this->numOfEdges += 1; //increase number of edge
}

void GraphAL::fillGraphFromFile(bool directed){
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
        cout<<" Successfully filled list!"<<endl; //filled the graph from file
        in.close();
    }
    else{
        cout<<" Cannot open graph.txt"<<endl; //opening the file failed
    }
}