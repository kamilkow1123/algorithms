#include<iostream>
#include "../AdjacencyListGraph/graphAL.h"
#include "../IncidenceMatrixGraph/graphIM.h"
#include "../PriorityQueue/queue.cpp"
using namespace std;

void primAL(GraphAL *graph, int src){
    int vertexes = graph->getNumOfVertexes(); // number of vertexes
    int edges = graph->getNumOfEdges(); // number of edges                      
	bool *visited = new bool[vertexes]; // boolean array to mark visted/unvisted for each vertex
    GraphAL *mst = new GraphAL();
    mst->addNodes(vertexes);
	
	// set the vertexes with infinity distance and mark them unvisited 
	for(int i = 0; i < vertexes; i++)
	{
		visited[i] = false;
	}

    visited[src] = true;
    int v = 0;
    Edge e;
    Queue *q = new Queue(edges); 

    for(int i = 0; i < vertexes - 1; i++){
        for(Node *ver = graph->getList(v); ver; ver = ver->next){
            if(!visited[ver->vertex]){
                e.vertexStart = v;
                e.vertexEnd = ver->vertex;
                e.weight = ver->edge;
                // e = new Edge(v, ver->vertex, ver->edge);
                q->push(e);
            }
        }

        do{
            e = q->front();
            q->pop();
        } while(visited[e.vertexEnd]);

        // cout<<e.vertexStart<<" "<<e.vertexEnd<<" "<<e.weight<<endl;
        mst->addNode(e.vertexStart, e.vertexEnd, e.weight);
        mst->addNode(e.vertexEnd, e.vertexStart, e.weight);

        visited[e.vertexEnd] = true;
        v = e.vertexEnd;
    }
    mst->setNumOfVertexes(vertexes);
    cout<<endl<<"MST from Prim's algorithm in adjacency list:"<<endl;
    mst->printGraph();
    delete [] visited;
}