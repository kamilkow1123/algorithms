#include<iostream>
#include "Dijkstra/dijkstra.cpp"
#include "Bellman-Ford/bellmanFord.cpp"
#include "Prim/prim.cpp"


using namespace std;

int main(){
    GraphAL *graphAL = new GraphAL();
    GraphIM *graphIM = new GraphIM();

    graphAL->fillGraphFromFile(false); // false - undirected graph, true - directed
    graphIM->fillGraphFromFile(false); // false - undirected graph, true - directed

    graphAL->printGraph();
    graphIM->printGraph();

    primAL(graphAL, 0);
    primIM(graphIM, 0);

    // dijkstraAL(graphAL, 0);
    // dijkstraIM(graphIM, 0);
    // bellmanFordAL(graphAL, 0);
    // bellmanFordIM(graphIM, 0);

    return 0;
}