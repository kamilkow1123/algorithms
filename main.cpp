#include<iostream>
#include "Dijkstra/dijkstra.cpp"
#include "Bellman-Ford/bellmanFord.cpp"
#include "Prim/prim.cpp"
#include "Kruskal/kruskal.cpp"


using namespace std;

int main(){
    GraphAL *graphAL = new GraphAL();
    GraphIM *graphIM = new GraphIM();

    graphAL->fillGraphFromFile(false); // false - undirected graph, true - directed
    graphIM->fillGraphFromFile(true); // false - undirected graph, true - directed

    graphAL->printGraph();
    // graphIM->printGraph();

    // primAL(graphAL, 0);
    // primIM(graphIM, 0);

    kruskalAL(graphAL);
    // kruskalIM(graphIM);

    // dijkstraAL(graphAL, 0);
    // dijkstraIM(graphIM, 0);

    // bellmanFordAL(graphAL, 0);
    // bellmanFordIM(graphIM, 0);

    return 0;
}