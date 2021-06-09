#include<iostream>
#include "../AdjacencyListGraph/graphAL.h"
#include "../IncidenceMatrixGraph/graphIM.h"
#include "../UnionFind/unionFind.cpp"
using namespace std;

GraphAL* kruskalAL(GraphAL *graph){
    int vertexes = graph->getNumOfVertexes(); //number of vertexes
    if(vertexes == 0){ //if the graph is empty, print that and return
        cout<<" Graph is empty!"<<endl;
        return nullptr;
    }
    int edges = graph->getNumOfEdges(); //number of edges
    Edge edge;

    UnionFind set(vertexes);
    Queue *queue = new Queue(2*edges);
    GraphAL *mst = new GraphAL(); //minimum spanning tree
    mst->addVertexes(vertexes); //initialize graph with vertices and no edges yet

    for(int i = 0; i < vertexes; i++){
        set.makeSet(i);
    }

    for(int i = 0; i < vertexes; i++){
        for(Node *ver = graph->getList(i); ver; ver = ver->next){
            edge.vertexStart = i;
            edge.vertexEnd = ver->vertex;
            edge.weight = ver->edge;
            queue->push(edge); //add the edge to the queue
        }
    }

    for(int i = 0; i < vertexes - 1; i++){
        do{
            edge = queue->front();
            queue->pop();
        } while(set.findSet(edge.vertexStart) == set.findSet(edge.vertexEnd));

        mst->addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        set.unionSets(edge); //union sets connected by the edge
    }

    delete queue;

    return mst;
}

GraphIM* kruskalIM(GraphIM *graph){
    int vertexes = graph->getNumOfVertexes(); //number of vertexes
    if(vertexes == 0){ //if the graph is empty, print that and return
        cout<<" Graph is empty!"<<endl;
        return nullptr;
    }
    int edges = graph->getNumOfEdges(); //number of edges
    Edge edge;

    UnionFind set(vertexes);
    Queue *queue = new Queue(2*edges);
    GraphIM *mst = new GraphIM(); //minimum spanning tree
    mst->addVertexes(vertexes); //initialize graph with vertices and no edges yet

    for(int i = 0; i < vertexes; i++){
        set.makeSet(i);
    }

    for(int i = 0; i < vertexes; i++){
        for(int j = 0; j < edges; j++){
            if(graph->findElement(i, j) > 0){
                edge.vertexStart = i;
                edge.vertexEnd = graph->getEndingVertexOfUndirectedEdge(j,i);
                edge.weight = graph->findElement(i, j);
                queue->push(edge); //add the edge to the queue
            }
        }
    }

    for(int i = 0; i < vertexes - 1; i++){
        do{
            edge = queue->front();
            queue->pop();
        } while(set.findSet(edge.vertexStart) == set.findSet(edge.vertexEnd));

        mst->addUndirectedEdge(edge.vertexStart, edge.vertexEnd, edge.weight);
        set.unionSets(edge); //union sets connected by the edge
    }

    delete queue;

    return mst;
}