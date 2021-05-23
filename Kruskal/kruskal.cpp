#include<iostream>
#include "../AdjacencyListGraph/graphAL.h"
#include "../IncidenceMatrixGraph/graphIM.h"
#include "../UnionFind/unionFind.cpp"
using namespace std;

void kruskalAL(GraphAL *graph){
    int vertexes = graph->getNumOfVertexes(); // number of vertexes
    int edges = graph->getNumOfEdges(); // number of edges  
    Edge edge;

    UnionFind set(vertexes);
    Queue *queue = new Queue(edges);
    GraphAL *mst = new GraphAL();
    mst->addVertexes(vertexes);

    for(int i = 0; i < vertexes; i++){
        set.makeSet(i);
    }

    for(int i = 0; i < vertexes; i++){
        for(Node *ver = graph->getList(i); ver; ver = ver->next){
            edge.vertexStart = i;
            edge.vertexEnd = ver->vertex;
            edge.weight = ver->edge;
            queue->push(edge);
            // cout<<edge.vertexStart<<" "<<edge.vertexEnd<<" "<<edge.weight<<endl;
        }
    }
    
    for(int i = 1; i < vertexes; i++){
        do{
            edge = queue->front();
            queue->pop();
        } while(set.findSet(edge.vertexStart) == set.findSet(edge.vertexEnd));

        mst->addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        set.unionSets(edge);
    }
    cout<<endl<<"MST from Kruskal's algorithm in adjacency list:"<<endl;
    mst->printGraph();
}