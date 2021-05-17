#include<iostream>
#include<iomanip>
#include<fstream>
#include<climits>
#include "GraphAL.h"
using namespace std;

GraphAL::GraphAL(){
    this->array = nullptr;
    this->numOfVertexes = 0;
    this->numOfEdges = 0;
}

GraphAL::~GraphAL(){
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
    if(numOfVertexes == 0){
        cout<<"Graph is empty!"<<endl;
        return;
    }

    Node *temp;

    for(int i = 0; i < numOfVertexes; i++){
        cout<<"["<<i<<"] = ";
        temp = array[i];
        while(temp){
            cout<<setw(3)<<"("<<temp->vertex<<":"<<temp->edge<<")";
            if(temp->next) cout<<setw(4)<<"->";
            temp = temp->next;
        }
        cout<<endl;
    }
    cout<<endl;
}

void GraphAL::setNumOfEdges(int num){
    this->numOfEdges = num;
}

void GraphAL::setNumOfVertexes(int num){
    this->numOfVertexes = num;
}

int GraphAL::getNumOfEdges(){
    return numOfEdges;
}

int GraphAL::getNumOfVertexes(){
    return numOfVertexes;
}

void GraphAL::fillGraphFromFile(){
    if(numOfVertexes != 0){
        cout<<"Graph is not empty"<<endl;
        return;
    }

    fstream in;
    in.open("graph.txt", ios::in);

    if(in.good()){
        int numberOfEdges, numberOfVertexes;
        in>>numberOfEdges>>numberOfVertexes;

        array = new Node *[numberOfVertexes];

        for(int i = 0; i<numberOfVertexes; i++) array[i] = nullptr;

        int vertexStart, vertexEnd, distanceValue;
        Node *temp;

        for(int i = 0; i<numberOfEdges; i++){
            in>>vertexStart>>vertexEnd>>distanceValue;
            temp = new Node(vertexEnd, distanceValue);
            temp->next = array[vertexStart];
            array[vertexStart] = temp;
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
    GraphAL *graph = new GraphAL();

    graph->fillGraphFromFile();
    graph->printGraph();

    return 0;
}