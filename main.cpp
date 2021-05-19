#include<iostream>
#include "Dijkstra/dijkstra.cpp"
#include "Bellman-Ford/bellmanFord.cpp"


using namespace std;

int main(){
    GraphAL *graphAL = new GraphAL();
    GraphIM *graphIM = new GraphIM();

    graphAL->fillGraphFromFile(false); // false - undirected graph, true - directed
    graphIM->fillGraphFromFile(true); // false - undirected graph, true - directed

    graphIM->printGraph();

    // dijkstraAL(graphAL, 0);
    // dijkstraIM(graphIM, 0);
    // bellmanFordAL(graphAL, 0);
    // bellmanFordIM(graphIM, 0);

    return 0;
}